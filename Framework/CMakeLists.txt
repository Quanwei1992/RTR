ucm_add_dirs(Common Interface TO sources)

add_library(Framework OBJECT ${sources})
target_include_directories(Framework PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Interface ${CMAKE_CURRENT_SOURCE_DIR}/Common)