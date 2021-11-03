include(${PROJECT_SOURCE_DIR}/cmake/DirectX.cmake)

if(DIRECTX_FOUND)

add_library(D3D9RHI
D3D9GraphicsManager.cpp
)
target_include_directories(D3D9RHI PUBLIC ${DIRECTX_INCLUDE_DIR})

#link_directories(${DIRECTX_LIBRARY_DIR});
target_link_libraries(D3D9RHI
${DIRECTX_LIBRARY_DIR}/d3d9.lib
${DIRECTX_LIBRARY_DIR}/d3dx10.lib
${DIRECTX_LIBRARY_DIR}/d3dx9.lib
${DIRECTX_LIBRARY_DIR}/dxerr.lib
${DIRECTX_LIBRARY_DIR}/dxguid.lib
comctl32.lib
winmm.lib
)
endif()