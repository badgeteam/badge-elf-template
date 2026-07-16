// SPDX-License-Identifier: MIT
// SPDX-CopyrightText: 2026 Rene Schickbauer

#pragma once

#include <stdbool.h>
#include <stdint.h>
#include "asp/err.h"

#ifdef __cplusplus
extern "C" {
#endif

// Get the number of RGB LEDs available on the device.
uint32_t asp_led_get_count(void);

// Set overall LED brightness (0-100%).
asp_err_t asp_led_set_brightness(uint8_t percentage);

// Get overall LED brightness (0-100%).
asp_err_t asp_led_get_brightness(uint8_t* out_percentage);

// Set LED mode (true = automatic/system control, false = manual control).
asp_err_t asp_led_set_mode(bool automatic);

// Get current LED mode.
asp_err_t asp_led_get_mode(bool* out_automatic);

// Set a single LED pixel color using 0xRRGGBB format.
// Does not update hardware until asp_led_send() is called.
asp_err_t asp_led_set_pixel(uint32_t index, uint32_t color);

// Set a single LED pixel color using RGB components.
// Does not update hardware until asp_led_send() is called.
asp_err_t asp_led_set_pixel_rgb(uint32_t index, uint8_t red, uint8_t green, uint8_t blue);

// Set a single LED pixel color using HSV.
// hue: 0-65535 (maps to 0-360 degrees)
// saturation: 0-255
// value: 0-255
// Does not update hardware until asp_led_send() is called.
asp_err_t asp_led_set_pixel_hsv(uint32_t index, uint16_t hue, uint8_t saturation, uint8_t value);

// Send LED data to hardware.
asp_err_t asp_led_send(void);

// Clear all LEDs (sets all to black and sends to hardware).
asp_err_t asp_led_clear(void);

#ifdef __cplusplus
}
#endif
