// SPDX-License-Identifier: MIT
// SPDX-CopyrightText: 2026 Badge.Team

#include "asp/led.h"

uint32_t asp_led_get_count(void) {
    // TODO: implement emulator LED backend.
    return 0;
}

asp_err_t asp_led_set_brightness(uint8_t percentage) {
    // TODO: implement emulator LED backend.
    (void)percentage;
    return ASP_ERR_UNSUPPORTED;
}

asp_err_t asp_led_get_brightness(uint8_t* out_percentage) {
    // TODO: implement emulator LED backend.
    (void)out_percentage;
    return ASP_ERR_UNSUPPORTED;
}

asp_err_t asp_led_set_mode(bool automatic) {
    // TODO: implement emulator LED backend.
    (void)automatic;
    return ASP_ERR_UNSUPPORTED;
}

asp_err_t asp_led_get_mode(bool* out_automatic) {
    // TODO: implement emulator LED backend.
    (void)out_automatic;
    return ASP_ERR_UNSUPPORTED;
}

asp_err_t asp_led_set_pixel(uint32_t index, uint32_t color) {
    // TODO: implement emulator LED backend.
    (void)index;
    (void)color;
    return ASP_ERR_UNSUPPORTED;
}

asp_err_t asp_led_set_pixel_rgb(uint32_t index, uint8_t red, uint8_t green, uint8_t blue) {
    // TODO: implement emulator LED backend.
    (void)index;
    (void)red;
    (void)green;
    (void)blue;
    return ASP_ERR_UNSUPPORTED;
}

asp_err_t asp_led_set_pixel_hsv(uint32_t index, uint16_t hue, uint8_t saturation, uint8_t value) {
    // TODO: implement emulator LED backend.
    (void)index;
    (void)hue;
    (void)saturation;
    (void)value;
    return ASP_ERR_UNSUPPORTED;
}

asp_err_t asp_led_send(void) {
    // TODO: implement emulator LED backend.
    return ASP_ERR_UNSUPPORTED;
}

asp_err_t asp_led_clear(void) {
    // TODO: implement emulator LED backend.
    return ASP_ERR_UNSUPPORTED;
}
