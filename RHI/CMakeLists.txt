add_subdirectory(Empty)
add_subdirectory(OpenGL)
add_subdirectory(OpenGLES)
IF(${WIN32})
# Windows specific code
add_subdirectory(D3D)
ENDIF(${WIN32})