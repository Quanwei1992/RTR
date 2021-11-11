
set(this D2DRHI)

add_library(${this} STATIC
    D2DGraphicsManager.cpp
)
target_include_directories(${this} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${this} PRIVATE WindowsApplication Common)

set_target_properties(${this} PROPERTIES FOLDER RHI)