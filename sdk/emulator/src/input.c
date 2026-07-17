
// SPDX-License-Identiefier: MIT
// SPDX-CopyRightText: 2025 Badge.Team

#include "asp/input.h"
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_log.h>
#include <bits/time.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "asp/input_types.h"
#include "emulator.h"

#define QUEUE_SIZE 32
static asp_input_event_t queue[QUEUE_SIZE];
static size_t            queue_read  = 0;
static size_t            queue_write = 0;

struct emu_keymap {
    asp_input_navigation_key_t nav;
    asp_input_scancode_t       scan;
};

// clang-format off
static struct emu_keymap get_keymap(SDL_Keycode sdlk) {
    switch (sdlk) {
        case SDLK_ESCAPE:                 return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_ESC,         ASP_INPUT_SCANCODE_ESC, };
        case SDLK_1:                      return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_1, };
        case SDLK_2:                      return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_2, };
        case SDLK_3:                      return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_3, };
        case SDLK_4:                      return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_4, };
        case SDLK_5:                      return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_5, };
        case SDLK_6:                      return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_6, };
        case SDLK_7:                      return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_7, };
        case SDLK_8:                      return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_8, };
        case SDLK_9:                      return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_9, };
        case SDLK_0:                      return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_0, };
        case SDLK_MINUS:                  return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_MINUS, };
        case SDLK_EQUALS:                 return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_EQUAL, };
        case SDLK_BACKSPACE:              return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_BACKSPACE,   ASP_INPUT_SCANCODE_BACKSPACE, };
        case SDLK_TAB:                    return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_TAB,         ASP_INPUT_SCANCODE_TAB, };
        case SDLK_Q:                      return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_Q, };
        case SDLK_W:                      return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_W, };
        case SDLK_E:                      return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_E, };
        case SDLK_R:                      return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_R, };
        case SDLK_T:                      return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_T, };
        case SDLK_Y:                      return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_Y, };
        case SDLK_U:                      return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_U, };
        case SDLK_I:                      return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_I, };
        case SDLK_O:                      return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_O, };
        case SDLK_P:                      return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_P, };
        case SDLK_LEFTBRACE:              return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_LEFTBRACE, };
        case SDLK_RIGHTBRACE:             return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_RIGHTBRACE, };
        case SDLK_RETURN:                 return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_RETURN,      ASP_INPUT_SCANCODE_ENTER, };
        case SDLK_LCTRL:                  return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_LEFTCTRL, };
        case SDLK_A:                      return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_A, };
        case SDLK_S:                      return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_S, };
        case SDLK_D:                      return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_D, };
        case SDLK_F:                      return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_F, };
        case SDLK_G:                      return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_G, };
        case SDLK_H:                      return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_H, };
        case SDLK_J:                      return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_J, };
        case SDLK_K:                      return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_K, };
        case SDLK_L:                      return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_L, };
        case SDLK_SEMICOLON:              return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_SEMICOLON, };
        case SDLK_APOSTROPHE:             return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_APOSTROPHE, };
        case SDLK_GRAVE:                  return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_GRAVE, };
        case SDLK_LSHIFT:                 return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_LEFTSHIFT, };
        case SDLK_BACKSLASH:              return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_BACKSLASH, };
        case SDLK_Z:                      return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_Z, };
        case SDLK_X:                      return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_X, };
        case SDLK_C:                      return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_C, };
        case SDLK_V:                      return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_V, };
        case SDLK_B:                      return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_B, };
        case SDLK_N:                      return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_N, };
        case SDLK_M:                      return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_M, };
        case SDLK_COMMA:                  return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_COMMA, };
        case SDLK_PERIOD:                 return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_DOT, };
        case SDLK_SLASH:                  return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_SLASH, };
        case SDLK_RSHIFT:                 return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_RIGHTSHIFT, };
        case SDLK_ASTERISK:               return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_KPASTERISK, };
        case SDLK_LALT:                   return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_LEFTALT, };
        case SDLK_SPACE:                  return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_SPACE_M,     ASP_INPUT_SCANCODE_SPACE, };
        case SDLK_CAPSLOCK:               return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_CAPSLOCK, };
        case SDLK_F1:                     return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_F1,          ASP_INPUT_SCANCODE_F1, };
        case SDLK_F2:                     return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_F2,          ASP_INPUT_SCANCODE_F2, };
        case SDLK_F3:                     return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_F3,          ASP_INPUT_SCANCODE_F3, };
        case SDLK_F4:                     return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_F4,          ASP_INPUT_SCANCODE_F4, };
        case SDLK_F5:                     return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_F5,          ASP_INPUT_SCANCODE_F5, };
        case SDLK_F6:                     return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_F6,          ASP_INPUT_SCANCODE_F6, };
        case SDLK_F7:                     return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_F7,          ASP_INPUT_SCANCODE_F7, };
        case SDLK_F8:                     return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_F8,          ASP_INPUT_SCANCODE_F8, };
        case SDLK_F9:                     return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_F9,          ASP_INPUT_SCANCODE_F9, };
        case SDLK_F10:                    return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_F10,         ASP_INPUT_SCANCODE_F10, };
        // SDL has no event for num lock.
        case SDLK_SCROLLLOCK:             return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_SCROLLLOCK, };
        case SDLK_KP_7:                   return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_KP7, };
        case SDLK_KP_8:                   return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_KP8, };
        case SDLK_KP_9:                   return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_KP9, };
        case SDLK_KP_MINUS:               return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_KPMINUS, };
        case SDLK_KP_4:                   return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_KP4, };
        case SDLK_KP_5:                   return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_KP5, };
        case SDLK_KP_6:                   return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_KP6, };
        case SDLK_KP_PLUS:                return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_KPPLUS, };
        case SDLK_KP_1:                   return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_KP1, };
        case SDLK_KP_2:                   return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_KP2, };
        case SDLK_KP_3:                   return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_KP3, };
        case SDLK_KP_0:                   return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_KP0, };
        case SDLK_KP_PERIOD:              return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_KPDOT, };
        case SDLK_SYSREQ:                 return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_SYSREQ, };
        // TODO: SDL has no event for fn and we should have a macro for it.
        case SDLK_F11:                    return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_F11, };
        case SDLK_F12:                    return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_F12, };
        case SDLK_MEDIA_PREVIOUS_TRACK:   return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_ESCAPED_PREV_TRACK, };
        case SDLK_MEDIA_NEXT_TRACK:       return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_ESCAPED_NEXT_TRACK, };
        case SDLK_KP_ENTER:               return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_ESCAPED_KPENTER, };
        case SDLK_RCTRL:                  return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_ESCAPED_RCTRL, };
        case SDLK_MUTE:                   return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_ESCAPED_VOLUME_MUTE, };
        // SDL has no calculator key.
        case SDLK_MEDIA_PLAY:             return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_ESCAPED_PLAY, };
        // SDL has no fake lshift.
        case SDLK_VOLUMEDOWN:             return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_VOLUME_DOWN, ASP_INPUT_SCANCODE_ESCAPED_VOLUME_DOWN, };
        case SDLK_VOLUMEUP:               return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_VOLUME_UP,   ASP_INPUT_SCANCODE_ESCAPED_VOLUME_UP, };
        // SDL has no fake rshift.
        case SDLK_PRINTSCREEN:            return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_ESCAPED_CTRL_PRTSCN, };
        case SDLK_RALT:                   return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_ESCAPED_RALT, };
        case SDLK_PAUSE:                  return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_ESCAPED_CTRL_BREAK, };
        case SDLK_HOME:                   return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_HOME,        ASP_INPUT_SCANCODE_ESCAPED_GREY_HOME, };
        case SDLK_UP:                     return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_UP,          ASP_INPUT_SCANCODE_ESCAPED_GREY_UP, };
        case SDLK_PAGEUP:                 return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_PGUP,        ASP_INPUT_SCANCODE_ESCAPED_GREY_PGUP, };
        case SDLK_LEFT:                   return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_LEFT,        ASP_INPUT_SCANCODE_ESCAPED_GREY_LEFT, };
        case SDLK_RIGHT:                  return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_RIGHT,       ASP_INPUT_SCANCODE_ESCAPED_GREY_RIGHT, };
        case SDLK_END:                    return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_END,         ASP_INPUT_SCANCODE_ESCAPED_GREY_END, };
        case SDLK_DOWN:                   return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_DOWN,        ASP_INPUT_SCANCODE_ESCAPED_GREY_DOWN, };
        case SDLK_PAGEDOWN:               return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_PGDN,        ASP_INPUT_SCANCODE_ESCAPED_GREY_PGDN, };
        case SDLK_INSERT:                 return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_ESCAPED_GREY_INSERT, };
        case SDLK_DELETE:                 return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_ESCAPED_GREY_DEL, };
        case SDLK_LMETA:                  return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_SUPER,       ASP_INPUT_SCANCODE_ESCAPED_LEFTMETA, };
        case SDLK_RMETA:                  return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_SUPER,       ASP_INPUT_SCANCODE_ESCAPED_RIGHTMETA, };
        case SDLK_MENU:                   return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_MENU,        ASP_INPUT_SCANCODE_ESCAPED_MENU, };
        case SDLK_SLEEP:                  return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_ESCAPED_SLEEP, };
        case SDLK_STOP:                   return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_ESCAPED_STOP, };
        case SDLK_AC_FORWARD:             return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_ESCAPED_FORWARD, };
        case SDLK_AC_BACK:                return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_ESCAPED_BACK, };
        // SDL has no my computer key.
        // SDL has no mail key.
        case SDLK_MEDIA_SELECT:           return (struct emu_keymap) { ASP_INPUT_NAVIGATION_KEY_NONE,        ASP_INPUT_SCANCODE_ESCAPED_MEDIA, };
    };
    return (struct emu_keymap) {ASP_INPUT_NAVIGATION_KEY_NONE, ASP_INPUT_SCANCODE_NONE};
}
// clang-format on

static int64_t time_ms() {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    return (int64_t)ts.tv_sec * 1000 + ts.tv_nsec / 1000000;
}

// Push an event to the queue.
static void push_event(const asp_input_event_t* ev) {
    if ((queue_write + 1) % QUEUE_SIZE != queue_read) {
        queue[queue_write] = *ev;
        queue_write        = (queue_write + 1) % QUEUE_SIZE;
    }
}

// Try to pop an event from the queue.
static bool pop_event(asp_input_event_t* ev) {
    if (queue_read != queue_write) {
        *ev        = queue[queue_read];
        queue_read = (queue_read + 1) % QUEUE_SIZE;
        return true;
    } else {
        return false;
    }
}

// Convert SDL modifier keys to ASP modifier keys.
static uint32_t asp_modkeys_from_sdl_modkeys(SDL_Keymod modkeys) {
    return 0;
}

// Convert SDL key up/down event to ASP input event.
static void asp_event_from_sdl_key(const SDL_KeyboardEvent* sdl_event, bool new_state) {
    uint32_t modifiers = asp_modkeys_from_sdl_modkeys(sdl_event->mod);

    struct emu_keymap km = get_keymap(sdl_event->key);

    if (km.nav != ASP_INPUT_NAVIGATION_KEY_NONE) {
        asp_input_event_t ev = {
            .type = ASP_INPUT_EVENT_TYPE_NAVIGATION,
            .args_navigation =
                (asp_input_event_args_navigation_t){
                    .key       = km.nav,
                    .state     = new_state,
                    .modifiers = modifiers,
                },
        };
        push_event(&ev);
    }

    if (km.scan != ASP_INPUT_SCANCODE_NONE) {
        asp_input_event_t ev = {
            .type = ASP_INPUT_EVENT_TYPE_SCANCODE,
            .args_scancode =
                (asp_input_event_args_scancode_t){
                    .scancode = km.scan,
                },
        };
        push_event(&ev);
    }
}

// Convert SDL text input event to ASP text input event.
static void asp_event_from_sdl_text(const SDL_TextInputEvent* sdl_event) {
    asp_input_event_t ev = {
        .type = ASP_INPUT_EVENT_TYPE_KEYBOARD,
        .args_keyboard =
            (asp_input_event_args_keyboard_t){
                .ascii     = sdl_event->text[0],
                .modifiers = 0,
            },
    };
    strlcpy(ev.args_keyboard.utf8, sdl_event->text, sizeof(ev.args_keyboard.utf8));
    push_event(&ev);
}

// Convert SDL event to ASP input event.
// Returns false if ASP has no representation for this event.
static void asp_event_from_sdl(const SDL_Event* sdl_event) {
    switch (sdl_event->type) {
        case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
            exit(0);
        case SDL_EVENT_KEY_UP:
            return asp_event_from_sdl_key(&sdl_event->key, false);
        case SDL_EVENT_KEY_DOWN:
            return asp_event_from_sdl_key(&sdl_event->key, true);
        case SDL_EVENT_TEXT_INPUT:
            return asp_event_from_sdl_text(&sdl_event->text);
    }
}

// Check for an input event; sleep for at most `max_delay_ms` (0 is non-blocking).
bool asp_input_poll(asp_input_event_t* event_out, int64_t max_delay_ms) {
    if (max_delay_ms < 0) max_delay_ms = 0;
    int64_t start = time_ms();
    int64_t lim;
    if (INT64_MAX - start < max_delay_ms) {
        lim = INT64_MAX;
    } else {
        lim = start + max_delay_ms;
    }

    int64_t now = start;
    while (now < lim) {
        if (pop_event(event_out)) {
            return true;
        }

        int64_t max = lim - now;
        if (max > INT32_MAX) max = INT32_MAX;
        SDL_Event sdl_event;
        if (SDL_WaitEventTimeout(&sdl_event, max)) {
            asp_event_from_sdl(&sdl_event);
        }

        now = time_ms();
    }

    return false;
}

// Get the current state of a navigation input.
asp_err_t asp_input_get_nav(asp_input_navigation_key_t nav_key, bool* state_out) {
    // TODO: implement emulator input backend.
    (void)nav_key;
    (void)state_out;
    return ASP_ERR_UNSUPPORTED;
}

// Get the current state of an action input.
asp_err_t asp_input_get_action(asp_input_action_type_t action, bool* state_out) {
    // TODO: implement emulator input backend.
    (void)action;
    (void)state_out;
    return ASP_ERR_UNSUPPORTED;
}

// Whether there is a need for an on-screen keyboard.
bool asp_input_needs_on_screen_keyboard() {
    return false;
}

// Set the input (usually keyboard) backlight brightness.
asp_err_t asp_input_set_backlight(uint8_t percent) {
    (void)percent;
    return ASP_ERR_UNSUPPORTED;
}

// Get the input (usually keyboard) backlight brightness.
asp_err_t asp_input_get_backlight(uint8_t* percent_out) {
    (void)percent_out;
    return ASP_ERR_UNSUPPORTED;
}
