set(this Interface)

ucm_add_dirs(include TO sources)
add_library(${this} INTERFACE ${sources})

target_include_directories(${this} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(${this} PROPERTIES FOLDER Framework)