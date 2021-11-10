macro(rtr_copy_assets_to target)
add_custom_command(TARGET ${target} PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/Asset/ ${CMAKE_CURRENT_BINARY_DIR}/Asset/
                       COMMENT "Copying assets to output directory.")
endmacro()


macro(rtr_add_object_module target)
ucm_add_dirs(include sources TO sources)
add_library(${target} OBJECT ${sources})
target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
endmacro()