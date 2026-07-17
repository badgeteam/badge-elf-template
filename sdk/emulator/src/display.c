
// SPDX-License-Identiefier: MIT
// SPDX-CopyRightText: 2025 Badge.Team

#include "asp/display.h"
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <string.h>
#include <wchar.h>
#include "asp/err.h"
#include "emulator.h"
#include "pax_gfx.h"
#include "pax_types.h"

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
    *params_out = (asp_disp_params_t){
        .width         = EMU_WINDOW_W,
        .height        = EMU_WINDOW_H,
        .rotation      = ASP_DISP_ROTATION_0,
        .pixfmt        = ASP_PIXFMT_24_888RGB,
        .little_endian = true,
    };
    return ASP_OK;
}

// Get existing framebuffer of the main display.
asp_err_t asp_disp_get_fb(uint8_t** fb_out) {
    *fb_out = pax_buf_get_pixels_rw(&emu_gfx);
    return ASP_OK;
}

// Get existing PAX buffer of the main display.
asp_err_t asp_disp_get_pax_buf(pax_buf_t** buf_out) {
    *buf_out = &emu_gfx;
    return ASP_OK;
}

// Initialize a PAX buffer that matches the main display's format.
asp_err_t asp_disp_init_pax_buf(pax_buf_t* buf) {
    if (pax_buf_init(buf, NULL, EMU_WINDOW_W, EMU_WINDOW_H, PAX_BUF_32_8888ARGB)) {
        return ASP_OK;
    } else {
        return ASP_ERR_FAIL;
    }
}

// Write the data in `fb` to the entirety of the main display.
asp_err_t asp_disp_write(void const* fb) {
    return asp_disp_write_part(fb, 0, 0, EMU_WINDOW_W, EMU_WINDOW_H);
}

// Write the data in the PAX buffer `img` to the entirety of the main display.
asp_err_t asp_disp_write_pax(pax_buf_t* img) {
    pax_vec2i dims = pax_buf_get_dims_raw(img);
    return asp_disp_write_part(pax_buf_get_pixels(img), 0, 0, dims.x, dims.y);
}

// Write the data in `fb` to part of the main display.
asp_err_t asp_disp_write_part(void const* fb, uint16_t x, uint16_t y, uint16_t w, uint16_t h) {
    if (x + w > EMU_WINDOW_W || y + h > EMU_WINDOW_H) {
        return ASP_ERR_PARAM;
    }

    // This gets us an uninitialized buffer to write to the texture.
    void*    texture_pixels;
    int      texture_pitch;
    SDL_Rect texture_window = {
        .x = x,
        .y = y,
        .w = w,
        .h = h,
    };
    if (!SDL_LockTexture(emu_texture, &texture_window, &texture_pixels, &texture_pitch)) {
        return ASP_ERR_FAIL;
    }

    // Copy into the texture.
    if (x == 0 && y == 0 && w == EMU_WINDOW_W && h == EMU_WINDOW_H && texture_pitch == 4 * EMU_WINDOW_W) {
        memcpy(texture_pixels, fb, EMU_WINDOW_W * EMU_WINDOW_H * 4);
    } else {
        for (uint16_t row = 0; row < h; row++) {
            void* texture_row_pixels = (void*)((size_t)texture_pixels + texture_pitch * row);
            void* fb_row_pixels      = (void*)((size_t)fb + 4 * x + EMU_WINDOW_W * 4 * (row + y));
            memcpy(texture_row_pixels, fb_row_pixels, w * 4);
        }
    }

    // This writes our pixels back to the texture.
    SDL_UnlockTexture(emu_texture);

    // Now we use the SDL renderer API to write this to the display.
    SDL_FRect draw_pos = {
        .x = 0,
        .y = 0,
        .w = EMU_WINDOW_W,
        .h = EMU_WINDOW_H,
    };
    SDL_RenderClear(emu_render);
    SDL_RenderTexture(emu_render, emu_texture, &draw_pos, &draw_pos);

    SDL_RenderPresent(emu_render);

    return ASP_OK;
}

// Write the data in the PAX buffer `img` to part of the main display.
asp_err_t asp_disp_write_part_pax(pax_buf_t* img, uint16_t x, uint16_t y) {
    pax_vec2i dims = pax_buf_get_dims_raw(img);
    return asp_disp_write_part(pax_buf_get_pixels(img), x, y, dims.x, dims.y);
}
