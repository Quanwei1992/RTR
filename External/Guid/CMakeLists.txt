
set(this Guid)
rtr_add_static_module(${this})
rtr_set_target_floder(${this} External)
if(WIN32)
    target_compile_definitions(${this} PUBLIC GUID_WINDOWS)
endif()