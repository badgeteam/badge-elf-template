
// SPDX-License-Identiefier: MIT
// SPDX-CopyRightText: 2025 Badge.Team

#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "asp/err.h"

// Set audio sampling rate.
asp_err_t asp_audio_set_rate(uint32_t rate_hz);
// Get current volume.
asp_err_t asp_audio_get_volume(float* out_percentage);
// Set audio volume.
asp_err_t asp_audio_set_volume(float percentage);
// Enable/disable the audio amplifier.
asp_err_t asp_audio_set_amplifier(bool enabled);
// Stop the audio stream.
asp_err_t asp_audio_stop();
// Start the audio stream.
asp_err_t asp_audio_start();
// Write audio samples.
asp_err_t asp_audio_write(void* samples, size_t samples_size, int64_t timeout_ms);
