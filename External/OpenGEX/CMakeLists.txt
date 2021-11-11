set(this OpenGEX)
rtr_add_static_module(${this})
rtr_set_target_floder(${this} External)
target_link_libraries(${this} PUBLIC OpenDDL)