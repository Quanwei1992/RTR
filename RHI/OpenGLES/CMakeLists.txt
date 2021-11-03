add_library(OpenGLESRHI
OpenGLESGraphicsManager.cpp)

target_include_directories(OpenGLESRHI PRIVATE "${PROJECT_SOURCE_DIR}/External/GLES/include")