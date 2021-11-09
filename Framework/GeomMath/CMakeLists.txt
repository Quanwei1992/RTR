set(this GeomMath)

ucm_add_dirs(include ispc TO sources ADDITIONAL_EXT ispc)


add_library(${this} STATIC ${sources} )
set_target_properties(${this} PROPERTIES FOLDER Framework)
target_include_directories(${this} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)


# ispc
set(ISPC_ADDRESSING 64)
include(${CMAKE_SOURCE_DIR}/cmake/ispc.cmake)
set(SOURCES_ISPC 
    ispc/AddByElement.ispc
    ispc/CrossProduct.ispc
    ispc/DotProduct.ispc
    ispc/MulByElement.ispc
    ispc/Normalize.ispc
    ispc/SubByElement.ispc
    ispc/Transform.ispc
    ispc/Transpose.ispc

)

set_target_properties(${this} PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(${this} PROPERTIES OUTPUT_NAME GeomMath)
ispc_target_add_sources(${this} ${SOURCES_ISPC})

add_subdirectory(test)