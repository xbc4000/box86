#if !(defined(GO) && defined(GOM) && defined(GO2) && defined(DATA))
#error meh!
#endif

GO(pango_alignment_get_type, iFv)
GO(pango_attr_background_new, pFWWW)
GO(pango_attr_fallback_new, pFi)
GO(pango_attr_family_new, pFp)
GO(pango_attr_font_desc_new, pFp)
GO(pango_attr_foreground_new, pFWWW)
GO(pango_attr_gravity_hint_new, pFi)
GO(pango_attr_gravity_new, pFi)
GO(pango_attribute_copy, pFp)
GO(pango_attribute_destroy, vFp)
GO(pango_attribute_equal, iFpp)
GO(pango_attribute_init, vFpp)
GO(pango_attr_iterator_copy, pFp)
GO(pango_attr_iterator_destroy, vFp)
GO(pango_attr_iterator_get, pFpi)
GO(pango_attr_iterator_get_attrs, pFp)
GO(pango_attr_iterator_get_font, vFpppp)
GO(pango_attr_iterator_next, iFp)
GO(pango_attr_iterator_range, vFppp)
GO(pango_attr_language_new, pFp)
GO(pango_attr_letter_spacing_new, pFi)
GO(pango_attr_list_change, vFpp)
GO(pango_attr_list_copy, pFp)
//GOM(pango_attr_list_filter, pFEpBp)
GO(pango_attr_list_get_iterator, pFp)
GO(pango_attr_list_get_type, iFv)
GO(pango_attr_list_insert, vFpp)
GO(pango_attr_list_insert_before, vFpp)
GO(pango_attr_list_new, pFv)
GO(pango_attr_list_ref, pFp)
GO(pango_attr_list_splice, vFppii)
GO(pango_attr_list_unref, vFp)
GO(pango_attr_rise_new, pFi)
GO(pango_attr_scale_new, pFd)
GO(pango_attr_shape_new, pFpp)
//GOM(pango_attr_shape_new_with_data, pFpppBB)
GO(pango_attr_size_new, pFi)
GO(pango_attr_size_new_absolute, pFi)
GO(pango_attr_stretch_new, pFi)
GO(pango_attr_strikethrough_color_new, pFWWW)
GO(pango_attr_strikethrough_new, pFi)
GO(pango_attr_style_new, pFi)
GO(pango_attr_type_get_name, pFp)
GO(pango_attr_type_get_type, iFv)
GO(pango_attr_type_register, iFp)
GO(pango_attr_underline_color_new, pFWWW)
GO(pango_attr_underline_new, pFi)
GO(pango_attr_variant_new, pFi)
GO(pango_attr_weight_new, pFi)
//GO(pango_bidi_type_for_unichar, 
//GO(pango_bidi_type_get_type, 
//GO(pango_break, 
GO(pango_color_copy, pFp)
GO(pango_color_free, vFp)
GO(pango_color_get_type, iFv)
GO(pango_color_parse, iFpp)
//GO(pango_color_to_string, 
//GO(pango_config_key_get, 
//GO(pango_config_key_get_system, 
//GO(pango_context_changed, 
//GO(pango_context_get_base_dir, 
//GO(pango_context_get_base_gravity, 
//GO(pango_context_get_font_description, 
//GO(pango_context_get_font_map, 
//GO(pango_context_get_gravity, 
//GO(pango_context_get_gravity_hint, 
//GO(pango_context_get_language, 
//GO(pango_context_get_matrix, 
//GO(pango_context_get_metrics, 
//GO(pango_context_get_serial, 
//GO(pango_context_get_type, 
//GO(pango_context_list_families, 
//GO(pango_context_load_font, 
//GO(pango_context_load_fontset, 
//GO(pango_context_new, 
//GO(pango_context_set_base_dir, 
//GO(pango_context_set_base_gravity, 
//GO(pango_context_set_font_description, 
//GO(pango_context_set_font_map, 
//GO(pango_context_set_gravity_hint, 
//GO(pango_context_set_language, 
//GO(pango_context_set_matrix, 
//GO(pango_coverage_copy, 
//GO(pango_coverage_from_bytes, 
//GO(pango_coverage_get, 
//GO(pango_coverage_level_get_type, 
//GO(pango_coverage_max, 
//GO(pango_coverage_new, 
//GO(pango_coverage_ref, 
//GO(pango_coverage_set, 
//GO(pango_coverage_to_bytes, 
//GO(pango_coverage_unref, 
//GO(pango_default_break, 
//GO(pango_direction_get_type, 
//GO(pango_ellipsize_mode_get_type, 
//GO(pango_engine_get_type, 
//GO(pango_engine_lang_get_type, 
//GO(pango_engine_shape_get_type, 
//GO(pango_extents_to_pixels, 
//GO(pango_find_base_dir, 
//GO(pango_find_map, 
//GO(pango_find_paragraph_boundary, 
//GO(pango_font_describe, 
GO(pango_font_describe_with_absolute_size, pFp)
GO(pango_font_description_better_match, iFppp)
GO(pango_font_description_copy, pFp)
GO(pango_font_description_copy_static, pFp)
GO(pango_font_description_equal, iFpp)
GO(pango_font_description_free, vFp)
GO(pango_font_description_from_string, pFp)
GO(pango_font_description_get_family, pFp)
GO(pango_font_description_get_gravity, iFp)
GO(pango_font_description_get_set_fields, iFp)
GO(pango_font_description_get_size, iFp)
GO(pango_font_description_get_size_is_absolute, iFp)
GO(pango_font_description_get_stretch, iFp)
GO(pango_font_description_get_style, iFp)
GO(pango_font_description_get_type, iFv)
GO(pango_font_description_get_variant, vFpi)
GO(pango_font_description_get_weight, iFp)
GO(pango_font_description_hash, uFp)
GO(pango_font_description_merge, vFppi)
GO(pango_font_description_merge_static, vFppi)
GO(pango_font_description_new, pFv)
GO(pango_font_description_set_absolute_size, vFpd)
GO(pango_font_description_set_family, vFpp)
GO(pango_font_description_set_family_static, vFpp)
GO(pango_font_description_set_gravity, vFpi)
GO(pango_font_description_set_size, vFpi)
GO(pango_font_description_set_stretch, vFpi)
GO(pango_font_description_set_style, vFpi)
GO(pango_font_description_set_variant, vFpi)
GO(pango_font_description_set_weight, vFpi)
GO(pango_font_descriptions_free, vFpi)
GO(pango_font_description_to_filename, pFp)
GO(pango_font_description_to_string, pFp)
GO(pango_font_description_unset_fields, vFpi)
GO(pango_font_face_describe, pFp)
GO(pango_font_face_get_face_name, pFp)
GO(pango_font_face_get_type, iFv)
GO(pango_font_face_is_synthesized, iFp)
GO(pango_font_face_list_sizes, vFppp)
GO(pango_font_family_get_name, pFp)
GO(pango_font_family_get_type, iFv)
GO(pango_font_family_is_monospace, iFp)
GO(pango_font_family_list_faces, vFppp)
GO(pango_font_find_shaper, pFppu)
GO(pango_font_get_coverage, pFpp)
GO(pango_font_get_font_map, pFp)
GO(pango_font_get_glyph_extents, vFpppp)
GO(pango_font_get_metrics, pFpp)
GO(pango_font_get_type, iFv)
GO(pango_font_map_create_context, pFp)
GO(pango_font_map_get_serial, uFp)
//GO(pango_font_map_get_shape_engine_type, 
GO(pango_font_map_get_type, iFv)
GO(pango_font_map_list_families, vFppp)
GO(pango_font_map_load_font, pFppp)
GO(pango_font_map_load_fontset, pFpppp)
GO(pango_font_mask_get_type, iFv)
GO(pango_font_metrics_get_approximate_char_width, iFp)
GO(pango_font_metrics_get_approximate_digit_width, iFp)
GO(pango_font_metrics_get_ascent, iFp)
GO(pango_font_metrics_get_descent, iFp)
GO(pango_font_metrics_get_strikethrough_position, iFp)
GO(pango_font_metrics_get_strikethrough_thickness, iFp)
GO(pango_font_metrics_get_type, iFv)
GO(pango_font_metrics_get_underline_position, iFp)
GO(pango_font_metrics_get_underline_thickness, iFp)
//GO(pango_font_metrics_new, 
GO(pango_font_metrics_ref, pFp)
GO(pango_font_metrics_unref, vFp)
//GO(pango_fontset_foreach, 
GO(pango_fontset_get_font, pFpu)
GO(pango_fontset_get_metrics, pFp)
//GO(pango_fontset_get_type, 
//GO(pango_fontset_simple_append, 
//GO(pango_fontset_simple_get_type, 
//GO(pango_fontset_simple_new, 
//GO(pango_fontset_simple_size, 
//GO(pango_get_lib_subdirectory, 
//GO(pango_get_log_attrs, 
//GO(pango_get_mirror_char, 
//GO(pango_get_sysconf_subdirectory, 
//GO(pango_glyph_item_apply_attrs, 
//GO(pango_glyph_item_copy, 
//GO(pango_glyph_item_free, 
//GO(pango_glyph_item_get_logical_widths, 
//GO(pango_glyph_item_get_type, 
//GO(pango_glyph_item_iter_copy, 
//GO(pango_glyph_item_iter_free, 
//GO(pango_glyph_item_iter_get_type, 
//GO(pango_glyph_item_iter_init_end, 
//GO(pango_glyph_item_iter_init_start, 
//GO(pango_glyph_item_iter_next_cluster, 
//GO(pango_glyph_item_iter_prev_cluster, 
//GO(pango_glyph_item_letter_space, 
//GO(pango_glyph_item_split, 
//GO(pango_glyph_string_copy, 
//GO(pango_glyph_string_extents, 
//GO(pango_glyph_string_extents_range, 
//GO(pango_glyph_string_free, 
//GO(pango_glyph_string_get_logical_widths, 
//GO(pango_glyph_string_get_type, 
//GO(pango_glyph_string_get_width, 
//GO(pango_glyph_string_index_to_x, 
//GO(pango_glyph_string_new, 
//GO(pango_glyph_string_set_size, 
//GO(pango_glyph_string_x_to_index, 
//GO(pango_gravity_get_for_matrix, 
//GO(pango_gravity_get_for_script, 
//GO(pango_gravity_get_for_script_and_width, 
//GO(pango_gravity_get_type, 
//GO(pango_gravity_hint_get_type, 
//GO(pango_gravity_to_rotation, 
//GO(pango_is_zero_width, 
//GO(pango_item_copy, 
//GO(pango_item_free, 
//GO(pango_item_get_type, 
//GO(pango_itemize, 
//GO(pango_itemize_with_base_dir, 
//GO(pango_item_new, 
//GO(pango_item_split, 
//GO(pango_language_from_string, 
//GO(pango_language_get_default, 
//GO(pango_language_get_sample_string, 
//GO(pango_language_get_scripts, 
//GO(pango_language_get_type, 
//GO(pango_language_includes_script, 
//GO(pango_language_matches, 
//GO(pango_language_to_string, 
//GO(pango_layout_context_changed, 
//GO(pango_layout_copy, 
//GO(pango_layout_get_alignment, 
//GO(pango_layout_get_attributes, 
//GO(pango_layout_get_auto_dir, 
//GO(pango_layout_get_baseline, 
//GO(pango_layout_get_character_count, 
//GO(pango_layout_get_context, 
//GO(pango_layout_get_cursor_pos, 
//GO(pango_layout_get_ellipsize, 
//GO(pango_layout_get_extents, 
//GO(pango_layout_get_font_description, 
//GO(pango_layout_get_height, 
//GO(pango_layout_get_indent, 
//GO(pango_layout_get_iter, 
//GO(pango_layout_get_justify, 
//GO(pango_layout_get_line, 
//GO(pango_layout_get_line_count, 
//GO(pango_layout_get_line_readonly, 
//GO(pango_layout_get_lines, 
//GO(pango_layout_get_lines_readonly, 
//GO(pango_layout_get_log_attrs, 
//GO(pango_layout_get_log_attrs_readonly, 
//GO(pango_layout_get_pixel_extents, 
//GO(pango_layout_get_pixel_size, 
//GO(pango_layout_get_serial, 
//GO(pango_layout_get_single_paragraph_mode, 
//GO(pango_layout_get_size, 
//GO(pango_layout_get_spacing, 
//GO(pango_layout_get_tabs, 
//GO(pango_layout_get_text, 
//GO(pango_layout_get_type, 
//GO(pango_layout_get_unknown_glyphs_count, 
//GO(pango_layout_get_width, 
//GO(pango_layout_get_wrap, 
//GO(pango_layout_index_to_line_x, 
//GO(pango_layout_index_to_pos, 
//GO(pango_layout_is_ellipsized, 
//GO(pango_layout_is_wrapped, 
//GO(pango_layout_iter_at_last_line, 
//GO(pango_layout_iter_copy, 
//GO(pango_layout_iter_free, 
//GO(pango_layout_iter_get_baseline, 
//GO(pango_layout_iter_get_char_extents, 
//GO(pango_layout_iter_get_cluster_extents, 
//GO(pango_layout_iter_get_index, 
//GO(pango_layout_iter_get_layout, 
//GO(pango_layout_iter_get_layout_extents, 
//GO(pango_layout_iter_get_line, 
//GO(pango_layout_iter_get_line_extents, 
//GO(pango_layout_iter_get_line_readonly, 
//GO(pango_layout_iter_get_line_yrange, 
//GO(pango_layout_iter_get_run, 
//GO(pango_layout_iter_get_run_extents, 
//GO(pango_layout_iter_get_run_readonly, 
//GO(pango_layout_iter_get_type, 
//GO(pango_layout_iter_next_char, 
//GO(pango_layout_iter_next_cluster, 
//GO(pango_layout_iter_next_line, 
//GO(pango_layout_iter_next_run, 
//GO(pango_layout_line_get_extents, 
//GO(pango_layout_line_get_pixel_extents, 
//GO(pango_layout_line_get_type, 
//GO(pango_layout_line_get_x_ranges, 
//GO(pango_layout_line_index_to_x, 
//GO(pango_layout_line_ref, 
//GO(pango_layout_line_unref, 
//GO(pango_layout_line_x_to_index, 
//GO(pango_layout_move_cursor_visually, 
//GO(pango_layout_new, 
//GO(pango_layout_set_alignment, 
//GO(pango_layout_set_attributes, 
//GO(pango_layout_set_auto_dir, 
//GO(pango_layout_set_ellipsize, 
//GO(pango_layout_set_font_description, 
//GO(pango_layout_set_height, 
//GO(pango_layout_set_indent, 
//GO(pango_layout_set_justify, 
//GO(pango_layout_set_markup, 
//GO(pango_layout_set_markup_with_accel, 
//GO(pango_layout_set_single_paragraph_mode, 
//GO(pango_layout_set_spacing, 
//GO(pango_layout_set_tabs, 
//GO(pango_layout_set_text, 
//GO(pango_layout_set_width, 
//GO(pango_layout_set_wrap, 
//GO(pango_layout_xy_to_index, 
//GO(pango_log2vis_get_embedding_levels, 
//GO(pango_lookup_aliases, 
//GO(pango_map_get_engine, 
//GO(pango_map_get_engines, 
//GO(pango_markup_parser_finish, 
//GO(pango_markup_parser_new, 
//GO(pango_matrix_concat, 
//GO(pango_matrix_copy, 
//GO(pango_matrix_free, 
//GO(pango_matrix_get_font_scale_factor, 
//GO(pango_matrix_get_type, 
//GO(pango_matrix_rotate, 
//GO(pango_matrix_scale, 
//GO(pango_matrix_transform_distance, 
//GO(pango_matrix_transform_pixel_rectangle, 
//GO(pango_matrix_transform_point, 
//GO(pango_matrix_transform_rectangle, 
//GO(pango_matrix_translate, 
//GO(pango_module_register, 
//GO(pango_parse_enum, 
//GO(pango_parse_markup, 
//GO(pango_parse_stretch, 
//GO(pango_parse_style, 
//GO(pango_parse_variant, 
//GO(pango_parse_weight, 
//GO(pango_quantize_line_geometry, 
//GO(pango_read_line, 
//GO(pango_renderer_activate, 
//GO(pango_renderer_deactivate, 
//GO(pango_renderer_draw_error_underline, 
//GO(pango_renderer_draw_glyph, 
//GO(pango_renderer_draw_glyph_item, 
//GO(pango_renderer_draw_glyphs, 
//GO(pango_renderer_draw_layout, 
//GO(pango_renderer_draw_layout_line, 
//GO(pango_renderer_draw_rectangle, 
//GO(pango_renderer_draw_trapezoid, 
//GO(pango_renderer_get_color, 
//GO(pango_renderer_get_layout, 
//GO(pango_renderer_get_layout_line, 
//GO(pango_renderer_get_matrix, 
//GO(pango_renderer_get_type, 
//GO(pango_renderer_part_changed, 
//GO(pango_renderer_set_color, 
//GO(pango_renderer_set_matrix, 
//GO(pango_render_part_get_type, 
//GO(pango_reorder_items, 
//GO(pango_scan_int, 
//GO(pango_scan_string, 
//GO(pango_scan_word, 
//GO(pango_script_for_unichar, 
//GO(pango_script_get_sample_language, 
//GO(pango_script_get_type, 
//GO(pango_script_iter_free, 
//GO(pango_script_iter_get_range, 
//GO(pango_script_iter_new, 
//GO(pango_script_iter_next, 
//GO(pango_shape, 
//GO(pango_shape_full, 
//GO(pango_skip_space, 
//GO(pango_split_file_list, 
//GO(pango_stretch_get_type, 
//GO(pango_style_get_type, 
//GO(pango_tab_align_get_type, 
//GO(pango_tab_array_copy, 
//GO(pango_tab_array_free, 
//GO(pango_tab_array_get_positions_in_pixels, 
//GO(pango_tab_array_get_size, 
//GO(pango_tab_array_get_tab, 
//GO(pango_tab_array_get_tabs, 
//GO(pango_tab_array_get_type, 
//GO(pango_tab_array_new, 
//GO(pango_tab_array_new_with_positions, 
//GO(pango_tab_array_resize, 
//GO(pango_tab_array_set_tab, 
//GO(pango_trim_string, 
//GO(pango_underline_get_type, 
//GO(pango_unichar_direction, 
//GO(pango_units_from_double, 
//GO(pango_units_to_double, 
//GO(pango_variant_get_type, 
//GO(pango_version, 
//GO(pango_version_check, 
//GO(pango_version_string, 
//GO(pango_weight_get_type, 
//GO(pango_wrap_mode_get_type, 
