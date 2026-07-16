
// SPDX-License-Identiefier: MIT
// SPDX-CopyRightText: 2025 Renze Nicolai
// SPDX-CopyRightText: 2025 Badge.Team

#include "asp/device.h"
#include <string.h>

asp_err_t asp_device_get_name(char* output, uint8_t buffer_length) {
    // TODO: implement emulator device info backend.
    if (!output) {
        return ASP_ERR_PARAM;
    }
    static char const name[] = "Emulator";
    if (sizeof(name) > buffer_length) {
        return ASP_ERR_PARAM;
    }
    memcpy(output, name, sizeof(name));
    return ASP_OK;
}

asp_err_t asp_device_get_manufacturer(char* output, uint8_t buffer_length) {
    // TODO: implement emulator device info backend.
    if (!output) {
        return ASP_ERR_PARAM;
    }
    static char const name[] = "Badge.Team";
    if (sizeof(name) > buffer_length) {
        return ASP_ERR_PARAM;
    }
    memcpy(output, name, sizeof(name));
    return ASP_OK;
}
