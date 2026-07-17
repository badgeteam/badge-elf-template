
// SPDX-License-Identiefier: MIT
// SPDX-CopyRightText: 2025 Badge.Team

#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <mqueue.h>
#include "pax_types.h"

#define EMU_WINDOW_W 800
#define EMU_WINDOW_H 480

extern pax_buf_t        emu_gfx;
extern SDL_Window*      emu_window;
extern SDL_Renderer*    emu_render;
extern SDL_Texture*     emu_texture;
extern SDL_AudioStream* emu_audio;
