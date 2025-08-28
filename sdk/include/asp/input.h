
// SPDX-License-Identiefier: MIT
// SPDX-CopyRightText: 2025 Badge.Team

#pragma once

#include "asp/err.h"
#include "asp/input_types.h"

// Check for an input event; sleep for at most `max_delay_ms` (0 is non-blocking).
bool      asp_input_poll(asp_input_event_t* event_out, int64_t max_delay_ms);
// Get the current state of a navigation input.
asp_err_t asp_input_get_nav(asp_input_navigation_key_t nav_key, bool* state_out);
// Get the current state of an action input.
asp_err_t asp_input_get_action(asp_input_action_type_t action, bool* state_out);

// Whether there is a need for an on-screen keyboard.
// TODO: Make a function to pop up the on-screen keyboard.
bool asp_input_needs_on_screen_keyboard();

// Set the input (usually keyboard) backlight brightness.
asp_err_t asp_input_set_backlight(uint8_t percent);
// Get the input (usually keyboard) backlight brightness.
asp_err_t asp_input_get_backlight(uint8_t* percent_out);
