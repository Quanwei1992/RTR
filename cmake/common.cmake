macro(copy_assets_to target)
add_custom_command(TARGET ${target} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/Asset/ ${CMAKE_CURRENT_BINARY_DIR}/Asset/
                       COMMENT "Copying assets to output directory.")
endmacro()