
set(this 0_HelloWorld)

add_executable(${this} main.cpp)
target_link_libraries(${this} PRIVATE framework)
install(TARGETS ${this} DESTINATION ${CMAKE_HOME_DIRECTORY}/output)
