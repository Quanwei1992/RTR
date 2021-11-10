set(this "Application")

add_subdirectory(WindowsApplication)

if(RTR_RHI STREQUAL "D3D9")

    add_executable(${this} D3D9Application.cpp)
    target_link_libraries(${this} Common WindowsApplication D3D9RHI)
elseif(RTR_RHI STREQUAL "D3D12")

    add_executable(${this} D3D12Application.cpp)
    target_link_libraries(${this} Common WindowsApplication D3D12RHI d3d12 dxgi d3dcompiler)

elseif(RTR_RHI STREQUAL "OPENGL")

    add_executable(${this}
    main.cpp
    OpenGLApplication.cpp
    ${PROJECT_SOURCE_DIR}/External/GL/src/glad_wgl.c)
    target_link_libraries(${this} Common WindowsApplication OpenGLRHI opengl32)
    target_include_directories(${this} PRIVATE "${PROJECT_SOURCE_DIR}/External/GL/include")

elseif(RTR_RHI STREQUAL "OPENGLES")

    add_executable(${this}
    main.cpp
    OpenGLESApplication.cpp)
    target_link_libraries(${this}
    Common
    OpenGLESRHI
    WindowsApplication
    "${PROJECT_SOURCE_DIR}/External/GLES/lib/x86/libEGL.lib"
    "${PROJECT_SOURCE_DIR}/External/GLES/lib/x86/libGLESv2.lib"
    )
    target_include_directories(${this} PRIVATE "${PROJECT_SOURCE_DIR}/External/GLES/include")

endif()






