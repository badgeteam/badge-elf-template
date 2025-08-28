
// SPDX-License-Identiefier: MIT
// SPDX-CopyRightText: 2025 Renze Nicolai
// SPDX-CopyRightText: 2025 Badge.Team

// See:
// https://github.com/badgeteam/esp32-component-badge-bsp/blob/dc35e4bc3f75c46d48597ae182b2b298d3d16055/bsp/device.h

#pragma once

#include <stdbool.h>
#include <stdint.h>
#include "asp/err.h"

/// @brief Get the name of the device as a string
/// @details Returns the name as a null terminated string
/// @param[out] output Pointer to buffer to which the name string gets copied
/// @param[in] buffer_length Length of the output buffer
/// @return Error code
///          - ASP_OK if the output string fits in the buffer
///          - ASP_ERR_PARAM if the output pointer is NULL
asp_err_t asp_device_get_name(char* output, uint8_t buffer_length);

/// @brief Get the name of the manufacturer as a string
/// @details Returns the name as a null terminated string
/// @param[out] output Pointer to buffer to which the name string gets copied
/// @param[in] buffer_length Length of the output buffer
/// @return Error code
///          - ASP_OK if the output string fits in the buffer
///          - ASP_ERR_PARAM if the output pointer is NULL
asp_err_t asp_device_get_manufacturer(char* output, uint8_t buffer_length);
