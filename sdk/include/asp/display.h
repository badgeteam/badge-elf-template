
// SPDX-License-Identiefier: MIT
// SPDX-CopyRightText: 2025 Badge.Team

#pragma once

#include <stdbool.h>
#include <stdint.h>
#include "asp/err.h"
#include "pax_gfx.h"

// Display pixel formats.
typedef enum {
    // 1-bit greyscale / black and white.
    ASP_PIXFMT_1_GREY,
    // 2-bit greyscale.
    ASP_PIXFMT_2_GREY,
    // 4-bit greyscale.
    ASP_PIXFMT_4_GREY,
    // 8-bit greyscale.
    ASP_PIXFMT_8_GREY,
    // 8-bit RGB: 3, 3, 2 bits for red, green and blue respectively.
    ASP_PIXFMT_8_332RGB,
    // 16-bit RGB: 5, 6, 5 bits for red, green and blue respectively.
    ASP_PIXFMT_16_565RGB,
    // 24-bit RGB: 8 bits per channel.
    ASP_PIXFMT_24_888RGB,
} asp_pixfmt_t;

// How far clockwise to rotate the graphics to be upright on the display.
typedef enum {
    ASP_DISP_ROTATION_0,
    ASP_DISP_ROTATION_90,
    ASP_DISP_ROTATION_180,
    ASP_DISP_ROTATION_270,
} asp_disp_rotation_t;

// Display parameters.
typedef struct {
    // Width in pixels (before rotation).
    uint16_t            width;
    // Height in pixels (before rotation).
    uint16_t            height;
    // How far clockwise to rotate the graphics to be upright on the display.
    asp_disp_rotation_t rotation;
    // Display's pixel format.
    asp_pixfmt_t        pixfmt;
    // Display is little-endian.
    bool                little_endian;
} asp_disp_params_t;

// Set display brightness.
asp_err_t asp_disp_set_brightness(uint8_t percent);
// Get current display brightness.
asp_err_t asp_disp_get_brightness(uint8_t* percent_out);

// Get display parameters of the main display.
asp_err_t asp_disp_get_params(asp_disp_params_t* params_out);
// Get existing framebuffer of the main display.
// If the framebuffer exists, it is written to `*fb_out`.
asp_err_t asp_disp_get_fb(uint8_t** fb_out);
// Get existing PAX buffer of the main display.
// If the PAX buffer exists, it is written to `*fb_out`.
asp_err_t asp_disp_get_pax_buf(pax_buf_t** buf_out);
// Initialize a PAX buffer that matches the main display's format.
asp_err_t asp_disp_init_pax_buf(pax_buf_t* buf);

// Write the data in `fb` to the entirety of the main display.
// See the `asp_disp_params_t` produced by `asp_disp_get_params` for the buffer format.
asp_err_t asp_disp_write(void const* fb);
// Write the data in the PAX buffer `img` to the entirety of the main display.
// Will error if the format of `img` does not match that of the main display.
asp_err_t asp_disp_write_pax(pax_buf_t* img);
// Write the data in `fb` to part of the main display.
// See the `asp_disp_params_t` produced by `asp_disp_get_params` for the buffer format.
// Will error if the specified region falls (partially) outside the size of the main display.
// **Note: It is up to the user to apply rotation, if needed.**
asp_err_t asp_disp_write_part(void const* fb, uint16_t x, uint16_t y, uint16_t w, uint16_t h);
// Write the data in the PAX buffer `img` to part of the main display.
// Will error if the specified region falls (partially) outside the size of the main display.
// **Note: It is up to the user to apply rotation, if needed.**
asp_err_t asp_disp_write_part_pax(pax_buf_t* img, uint16_t x, uint16_t y);
