
set(this 1_ShadowMap)

add_executable(${this} main.cpp )
target_link_libraries(${this} PRIVATE framework)
install(TARGETS ${this} DESTINATION ${CMAKE_HOME_DIRECTORY}/output)
