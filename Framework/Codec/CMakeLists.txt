set(this Codec)

ucm_add_dirs(include sources TO sources)

add_library(${this} OBJECT ${sources})

target_include_directories(${this} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${this} PUBLIC Interface Common)

set_target_properties(${this} PROPERTIES FOLDER Framework)