// SPDX-License-Identifier: MIT
// SPDX-CopyRightText: 2026 Rene Schickbauer

#pragma once

#include <stdbool.h>
#include <stdint.h>
#include "asp/err.h"

/// @brief Battery information structure
typedef struct {
    bool        power_supply_available;    ///< Power supply attached
    bool        battery_available;         ///< Battery installed
    bool        charging_disabled;         ///< Charging disabled
    bool        battery_charging;          ///< Currently charging
    uint16_t    voltage;                   ///< Battery voltage (mV)
    uint16_t    charging_target_voltage;   ///< Target voltage (mV)
    uint16_t    maximum_charging_current;  ///< Max charging current (mA)
    uint16_t    current_charging_current;  ///< Current charging current (mA)
    uint8_t     remaining_percentage;      ///< Battery percentage (0-100)
} asp_battery_info_t;

/// @brief Get comprehensive battery information
/// @param[out] out_info Pointer to receive battery information
/// @return Error code
asp_err_t asp_power_get_battery_info(asp_battery_info_t* out_info);

/// @brief Get system voltage (main power rail)
/// @param[out] out_millivolt Pointer to receive voltage in millivolts
/// @return Error code
asp_err_t asp_power_get_system_voltage(uint16_t* out_millivolt);

/// @brief Get battery voltage
/// @param[out] out_millivolt Pointer to receive voltage in millivolts
/// @return Error code
asp_err_t asp_power_get_battery_voltage(uint16_t* out_millivolt);

/// @brief Get charger input voltage
/// @param[out] out_millivolt Pointer to receive voltage in millivolts
/// @return Error code
asp_err_t asp_power_get_input_voltage(uint16_t* out_millivolt);

/// @brief Get charging configuration
/// @param[out] out_disabled Pointer to receive disabled state
/// @param[out] out_current_ma Pointer to receive current limit in mA
/// @return Error code
asp_err_t asp_power_get_charging_config(bool* out_disabled, uint16_t* out_current_ma);

/// @brief Configure charging
/// @param disable Set to true to disable charging
/// @param current_ma Charging current limit in mA
/// @return Error code
asp_err_t asp_power_set_charging(bool disable, uint16_t current_ma);

/// @brief Get USB host boost status
/// @param[out] out_enabled Pointer to receive enabled state
/// @return Error code
asp_err_t asp_power_get_usb_host_boost_enabled(bool* out_enabled);

/// @brief Set USB host boost
/// @param enable Set to true to enable USB host boost
/// @return Error code
asp_err_t asp_power_set_usb_host_boost_enabled(bool enable);
