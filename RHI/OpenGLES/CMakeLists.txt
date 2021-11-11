set(this OpenGLESRHI)

add_library(${this} STATIC
OpenGLESGraphicsManager.cpp)

target_include_directories(${this} PRIVATE "${PROJECT_SOURCE_DIR}/External/GLES/include")
target_link_libraries(${this} PUBLIC Common)
set_target_properties(${this} PROPERTIES FOLDER RHI)