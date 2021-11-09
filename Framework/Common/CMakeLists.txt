set(this Common)

ucm_add_dirs(interface include sources TO sources)

add_library(${this} OBJECT ${sources})

target_include_directories(${this} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/interface)

target_link_libraries(${this} PUBLIC GeomMath)

set_target_properties(${this} PROPERTIES FOLDER Framework)