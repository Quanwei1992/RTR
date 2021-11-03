add_executable(app_d3d9 WindowsApplication.cpp D3D9Application.cpp)
target_link_libraries(app_d3d9 Common D3D9RHI)

add_executable(app_opengl
WindowsApplication.cpp
OpenGLApplication.cpp
${PROJECT_SOURCE_DIR}/External/GL/src/glad_wgl.c)

target_link_libraries(app_opengl Common OpenGLRHI opengl32)
target_include_directories(app_opengl PRIVATE "${PROJECT_SOURCE_DIR}/External/GL/include")


add_executable(app_opengl_es
WindowsApplication.cpp
OpenGLESApplication.cpp)

target_link_libraries(app_opengl_es
Common
OpenGLESRHI
"${PROJECT_SOURCE_DIR}/External/GLES/lib/x86/libEGL.lib"
"${PROJECT_SOURCE_DIR}/External/GLES/lib/x86/libGLESv2.lib"
)
target_include_directories(app_opengl_es PRIVATE "${PROJECT_SOURCE_DIR}/External/GLES/include")