#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <signal.h>

#include "box86context.h"
#include "elfloader.h"
#include "debug.h"
#include "x86trace.h"
#include "x86emu.h"
#include "librarian.h"
#include "bridge.h"
#include "library.h"
#include "callback.h"
#include "wrapper.h"
#include "myfts.h"
#include "threads.h"
#include "x86trace.h"
#include "signals.h"
#ifdef DYNAREC
#include <sys/mman.h>
#include "dynablock.h"

#define MMAPSIZE (4*1024*1024)      // allocate 4Mo sized blocks
#define MMAPBLOCK   256             // minimum size of a block
//#define USE_MMAP

typedef struct mmaplist_s {
    void*         block;
    uint8_t       map[MMAPSIZE/(8*MMAPBLOCK)];  // map of allocated sub-block
} mmaplist_t;

// get first subblock free in map, stating at start. return -1 if no block, else first subblock free, filling size (in subblock unit)
static int getFirstBlock(mmaplist_t *map, int start, int maxsize, int* size)
{
    #define ISFREE(A) (((map->map[(A)>>3]>>((A)&7))&1)?0:1)
    if(start<0) start = 0;
    while(start<MMAPSIZE/(8*MMAPBLOCK)) {   // still a chance...
        if(ISFREE(start)) {
            // free, now get size...
            int end = start+1;
            while(end<MMAPSIZE/(8*MMAPBLOCK)) {
                if(!ISFREE(end) || (end-start==maxsize)) {
                    if(size) *size = end-start;
                    return start;
                }
                ++end;
            }
            if(size) *size = end-start;
            return start;
        }
        ++start;
    }
    return -1;
}

static void allocBlock(mmaplist_t *map, int start, int size)
{
    for(int i=0; i<size; ++i) {
        map->map[start/8]|=(1<<(start&7));
        ++start;
    }
}
static void freeBlock(mmaplist_t *map, int start, int size)
{
    for(int i=0; i<size; ++i) {
        map->map[start/8]&=~(1<<(start&7));
        ++start;
    }
}

uintptr_t AllocDynarecMap(int size, int nolinker)
{
    if(size>MMAPSIZE) {
        #ifdef USE_MMAP
        void* p = mmap(NULL, size, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        if(p==MAP_FAILED) {
            dynarec_log(LOG_INFO, "Cannot create dynamic map of %d bytes\n", size);
            return 0;
        }
        #else
        void *p = NULL;
        if(posix_memalign(&p, box86_pagesize, size)) {
            dynarec_log(LOG_INFO, "Cannot create dynamic map of %d bytes\n", size);
            return 0;
        }
        mprotect(p, size, PROT_READ | PROT_WRITE | PROT_EXEC);
        #endif
        return (uintptr_t)p;
    }
    pthread_mutex_lock(&my_context->mutex_mmap);
    int bsize = (size+MMAPBLOCK-1)/MMAPBLOCK;
    // look for free space
    for(int i=0; i<my_context->mmapsize; ++i) {
        int rsize = 0;
        int start = 0;
        do {
            start = getFirstBlock(my_context->mmaplist+i, start, bsize, &rsize);
            if(start!=-1 && rsize>=bsize) {
                allocBlock(my_context->mmaplist+i, start, bsize);
                uintptr_t ret = (uintptr_t)my_context->mmaplist[i].block + start*MMAPBLOCK;
                pthread_mutex_unlock(&my_context->mutex_mmap);
                return ret;
            }
            if(start!=-1)
                start += rsize;
        } while (start!=-1);
    }
    // no luck, add a new one !
    int i = my_context->mmapsize++;    // yeah, useful post incrementation
    dynarec_log(LOG_DEBUG, "Ask for DynaRec Block Alloc #%d\n", my_context->mmapsize);
    my_context->mmaplist = (mmaplist_t*)realloc(my_context->mmaplist, my_context->mmapsize*sizeof(mmaplist_t));
    #ifdef USE_MMAP
    void* p = mmap(NULL, MMAPSIZE, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if(p==MAP_FAILED) {
        dynarec_log(LOG_INFO, "Cannot create memory map of %d byte for dynarec block #%d\n", MMAPSIZE, i);
        --my_context->mmapsize;
        pthread_mutex_unlock(&my_context->mutex_mmap);
        return 0;
    }
    #else
    void *p = NULL;
    if(posix_memalign(&p, box86_pagesize, MMAPSIZE)) {
        dynarec_log(LOG_INFO, "Cannot create memory map of %d byte for dynarec block #%d\n", MMAPSIZE, i);
        --my_context->mmapsize;
        pthread_mutex_unlock(&my_context->mutex_mmap);
        return 0;
    }
    mprotect(p, MMAPSIZE, PROT_READ | PROT_WRITE | PROT_EXEC);
    #endif
    my_context->mmaplist[i].block = p;
    memset(my_context->mmaplist[i].map, 0, sizeof(my_context->mmaplist[i].map));
    allocBlock(my_context->mmaplist+i, 0, bsize);
    pthread_mutex_unlock(&my_context->mutex_mmap);
    return (uintptr_t)p;
}

void FreeDynarecMap(uintptr_t addr, uint32_t size)
{
    if(size>MMAPSIZE) {
        munmap((void*)addr, size);
        return;
    }
    pthread_mutex_lock(&my_context->mutex_mmap);
    int bsize = (size+MMAPBLOCK-1)/MMAPBLOCK;
    // look for free space
    for(int i=0; i<my_context->mmapsize; ++i) {
        if(addr>=(uintptr_t)my_context->mmaplist[i].block && ((uintptr_t)my_context->mmaplist[i].block+MMAPSIZE)>=addr+size) {
            int start = (addr - (uintptr_t)my_context->mmaplist[i].block) / MMAPBLOCK;
            freeBlock(my_context->mmaplist+i, start, bsize);
            pthread_mutex_unlock(&my_context->mutex_mmap);
            return;
        }
    }
    pthread_mutex_unlock(&my_context->mutex_mmap);
}

// each dynmap is 64k of size
dynablocklist_t* getDBFromAddress(uintptr_t addr)
{
    int idx = (addr>>DYNAMAP_SHIFT);
    if(!my_context->dynmap[idx]) {
        return NULL;
    }
    return my_context->dynmap[idx]->dynablocks;
}

void addDBFromAddressRange(uintptr_t addr, uintptr_t size, int nolinker)
{
    dynarec_log(LOG_DEBUG, "addDBFromAddressRange %p -> %p\n", (void*)addr, (void*)(addr+size-1));
    uintptr_t idx = (addr>>DYNAMAP_SHIFT);
    uintptr_t end = ((addr+size-1)>>DYNAMAP_SHIFT);
    for (uintptr_t i=idx; i<=end; ++i) {
        if(!my_context->dynmap[i]) {
            my_context->dynmap[i] = (dynmap_t*)calloc(1, sizeof(dynmap_t));
            my_context->dynmap[i]->dynablocks = NewDynablockList(i<<DYNAMAP_SHIFT, i<<DYNAMAP_SHIFT, 1<<DYNAMAP_SHIFT, nolinker, 0);
        } else {
            ProtectkDynablockList(&my_context->dynmap[i]->dynablocks);
        }
    }
}

void cleanDBFromAddressRange(uintptr_t addr, uintptr_t size, int destroy)
{
    dynarec_log(LOG_DEBUG, "cleanDBFromAddressRange %p -> %p %s\n", (void*)addr, (void*)(addr+size-1), destroy?"destroy":"mark");
    uintptr_t idx = (addr>box86_dynarec_largest && !destroy)?((addr-box86_dynarec_largest)>>DYNAMAP_SHIFT):(addr>>DYNAMAP_SHIFT);
    uintptr_t end = ((addr+size-1)>>DYNAMAP_SHIFT);
    for (uintptr_t i=idx; i<=end; ++i) {
        dynmap_t* dynmap = my_context->dynmap[i];
        if(dynmap) {
            uintptr_t startdb = StartDynablockList(dynmap->dynablocks);
            uintptr_t enddb = EndDynablockList(dynmap->dynablocks);
            uintptr_t startaddr = addr;
            if(startaddr<startdb) startaddr = startdb;
            uintptr_t endaddr = addr + size - 1;
            if(endaddr>enddb) endaddr = enddb;
            if(startaddr==startdb && endaddr==enddb) {
                if(destroy) {
                    my_context->dynmap[i] = NULL;
                    FreeDynablockList(&dynmap->dynablocks);
                    free(dynmap);
                } else
                    MarkDynablockList(&dynmap->dynablocks);
            } else
                if(destroy)
                    FreeRangeDynablock(dynmap->dynablocks, startaddr, endaddr-startaddr+1);
                else
                    MarkRangeDynablock(dynmap->dynablocks, startaddr, endaddr-startaddr+1);

        }
    }
}

// Remove the Write flag from an adress range, so DB can be executed
// no log, as it can be executed inside a signal handler
void protectDB(uintptr_t addr, uintptr_t size)
{
    uintptr_t start = (addr)&~(box86_pagesize-1);
    uintptr_t end = (addr+size+(box86_pagesize-1))&~(box86_pagesize-1);
    // should get "end" according to last block inside the window
    mprotect((void*)start, end-start, PROT_READ|PROT_EXEC);
}

// Add the Write flag from an adress range, and mark all block as dirty
// no log, as it can be executed inside a signal handler
void unprotectDB(uintptr_t addr, uintptr_t size)
{
    uintptr_t start = (addr)&~(box86_pagesize-1);
    uintptr_t end = (addr+size+(box86_pagesize-1))&~(box86_pagesize-1);
    // should get "end" according to last block inside the window
    mprotect((void*)start, end-start, PROT_READ|PROT_WRITE|PROT_EXEC);
    cleanDBFromAddressRange(start, end-start, 0);
}

#endif

EXPORTDYN
void initAllHelpers(box86context_t* context)
{
    static int inited = 0;
    if(inited)
        return;
    my_context = context;
    init_pthread_helper();
    init_signal_helper(context);
    inited = 1;
}

EXPORTDYN
void finiAllHelpers()
{
    static int finied = 0;
    if(finied)
        return;
    fini_pthread_helper();
    fini_signal_helper();
    finied = 1;
}

void x86Syscall(x86emu_t *emu);

/// maxval not inclusive
int getrand(int maxval)
{
    if(maxval<1024) {
        return ((random()&0x7fff)*maxval)/0x7fff;
    } else {
        uint64_t r = random();
        r = (r*maxval) / RAND_MAX;
        return r;
    }
}

void free_tlsdatasize(void* p)
{
    if(!p)
        return;
    tlsdatasize_t *data = (tlsdatasize_t*)p;
    free(data->tlsdata);
    free(p);
}

EXPORTDYN
box86context_t *NewBox86Context(int argc)
{
#ifdef BUILD_DYNAMIC
    if(my_context) {
        ++my_context->count;
        return my_context;
    }
#endif
    // init and put default values
    box86context_t *context = (box86context_t*)calloc(1, sizeof(box86context_t));

#ifdef BUILD_LIB
    context->deferedInit = 0;
#else
    context->deferedInit = 1;
#endif
    context->maplib = NewLibrarian(context, 1);
    context->local_maplib = NewLibrarian(context, 1);
    context->system = NewBridge();
    // create vsyscall
    context->vsyscall = AddBridge(context->system, vFv, x86Syscall, 0);
#ifdef BUILD_LIB
    context->box86lib = RTLD_DEFAULT;   // not ideal
#else
    context->box86lib = dlopen(NULL, RTLD_NOW|RTLD_GLOBAL);
#endif
    context->dlprivate = NewDLPrivate();

    context->callbacks = NewCallbackList();

    context->argc = argc;
    context->argv = (char**)calloc(context->argc+1, sizeof(char*));

    pthread_mutex_init(&context->mutex_once, NULL);
    pthread_mutex_init(&context->mutex_once2, NULL);
    pthread_mutex_init(&context->mutex_trace, NULL);
#ifndef DYNAREC
    pthread_mutex_init(&context->mutex_lock, NULL);
#endif
    pthread_mutex_init(&context->mutex_tls, NULL);
    pthread_mutex_init(&context->mutex_thread, NULL);
#ifdef DYNAREC
    pthread_mutex_init(&context->mutex_dyndump, NULL);
#endif
    pthread_key_create(&context->tlskey, free_tlsdatasize);

#ifdef DYNAREC
    pthread_mutex_init(&context->mutex_blocks, NULL);
    pthread_mutex_init(&context->mutex_mmap, NULL);
    context->dynablocks = NewDynablockList(0, 0, 0, 0, 0);
#endif
    InitFTSMap(context);

    for (int i=0; i<4; ++i) context->canary[i] = 1 +  getrand(255);
    context->canary[getrand(4)] = 0;
    printf_log(LOG_DEBUG, "Setting up canary (for Stack protector) at GS:0x14, value:%08X\n", *(uint32_t*)context->canary);

    initAllHelpers(context);

    return context;
}

EXPORTDYN
void FreeBox86Context(box86context_t** context)
{
#ifdef BUILD_DYNAMIC
    if(--(*context)->count)
        return;
#endif
    if(!context)
        return;
    
    if(--(*context)->forked >= 0)
        return;

    box86context_t* ctx = *context;   // local copy to do the cleanning

    for(int i=0; i<ctx->elfsize; ++i) {
        FreeElfHeader(&ctx->elfs[i]);
    }
    free(ctx->elfs);

    FreeFTSMap(ctx);

    if(ctx->maplib)
        FreeLibrarian(&ctx->maplib);
    if(ctx->local_maplib)
        FreeLibrarian(&ctx->local_maplib);

    FreeCollection(&ctx->box86_path);
    FreeCollection(&ctx->box86_ld_lib);
    FreeCollection(&ctx->box86_emulated_libs);
    // stop trace now
    if(ctx->dec)
        DeleteX86TraceDecoder(&ctx->dec);
    if(ctx->zydis)
        DeleteX86Trace(ctx);

    if(ctx->deferedInitList)
        free(ctx->deferedInitList);

    free(ctx->argv);
    
    for (int i=0; i<ctx->envc; ++i)
        free(ctx->envv[i]);
    free(ctx->envv);

#ifdef DYNAREC
    dynarec_log(LOG_DEBUG, "Free global Dynarecblocks\n");
    if(ctx->dynablocks)
        FreeDynablockList(&ctx->dynablocks);
    for (int i=0; i<ctx->mmapsize; ++i)
        if(ctx->mmaplist[i].block)
            #ifdef USE_MMAP
            munmap(ctx->mmaplist[i].block, MMAPSIZE);
            #else
            free(ctx->mmaplist[i].block);
            #endif
    dynarec_log(LOG_DEBUG, "Free dynamic Dynarecblocks\n");
    cleanDBFromAddressRange(0, 0xffffffff, 1);
    pthread_mutex_destroy(&ctx->mutex_blocks);
    pthread_mutex_destroy(&ctx->mutex_mmap);
    free(ctx->mmaplist);
#endif
    
    *context = NULL;                // bye bye my_context

    CleanStackSize(ctx);

#ifndef BUILD_LIB
    if(ctx->box86lib)
        dlclose(ctx->box86lib);
#endif

    FreeDLPrivate(&ctx->dlprivate);

    free(ctx->stack);

    free(ctx->fullpath);
    free(ctx->box86path);

    FreeBridge(&ctx->system);

    freeGLProcWrapper(ctx);
    freeALProcWrapper(ctx);

    FreeCallbackList(&ctx->callbacks);

    void* ptr;
    if ((ptr = pthread_getspecific(ctx->tlskey)) != NULL) {
        free_tlsdatasize(ptr);
        pthread_setspecific(ctx->tlskey, NULL);
    }
    pthread_key_delete(ctx->tlskey);

    if(ctx->tlsdata)
        free(ctx->tlsdata);

    for(int i=0; i<3; ++i) {
        if(ctx->segtls[i].present) {
            // key content not handled by box86, so not doing anything with it
            pthread_key_delete(ctx->segtls[i].key);
        }
    }

    pthread_mutex_destroy(&ctx->mutex_once);
    pthread_mutex_destroy(&ctx->mutex_once2);
    pthread_mutex_destroy(&ctx->mutex_trace);
#ifndef DYNAREC
    pthread_mutex_destroy(&ctx->mutex_lock);
#endif
    pthread_mutex_destroy(&ctx->mutex_tls);
    pthread_mutex_destroy(&ctx->mutex_thread);
#ifdef DYNAREC
    pthread_mutex_destroy(&ctx->mutex_dyndump);
#endif

    free_neededlib(&ctx->neededlibs);

    if(ctx->atfork_sz) {
        free(ctx->atforks);
        ctx->atforks = NULL;
        ctx->atfork_sz = ctx->atfork_cap = 0;
    }

    for(int i=0; i<MAX_SIGNAL; ++i)
        if(ctx->signals[i]!=0 && ctx->signals[i]!=1) {
            signal(i, SIG_DFL);
        }

    if(ctx->emu_sig)
        FreeX86Emu(&ctx->emu_sig);

    finiAllHelpers();

    free(ctx);
}

int AddElfHeader(box86context_t* ctx, elfheader_t* head) {
    int idx = ctx->elfsize;
    if(idx==ctx->elfcap) {
        // resize...
        ctx->elfcap += 16;
        ctx->elfs = (elfheader_t**)realloc(ctx->elfs, sizeof(elfheader_t*) * ctx->elfcap);
    }
    ctx->elfs[idx] = head;
    ctx->elfsize++;
    printf_log(LOG_DEBUG, "Adding \"%s\" as #%d in elf collection\n", ElfName(head), idx);
    return idx;
}

int AddTLSPartition(box86context_t* context, int tlssize) {
    int oldsize = context->tlssize;
    context->tlssize += tlssize;
    context->tlsdata = realloc(context->tlsdata, context->tlssize);
    memmove(context->tlsdata+tlssize, context->tlsdata, oldsize);   // move to the top, using memmove as regions will probably overlap
    memset(context->tlsdata, 0, tlssize);           // fill new space with 0 (not mandatory)
    return -context->tlssize;   // negative offset
}

void add_neededlib(needed_libs_t* needed, library_t* lib)
{
    if(!needed)
        return;
    if(needed->size == needed->cap) {
        needed->cap += 8;
        needed->libs = (library_t**)realloc(needed->libs, needed->cap*sizeof(library_t*));
    }
    needed->libs[needed->size++] = lib;
}

void free_neededlib(needed_libs_t* needed)
{
    if(!needed)
        return;
    needed->cap = 0;
    needed->size = 0;
    if(needed->libs)
        free(needed->libs);
    needed->libs = NULL;
}
