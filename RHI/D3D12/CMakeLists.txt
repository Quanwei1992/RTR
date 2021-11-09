add_library(D3D12RHI OBJECT
D3D12GraphicsManager.cpp
)
target_include_directories(D3D12RHI PRIVATE  ${PROJECT_SOURCE_DIR}/Platform/Windows)
target_include_directories(D3D12RHI PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(D3D12RHI PRIVATE Common)
