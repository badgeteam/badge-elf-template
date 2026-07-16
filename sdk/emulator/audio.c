
// SPDX-License-Identiefier: MIT
// SPDX-CopyRightText: 2025 Badge.Team

#include "asp/audio.h"

// Set audio sampling rate.
asp_err_t asp_audio_set_rate(uint32_t rate_hz) {
    // TODO: implement emulator audio backend.
    (void)rate_hz;
    return ASP_ERR_UNSUPPORTED;
}

// Get current volume.
asp_err_t asp_audio_get_volume(float* out_percentage) {
    // TODO: implement emulator audio backend.
    (void)out_percentage;
    return ASP_ERR_UNSUPPORTED;
}

// Set audio volume.
asp_err_t asp_audio_set_volume(float percentage) {
    // TODO: implement emulator audio backend.
    (void)percentage;
    return ASP_ERR_UNSUPPORTED;
}

// Enable/disable the audio amplifier.
asp_err_t asp_audio_set_amplifier(bool enabled) {
    // TODO: implement emulator audio backend.
    (void)enabled;
    return ASP_ERR_UNSUPPORTED;
}

// Stop the audio stream.
asp_err_t asp_audio_stop() {
    // TODO: implement emulator audio backend.
    return ASP_ERR_UNSUPPORTED;
}

// Start the audio stream.
asp_err_t asp_audio_start() {
    // TODO: implement emulator audio backend.
    return ASP_ERR_UNSUPPORTED;
}

// Write audio samples.
asp_err_t asp_audio_write(void* samples, size_t samples_size, int64_t timeout_ms) {
    // TODO: implement emulator audio backend.
    (void)samples;
    (void)samples_size;
    (void)timeout_ms;
    return ASP_ERR_UNSUPPORTED;
}
