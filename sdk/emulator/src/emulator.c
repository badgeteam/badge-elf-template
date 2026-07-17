
// SPDX-License-Identiefier: MIT
// SPDX-CopyRightText: 2025 Badge.Team

#include "emulator.h"
#include <SDL3/SDL_audio.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_render.h>
#include <fcntl.h>
#include <limits.h>
#include <mqueue.h>
#include <stdlib.h>
#include <unistd.h>
#include "asp/display.h"
#include "asp/err.h"
#include "pax_types.h"

pax_buf_t     emu_gfx;
SDL_Window*   emu_window;
SDL_Renderer* emu_render;
SDL_Texture*  emu_texture;

// We want to run as the absolute *last* thing before `main`; priority 65535 is the lowet possible.
__attribute__((constructor(65535))) static void emulator_init() {
    SDL_SetAppMetadata("BadgeELF Emulator", "1.0", "team.badge.badge-elf-emulator");

    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        exit(1);
    }

    if (!SDL_CreateWindowAndRenderer("BadgeELF Emulator", 800, 480, 0, &emu_window, &emu_render)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        exit(1);
    }

    emu_texture = SDL_CreateTexture(emu_render, SDL_PIXELFORMAT_XRGB8888, SDL_TEXTUREACCESS_STREAMING, EMU_WINDOW_W,
                                    EMU_WINDOW_H);
    if (!emu_texture) {
        SDL_Log("Couldn't create streaming texture: %s", SDL_GetError());
        exit(1);
    }

    asp_err_t res = asp_disp_init_pax_buf(&emu_gfx);
    if (res != ASP_OK) {
        SDL_Log("Couldn't create PAX graphics buffer: %s", asp_err_desc(res));
        exit(1);
    }

    SDL_StartTextInput(emu_window);
}
