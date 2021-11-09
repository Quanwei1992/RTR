set(this Framework)

ucm_add_dirs(Common Interface GeomMath TO sources RECURSIVE)

add_library(${this} OBJECT ${sources})
target_include_directories(${this} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Interface ${CMAKE_CURRENT_SOURCE_DIR}/Common)

# ispc
set(ISPC_ADDRESSING 64)
include(${CMAKE_SOURCE_DIR}/cmake/ispc.cmake)
set(SOURCES_ISPC 
    GeomMath/ispc/CrossProduct.ispc
    GeomMath/ispc/DotProduct.ispc
    GeomMath/ispc/MulByElement.ispc
    GeomMath/ispc/MulByElement.isph
    GeomMath/ispc/Transpose.ispc
)
source_group(ispc FILES ${SOURCES_ISPC})
ispc_target_add_sources(${this} ${SOURCES_ISPC})
