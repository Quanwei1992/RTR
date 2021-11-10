set(this AssetLoaderTest)
add_executable(${this} test.cpp)
target_link_libraries(${this} PRIVATE Common)
set_target_properties(${this} PROPERTIES FOLDER Tests)


copy_assets_to(${this})