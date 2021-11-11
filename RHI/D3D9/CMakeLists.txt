include(${PROJECT_SOURCE_DIR}/cmake/DirectX.cmake)
set(this D3D9RHI)

if(DIRECTX_FOUND)

add_library(${this} STATIC
D3D9GraphicsManager.cpp
)
target_include_directories(${this} PRIVATE  ${PROJECT_SOURCE_DIR}/Platform/Windows)
target_include_directories(${this} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${DIRECTX_INCLUDE_DIR})

#link_directories(${DIRECTX_LIBRARY_DIR});
target_link_libraries(${this}
${DIRECTX_LIBRARY_DIR}/d3d9.lib
${DIRECTX_LIBRARY_DIR}/d3dx10.lib
${DIRECTX_LIBRARY_DIR}/d3dx9.lib
${DIRECTX_LIBRARY_DIR}/dxerr.lib
${DIRECTX_LIBRARY_DIR}/dxguid.lib
comctl32.lib
winmm.lib
Common
WindowsApplication
)
endif()

set_target_properties(${this} PROPERTIES FOLDER RHI)