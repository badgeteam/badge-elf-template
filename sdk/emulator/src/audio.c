
// SPDX-License-Identiefier: MIT
// SPDX-CopyRightText: 2025 Badge.Team

#include "asp/audio.h"
#include <SDL3/SDL_audio.h>
#include <SDL3/SDL_log.h>
#include "asp/err.h"

SDL_AudioStream* emu_audio;
SDL_AudioSpec    emu_audio_spec;

// Set audio sampling rate.
asp_err_t asp_audio_set_rate(uint32_t rate_hz) {
    emu_audio_spec.freq = rate_hz;
    return ASP_OK;
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
    if (!enabled && emu_audio) {
        SDL_PauseAudioStreamDevice(emu_audio);
        SDL_DestroyAudioStream(emu_audio);
        emu_audio = NULL;
    }

    if (enabled && !emu_audio) {
        emu_audio_spec.channels = 2;
        emu_audio_spec.format   = SDL_AUDIO_S16LE;
        emu_audio = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &emu_audio_spec, NULL, NULL);
        if (!emu_audio) {
            SDL_Log("Failed to open audio stream: %s", SDL_GetError());
            return ASP_ERR_FAIL;
        }
    }

    return ASP_OK;
}

// Stop the audio stream.
asp_err_t asp_audio_stop() {
    if (!emu_audio) {
        return ASP_ERR_FAIL;
    }

    SDL_ResumeAudioStreamDevice(emu_audio);
    return ASP_OK;
}

// Start the audio stream.
asp_err_t asp_audio_start() {
    if (!emu_audio) {
        return ASP_ERR_FAIL;
    }

    SDL_PauseAudioStreamDevice(emu_audio);
    return ASP_OK;
}

// Write audio samples.
asp_err_t asp_audio_write(void* samples, size_t samples_size, int64_t timeout_ms) {
    if (!emu_audio) {
        return ASP_ERR_FAIL;
    }

    SDL_PutAudioStreamData(emu_audio, samples, samples_size);
    return ASP_OK;
}
