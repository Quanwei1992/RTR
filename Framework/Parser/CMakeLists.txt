set(this Parser)

rtr_add_static_module(${this})
rtr_set_target_floder(${this} Framework)
target_link_libraries(${this} PUBLIC Interface Common OpenGEX)
