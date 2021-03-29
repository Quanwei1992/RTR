cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 17)
include(cmake/ucm.cmake)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(RTR)



add_subdirectory(third_part/glad)
add_subdirectory(third_part/glfw)
add_subdirectory(third_part/stb)
add_subdirectory(third_part/glm)
add_subdirectory(third_part/assimp)


SET_TARGET_PROPERTIES (glad PROPERTIES FOLDER ThirdPart)
SET_TARGET_PROPERTIES (glfw PROPERTIES FOLDER ThirdPart)
SET_TARGET_PROPERTIES (stb PROPERTIES FOLDER ThirdPart)
SET_TARGET_PROPERTIES (assimp PROPERTIES FOLDER ThirdPart)
SET_TARGET_PROPERTIES (assimp_cmd PROPERTIES FOLDER ThirdPart)

#SET_TARGET_PROPERTIES (glm_shared PROPERTIES FOLDER ThirdPart)
SET_TARGET_PROPERTIES (IrrXML PROPERTIES FOLDER ThirdPart)
SET_TARGET_PROPERTIES (uninstall PROPERTIES FOLDER ThirdPart)
SET_TARGET_PROPERTIES (unit PROPERTIES FOLDER ThirdPart)
SET_TARGET_PROPERTIES (UpdateAssimpLibsDebugSymbolsAndDLLs PROPERTIES FOLDER ThirdPart)
SET_TARGET_PROPERTIES (zlib PROPERTIES FOLDER ThirdPart)
SET_TARGET_PROPERTIES (zlibstatic PROPERTIES FOLDER ThirdPart)


ucm_dir_list("demos" demos)

foreach(X IN LISTS demos)
    message(STATUS "Add demo ${X}")
    add_subdirectory(demos/${X})
endforeach()