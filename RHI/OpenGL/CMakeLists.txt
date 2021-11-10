set(this OpenGLRHI)

add_library(${this}
OpenGLGraphicsManager.cpp
${PROJECT_SOURCE_DIR}/External/GL/src/glad.c)

target_include_directories(${this} PRIVATE "${PROJECT_SOURCE_DIR}/External/GL/include")

set_target_properties(${this} PROPERTIES FOLDER RHI)