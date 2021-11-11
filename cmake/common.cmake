macro(rtr_copy_assets_to target)
add_custom_command(TARGET ${target} PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/Asset/ ${CMAKE_CURRENT_BINARY_DIR}/Asset/
                       COMMENT "Copying assets to output directory.")
endmacro()


macro(rtr_add_static_module target)
ucm_add_dirs(include sources TO sources)
add_library(${target} STATIC ${sources})
target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
endmacro()

macro(rtr_add_interface_module target)
ucm_add_dirs(include TO sources)
add_library(${target} INTERFACE ${sources})
target_include_directories(${target} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
endmacro()

macro(rtr_set_target_floder target floder)
set_target_properties(${target} PROPERTIES FOLDER ${floder})
endmacro()
