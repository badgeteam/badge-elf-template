// SPDX-License-Identifier: MIT
// SPDX-CopyRightText: 2026 Badge.Team

#include "asp/power.h"

asp_err_t asp_power_get_battery_info(asp_battery_info_t* out_info) {
    // TODO: implement emulator power backend.
    (void)out_info;
    return ASP_ERR_UNSUPPORTED;
}

asp_err_t asp_power_get_system_voltage(uint16_t* out_millivolt) {
    // TODO: implement emulator power backend.
    (void)out_millivolt;
    return ASP_ERR_UNSUPPORTED;
}

asp_err_t asp_power_get_battery_voltage(uint16_t* out_millivolt) {
    // TODO: implement emulator power backend.
    (void)out_millivolt;
    return ASP_ERR_UNSUPPORTED;
}

asp_err_t asp_power_get_input_voltage(uint16_t* out_millivolt) {
    // TODO: implement emulator power backend.
    (void)out_millivolt;
    return ASP_ERR_UNSUPPORTED;
}

asp_err_t asp_power_get_charging_config(bool* out_disabled, uint16_t* out_current_ma) {
    // TODO: implement emulator power backend.
    (void)out_disabled;
    (void)out_current_ma;
    return ASP_ERR_UNSUPPORTED;
}

asp_err_t asp_power_set_charging(bool disable, uint16_t current_ma) {
    // TODO: implement emulator power backend.
    (void)disable;
    (void)current_ma;
    return ASP_ERR_UNSUPPORTED;
}

asp_err_t asp_power_get_usb_host_boost_enabled(bool* out_enabled) {
    // TODO: implement emulator power backend.
    (void)out_enabled;
    return ASP_ERR_UNSUPPORTED;
}

asp_err_t asp_power_set_usb_host_boost_enabled(bool enable) {
    // TODO: implement emulator power backend.
    (void)enable;
    return ASP_ERR_UNSUPPORTED;
}
