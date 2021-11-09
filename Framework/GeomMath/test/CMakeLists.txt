set(this GeomMathTest)
add_executable(${this} test.cpp)
target_link_libraries(${this} PRIVATE GeomMath)
set_target_properties(${this} PROPERTIES FOLDER Tests)