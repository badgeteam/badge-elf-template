
// SPDX-License-Identiefier: MIT
// SPDX-CopyRightText: 2025 Renze Nicolai
// SPDX-CopyRightText: 2025 Badge.Team

// See: https://github.com/badgeteam/esp32-component-badge-bsp/blob/928ffc3122908b94d80a404667929d6d304b979d/bsp/input.h

#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef enum {
    ASP_INPUT_EVENT_TYPE_NONE       = 0,
    ASP_INPUT_EVENT_TYPE_NAVIGATION = 1,  // Keyboard: navigation keys
    ASP_INPUT_EVENT_TYPE_KEYBOARD   = 2,  // Keyboard: ASCII/UTF-8
    ASP_INPUT_EVENT_TYPE_ACTION     = 3,  // Other actions (e.g. power button)
    ASP_INPUT_EVENT_TYPE_SCANCODE   = 4,  // Keyboard: PC scancodes
    ASP_INPUT_EVENT_TYPE_LAST,
} asp_input_event_type_t;

typedef enum {
    ASP_INPUT_SCANCODE_NONE                = 0x00,
    ASP_INPUT_SCANCODE_ESC                 = 0x01,
    ASP_INPUT_SCANCODE_1                   = 0x02,
    ASP_INPUT_SCANCODE_2                   = 0x03,
    ASP_INPUT_SCANCODE_3                   = 0x04,
    ASP_INPUT_SCANCODE_4                   = 0x05,
    ASP_INPUT_SCANCODE_5                   = 0x06,
    ASP_INPUT_SCANCODE_6                   = 0x07,
    ASP_INPUT_SCANCODE_7                   = 0x08,
    ASP_INPUT_SCANCODE_8                   = 0x09,
    ASP_INPUT_SCANCODE_9                   = 0x0A,
    ASP_INPUT_SCANCODE_0                   = 0x0B,
    ASP_INPUT_SCANCODE_MINUS               = 0x0C,
    ASP_INPUT_SCANCODE_EQUAL               = 0x0D,
    ASP_INPUT_SCANCODE_BACKSPACE           = 0x0E,
    ASP_INPUT_SCANCODE_TAB                 = 0x0F,
    ASP_INPUT_SCANCODE_Q                   = 0x10,
    ASP_INPUT_SCANCODE_W                   = 0x11,
    ASP_INPUT_SCANCODE_E                   = 0x12,
    ASP_INPUT_SCANCODE_R                   = 0x13,
    ASP_INPUT_SCANCODE_T                   = 0x14,
    ASP_INPUT_SCANCODE_Y                   = 0x15,
    ASP_INPUT_SCANCODE_U                   = 0x16,
    ASP_INPUT_SCANCODE_I                   = 0x17,
    ASP_INPUT_SCANCODE_O                   = 0x18,
    ASP_INPUT_SCANCODE_P                   = 0x19,
    ASP_INPUT_SCANCODE_LEFTBRACE           = 0x1A,
    ASP_INPUT_SCANCODE_RIGHTBRACE          = 0x1B,
    ASP_INPUT_SCANCODE_ENTER               = 0x1C,
    ASP_INPUT_SCANCODE_LEFTCTRL            = 0x1D,
    ASP_INPUT_SCANCODE_A                   = 0x1E,
    ASP_INPUT_SCANCODE_S                   = 0x1F,
    ASP_INPUT_SCANCODE_D                   = 0x20,
    ASP_INPUT_SCANCODE_F                   = 0x21,
    ASP_INPUT_SCANCODE_G                   = 0x22,
    ASP_INPUT_SCANCODE_H                   = 0x23,
    ASP_INPUT_SCANCODE_J                   = 0x24,
    ASP_INPUT_SCANCODE_K                   = 0x25,
    ASP_INPUT_SCANCODE_L                   = 0x26,
    ASP_INPUT_SCANCODE_SEMICOLON           = 0x27,
    ASP_INPUT_SCANCODE_APOSTROPHE          = 0x28,
    ASP_INPUT_SCANCODE_GRAVE               = 0x29,
    ASP_INPUT_SCANCODE_LEFTSHIFT           = 0x2A,
    ASP_INPUT_SCANCODE_BACKSLASH           = 0x2B,
    ASP_INPUT_SCANCODE_Z                   = 0x2C,
    ASP_INPUT_SCANCODE_X                   = 0x2D,
    ASP_INPUT_SCANCODE_C                   = 0x2E,
    ASP_INPUT_SCANCODE_V                   = 0x2F,
    ASP_INPUT_SCANCODE_B                   = 0x30,
    ASP_INPUT_SCANCODE_N                   = 0x31,
    ASP_INPUT_SCANCODE_M                   = 0x32,
    ASP_INPUT_SCANCODE_COMMA               = 0x33,
    ASP_INPUT_SCANCODE_DOT                 = 0x34,
    ASP_INPUT_SCANCODE_SLASH               = 0x35,
    ASP_INPUT_SCANCODE_RIGHTSHIFT          = 0x36,
    ASP_INPUT_SCANCODE_KPASTERISK          = 0x37,
    ASP_INPUT_SCANCODE_LEFTALT             = 0x38,
    ASP_INPUT_SCANCODE_SPACE               = 0x39,
    ASP_INPUT_SCANCODE_CAPSLOCK            = 0x3A,
    ASP_INPUT_SCANCODE_F1                  = 0x3B,
    ASP_INPUT_SCANCODE_F2                  = 0x3C,
    ASP_INPUT_SCANCODE_F3                  = 0x3D,
    ASP_INPUT_SCANCODE_F4                  = 0x3E,
    ASP_INPUT_SCANCODE_F5                  = 0x3F,
    ASP_INPUT_SCANCODE_F6                  = 0x40,
    ASP_INPUT_SCANCODE_F7                  = 0x41,
    ASP_INPUT_SCANCODE_F8                  = 0x42,
    ASP_INPUT_SCANCODE_F9                  = 0x43,
    ASP_INPUT_SCANCODE_F10                 = 0x44,
    ASP_INPUT_SCANCODE_NUMLOCK             = 0x45,
    ASP_INPUT_SCANCODE_SCROLLLOCK          = 0x46,
    ASP_INPUT_SCANCODE_KP7                 = 0x47,
    ASP_INPUT_SCANCODE_KP8                 = 0x48,
    ASP_INPUT_SCANCODE_KP9                 = 0x49,
    ASP_INPUT_SCANCODE_KPMINUS             = 0x4A,
    ASP_INPUT_SCANCODE_KP4                 = 0x4B,
    ASP_INPUT_SCANCODE_KP5                 = 0x4C,
    ASP_INPUT_SCANCODE_KP6                 = 0x4D,
    ASP_INPUT_SCANCODE_KPPLUS              = 0x4E,
    ASP_INPUT_SCANCODE_KP1                 = 0x4F,
    ASP_INPUT_SCANCODE_KP2                 = 0x50,
    ASP_INPUT_SCANCODE_KP3                 = 0x51,
    ASP_INPUT_SCANCODE_KP0                 = 0x52,
    ASP_INPUT_SCANCODE_KPDOT               = 0x53,
    ASP_INPUT_SCANCODE_SYSREQ              = 0x54,
    ASP_INPUT_SCANCODE_FN                  = 0x55,
    ASP_INPUT_SCANCODE_F11                 = 0x57,
    ASP_INPUT_SCANCODE_F12                 = 0x58,
    ASP_INPUT_SCANCODE_ESCAPED_PREV_TRACK  = 0xe010,
    ASP_INPUT_SCANCODE_ESCAPED_NEXT_TRACK  = 0xe019,
    ASP_INPUT_SCANCODE_ESCAPED_KPENTER     = 0xe01c,
    ASP_INPUT_SCANCODE_ESCAPED_RCTRL       = 0xe01d,
    ASP_INPUT_SCANCODE_ESCAPED_VOLUME_MUTE = 0xe020,
    ASP_INPUT_SCANCODE_ESCAPED_CALCULATOR  = 0xe021,
    ASP_INPUT_SCANCODE_ESCAPED_PLAY        = 0xe022,
    ASP_INPUT_SCANCODE_ESCAPED_FAKE_LSHIFT = 0xe02a,
    ASP_INPUT_SCANCODE_ESCAPED_VOLUME_DOWN = 0xe02e,
    ASP_INPUT_SCANCODE_ESCAPED_VOLUME_UP   = 0xe030,
    ASP_INPUT_SCANCODE_ESCAPED_KPMINUS     = 0xe035,
    ASP_INPUT_SCANCODE_ESCAPED_FAKE_RSHIFT = 0xe036,
    ASP_INPUT_SCANCODE_ESCAPED_CTRL_PRTSCN = 0xe037,
    ASP_INPUT_SCANCODE_ESCAPED_RALT        = 0xe038,
    ASP_INPUT_SCANCODE_ESCAPED_CTRL_BREAK  = 0xe046,
    ASP_INPUT_SCANCODE_ESCAPED_GREY_HOME   = 0xe047,
    ASP_INPUT_SCANCODE_ESCAPED_GREY_UP     = 0xe048,
    ASP_INPUT_SCANCODE_ESCAPED_GREY_PGUP   = 0xe049,
    ASP_INPUT_SCANCODE_ESCAPED_GREY_LEFT   = 0xe04b,
    ASP_INPUT_SCANCODE_ESCAPED_GREY_RIGHT  = 0xe04d,
    ASP_INPUT_SCANCODE_ESCAPED_GREY_END    = 0xe04f,
    ASP_INPUT_SCANCODE_ESCAPED_GREY_DOWN   = 0xe050,
    ASP_INPUT_SCANCODE_ESCAPED_GREY_PGDN   = 0xe051,
    ASP_INPUT_SCANCODE_ESCAPED_GREY_INSERT = 0xe052,
    ASP_INPUT_SCANCODE_ESCAPED_GREY_DEL    = 0xe053,
    ASP_INPUT_SCANCODE_ESCAPED_LEFTMETA    = 0xe05b,
    ASP_INPUT_SCANCODE_ESCAPED_RIGHTMETA   = 0xe05c,
    ASP_INPUT_SCANCODE_ESCAPED_MENU        = 0xe05d,
    ASP_INPUT_SCANCODE_ESCAPED_SLEEP       = 0xe05f,
    ASP_INPUT_SCANCODE_ESCAPED_STOP        = 0xe068,
    ASP_INPUT_SCANCODE_ESCAPED_FORWARD     = 0xe069,
    ASP_INPUT_SCANCODE_ESCAPED_BACK        = 0xe06a,
    ASP_INPUT_SCANCODE_ESCAPED_MYCOMPUTER  = 0xe06b,
    ASP_INPUT_SCANCODE_ESCAPED_MAIL        = 0xe06c,
    ASP_INPUT_SCANCODE_ESCAPED_MEDIA       = 0xe06d,
} asp_input_scancode_t;

#define ASP_INPUT_SCANCODE_RELEASE_MODIFIER (0x80)

typedef enum {
    ASP_INPUT_NAVIGATION_KEY_NONE = 0,

    // Navigation keys
    ASP_INPUT_NAVIGATION_KEY_ESC,
    ASP_INPUT_NAVIGATION_KEY_LEFT,
    ASP_INPUT_NAVIGATION_KEY_RIGHT,
    ASP_INPUT_NAVIGATION_KEY_UP,
    ASP_INPUT_NAVIGATION_KEY_DOWN,
    ASP_INPUT_NAVIGATION_KEY_HOME,
    ASP_INPUT_NAVIGATION_KEY_END,
    ASP_INPUT_NAVIGATION_KEY_PGUP,
    ASP_INPUT_NAVIGATION_KEY_PGDN,
    ASP_INPUT_NAVIGATION_KEY_MENU,
    ASP_INPUT_NAVIGATION_KEY_START,
    ASP_INPUT_NAVIGATION_KEY_SELECT,
    ASP_INPUT_NAVIGATION_KEY_RETURN,
    ASP_INPUT_NAVIGATION_KEY_SUPER,
    ASP_INPUT_NAVIGATION_KEY_TAB,
    ASP_INPUT_NAVIGATION_KEY_BACKSPACE,
    ASP_INPUT_NAVIGATION_KEY_SPACE_L,
    ASP_INPUT_NAVIGATION_KEY_SPACE_M,
    ASP_INPUT_NAVIGATION_KEY_SPACE_R,

    // Function keys
    ASP_INPUT_NAVIGATION_KEY_F1,
    ASP_INPUT_NAVIGATION_KEY_F2,
    ASP_INPUT_NAVIGATION_KEY_F3,
    ASP_INPUT_NAVIGATION_KEY_F4,
    ASP_INPUT_NAVIGATION_KEY_F5,
    ASP_INPUT_NAVIGATION_KEY_F6,
    ASP_INPUT_NAVIGATION_KEY_F7,
    ASP_INPUT_NAVIGATION_KEY_F8,
    ASP_INPUT_NAVIGATION_KEY_F9,
    ASP_INPUT_NAVIGATION_KEY_F10,
    ASP_INPUT_NAVIGATION_KEY_F11,
    ASP_INPUT_NAVIGATION_KEY_F12,

    // Gamepad
    ASP_INPUT_NAVIGATION_KEY_GAMEPAD_A,
    ASP_INPUT_NAVIGATION_KEY_GAMEPAD_B,
    ASP_INPUT_NAVIGATION_KEY_GAMEPAD_X,
    ASP_INPUT_NAVIGATION_KEY_GAMEPAD_Y,
    ASP_INPUT_NAVIGATION_KEY_JOYSTICK_PRESS,

    // Volume keys
    ASP_INPUT_NAVIGATION_KEY_VOLUME_UP,
    ASP_INPUT_NAVIGATION_KEY_VOLUME_DOWN,
} asp_input_navigation_key_t;

typedef enum {
    ASP_INPUT_ACTION_TYPE_NONE = 0,
    ASP_INPUT_ACTION_TYPE_SD_CARD,
    ASP_INPUT_ACTION_TYPE_AUDIO_JACK,
    ASP_INPUT_ACTION_TYPE_POWER_BUTTON,
    ASP_INPUT_ACTION_TYPE_FPGA_CDONE,
    ASP_INPUT_ACTION_TYPE_PMIC_FAULT,
} asp_input_action_type_t;

// Modifiers
#define ASP_INPUT_MODIFIER_CAPSLOCK  (1 << 0)
#define ASP_INPUT_MODIFIER_SHIFT_L   (1 << 1)
#define ASP_INPUT_MODIFIER_SHIFT_R   (1 << 2)
#define ASP_INPUT_MODIFIER_SHIFT     (ASP_INPUT_MODIFIER_SHIFT_L | ASP_INPUT_MODIFIER_SHIFT_R)
#define ASP_INPUT_MODIFIER_UPPERCASE (ASP_INPUT_MODIFIER_SHIFT | ASP_INPUT_MODIFIER_CAPSLOCK)
#define ASP_INPUT_MODIFIER_CTRL_L    (1 << 3)
#define ASP_INPUT_MODIFIER_CTRL_R    (1 << 4)
#define ASP_INPUT_MODIFIER_CTRL      (ASP_INPUT_MODIFIER_CTRL_L | ASP_INPUT_MODIFIER_CTRL_R)
#define ASP_INPUT_MODIFIER_ALT_L     (1 << 5)
#define ASP_INPUT_MODIFIER_ALT_R     (1 << 6)
#define ASP_INPUT_MODIFIER_ALT       (ASP_INPUT_MODIFIER_ALT_L | ASP_INPUT_MODIFIER_ALT_R)
#define ASP_INPUT_MODIFIER_SUPER_L   (1 << 7)
#define ASP_INPUT_MODIFIER_SUPER_R   (1 << 8)
#define ASP_INPUT_MODIFIER_SUPER     (ASP_INPUT_MODIFIER_SUPER_L | ASP_INPUT_MODIFIER_SUPER_R)
#define ASP_INPUT_MODIFIER_FUNCTION  (1 << 9)

typedef struct {
    asp_input_navigation_key_t key;
    uint32_t                   modifiers;
    bool                       state;
} asp_input_event_args_navigation_t;

typedef struct {
    char        ascii;
    char const* utf8;
    uint32_t    modifiers;
} asp_input_event_args_keyboard_t;

typedef struct {
    asp_input_action_type_t type;
    bool                    state;
} asp_input_event_args_action_t;

typedef struct {
    asp_input_scancode_t scancode;
} asp_input_event_args_scancode_t;

typedef struct {
    asp_input_event_type_t type;
    union {
        asp_input_event_args_navigation_t args_navigation;
        asp_input_event_args_keyboard_t   args_keyboard;
        asp_input_event_args_action_t     args_action;
        asp_input_event_args_scancode_t   args_scancode;
    };
} asp_input_event_t;
