set(this WindowsApplication)
rtr_add_static_module(${this})
target_link_libraries(${this} PUBLIC Common)
set_target_properties(${this} PROPERTIES FOLDER Platform)
