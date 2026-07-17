// SPDX-License-Identifier: MIT
// SPDX-CopyRightText: 2026 Badge.Team

#include "asp/orientation.h"

asp_err_t asp_orientation_enable_gyroscope(void) {
    // TODO: implement emulator orientation sensor backend.
    return ASP_ERR_UNSUPPORTED;
}

asp_err_t asp_orientation_disable_gyroscope(void) {
    // TODO: implement emulator orientation sensor backend.
    return ASP_ERR_UNSUPPORTED;
}

asp_err_t asp_orientation_enable_accelerometer(void) {
    // TODO: implement emulator orientation sensor backend.
    return ASP_ERR_UNSUPPORTED;
}

asp_err_t asp_orientation_disable_accelerometer(void) {
    // TODO: implement emulator orientation sensor backend.
    return ASP_ERR_UNSUPPORTED;
}

asp_err_t asp_orientation_get(bool* out_gyro_ready, bool* out_accel_ready,
                              float* out_gyro_x, float* out_gyro_y, float* out_gyro_z,
                              float* out_accel_x, float* out_accel_y, float* out_accel_z) {
    // TODO: implement emulator orientation sensor backend.
    (void)out_gyro_x;
    (void)out_gyro_y;
    (void)out_gyro_z;
    (void)out_accel_x;
    (void)out_accel_y;
    (void)out_accel_z;
    if (out_gyro_ready) {
        *out_gyro_ready = false;
    }
    if (out_accel_ready) {
        *out_accel_ready = false;
    }
    return ASP_ERR_UNSUPPORTED;
}
