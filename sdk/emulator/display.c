
// SPDX-License-Identiefier: MIT
// SPDX-CopyRightText: 2025 Badge.Team

#include "asp/display.h"

// Set display brightness.
asp_err_t asp_disp_set_brightness(uint8_t percent) {
    // TODO: implement emulator display backend.
    (void)percent;
    return ASP_ERR_UNSUPPORTED;
}

// Get current display brightness.
asp_err_t asp_disp_get_brightness(uint8_t* percent_out) {
    // TODO: implement emulator display backend.
    (void)percent_out;
    return ASP_ERR_UNSUPPORTED;
}

// Get display parameters of the main display.
asp_err_t asp_disp_get_params(asp_disp_params_t* params_out) {
    // TODO: implement emulator display backend.
    (void)params_out;
    return ASP_ERR_UNSUPPORTED;
}

// Get existing framebuffer of the main display.
asp_err_t asp_disp_get_fb(uint8_t** fb_out) {
    // TODO: implement emulator display backend.
    (void)fb_out;
    return ASP_ERR_UNSUPPORTED;
}

// Get existing PAX buffer of the main display.
asp_err_t asp_disp_get_pax_buf(pax_buf_t** buf_out) {
    // TODO: implement emulator display backend.
    (void)buf_out;
    return ASP_ERR_UNSUPPORTED;
}

// Initialize a PAX buffer that matches the main display's format.
asp_err_t asp_disp_init_pax_buf(pax_buf_t* buf) {
    // TODO: implement emulator display backend.
    (void)buf;
    return ASP_ERR_UNSUPPORTED;
}

// Write the data in `fb` to the entirety of the main display.
asp_err_t asp_disp_write(void const* fb) {
    // TODO: implement emulator display backend.
    (void)fb;
    return ASP_ERR_UNSUPPORTED;
}

// Write the data in the PAX buffer `img` to the entirety of the main display.
asp_err_t asp_disp_write_pax(pax_buf_t* img) {
    // TODO: implement emulator display backend.
    (void)img;
    return ASP_ERR_UNSUPPORTED;
}

// Write the data in `fb` to part of the main display.
asp_err_t asp_disp_write_part(void const* fb, uint16_t x, uint16_t y, uint16_t w, uint16_t h) {
    // TODO: implement emulator display backend.
    (void)fb;
    (void)x;
    (void)y;
    (void)w;
    (void)h;
    return ASP_ERR_UNSUPPORTED;
}

// Write the data in the PAX buffer `img` to part of the main display.
asp_err_t asp_disp_write_part_pax(pax_buf_t* img, uint16_t x, uint16_t y) {
    // TODO: implement emulator display backend.
    (void)img;
    (void)x;
    (void)y;
    return ASP_ERR_UNSUPPORTED;
}
