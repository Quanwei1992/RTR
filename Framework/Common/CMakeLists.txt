set(this Common)

ucm_add_dirs(include sources TO sources)

add_library(${this} STATIC ${sources})

target_include_directories(${this} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${this} PUBLIC Interface GeomMath Guid)

set_target_properties(${this} PROPERTIES FOLDER Framework)