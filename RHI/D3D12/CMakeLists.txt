set(this D3D12RHI)

add_library(${this} OBJECT
    D3D12GraphicsManager.cpp
)
target_include_directories(${this} PRIVATE  ${PROJECT_SOURCE_DIR}/Platform/Windows)
target_include_directories(${this} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${this} PRIVATE Common WindowsApplication)

set_target_properties(${this} PROPERTIES FOLDER RHI)