set(this SceneObjectTest)
add_executable(${this} test.cpp)
target_link_libraries(${this} PRIVATE Common Guid)
set_target_properties(${this} PROPERTIES FOLDER Tests)