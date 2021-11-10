set(this TextureLoadTest)

add_executable(${this} TextureLoadTest.cpp)
target_link_libraries(${this} WindowsApplication Codec Common D2DRHI d2d1)
set_target_properties(${this} PROPERTIES FOLDER Tests)
rtr_copy_assets_to(${this})