cmake_minimum_required (VERSION 3.1)
set_property(GLOBAL PROPERTY USE_FOLDERS ON) 
include(cmake/ucm.cmake)
include(cmake/common.cmake)
ucm_print_flags()

project (RTR)

if(WIN32)
    set(RTR_RHI "D3D9" CACHE STRING "RHI")
    set_property(CACHE RTR_RHI PROPERTY STRINGS D3D9 D3D12 OPENGL OPENGLES EMPTY)
elseif(APPLE)
    set(RTR_RHI "OPENGL" CACHE STRING "RHI")
    set_property(CACHE RTR_RHI PROPERTY STRINGS OPENGL EMPTY) 
endif()


add_subdirectory(Framework)
add_subdirectory(Platform)
add_subdirectory(RHI/${RTR_RHI})
add_subdirectory(Tests)


