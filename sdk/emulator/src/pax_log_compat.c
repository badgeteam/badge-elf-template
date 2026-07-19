
// SPDX-License-Identifier: MIT

// pax-graphics v2.1.0's pax_internal.h declares these globals (used by its PAX_LOG
// macro, which pax-codecs' standalone build also relies on) but never defines them
// outside of ESP-IDF builds. Provide them here so the emulator build links.
#include <pthread.h>
#include <stdbool.h>

pthread_mutex_t pax_log_mutex     = PTHREAD_MUTEX_INITIALIZER;
bool            pax_log_use_mutex = false;
