// SPDX-License-Identifier: MIT
// SPDX-CopyRightText: 2026 Rene Schickbauer

#pragma once

#include <stdbool.h>
#include "asp/err.h"

/// @brief Enable the gyroscope
asp_err_t asp_orientation_enable_gyroscope(void);

/// @brief Disable the gyroscope
asp_err_t asp_orientation_disable_gyroscope(void);

/// @brief Enable the accelerometer
asp_err_t asp_orientation_enable_accelerometer(void);

/// @brief Disable the accelerometer
asp_err_t asp_orientation_disable_accelerometer(void);

/// @brief Get current orientation sensor data
/// @param[out] out_gyro_ready  true if gyroscope data is valid
/// @param[out] out_accel_ready true if accelerometer data is valid
/// @param[out] out_gyro_x  Gyroscope X axis (degrees per second)
/// @param[out] out_gyro_y  Gyroscope Y axis (degrees per second)
/// @param[out] out_gyro_z  Gyroscope Z axis (degrees per second)
/// @param[out] out_accel_x Accelerometer X axis (m/s²)
/// @param[out] out_accel_y Accelerometer Y axis (m/s²)
/// @param[out] out_accel_z Accelerometer Z axis (m/s²)
asp_err_t asp_orientation_get(bool* out_gyro_ready, bool* out_accel_ready,
                              float* out_gyro_x, float* out_gyro_y, float* out_gyro_z,
                              float* out_accel_x, float* out_accel_y, float* out_accel_z);
