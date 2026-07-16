
// SPDX-License-Identiefier: MIT
// SPDX-CopyRightText: 2025 Badge.Team

#include "asp/input.h"

// Check for an input event; sleep for at most `max_delay_ms` (0 is non-blocking).
bool asp_input_poll(asp_input_event_t* event_out, int64_t max_delay_ms) {
    // TODO: implement emulator input backend.
    (void)max_delay_ms;
    if (event_out) {
        event_out->type = ASP_INPUT_EVENT_TYPE_NONE;
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
    // TODO: implement emulator input backend.
    return false;
}

// Set the input (usually keyboard) backlight brightness.
asp_err_t asp_input_set_backlight(uint8_t percent) {
    // TODO: implement emulator input backend.
    (void)percent;
    return ASP_ERR_UNSUPPORTED;
}

// Get the input (usually keyboard) backlight brightness.
asp_err_t asp_input_get_backlight(uint8_t* percent_out) {
    // TODO: implement emulator input backend.
    (void)percent_out;
    return ASP_ERR_UNSUPPORTED;
}
