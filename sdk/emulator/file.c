// SPDX-License-Identifier: MIT

#include "asp/file.h"

// The emulator has no DMA-capable stdio buffer to offer, so these are thin
// wrappers around plain stdio, matching the fallback behavior described in
// file.h.
FILE* asp_fastopen(const char* path, const char* mode) {
    return fopen(path, mode);
}

void asp_fastclose(FILE* f) {
    fclose(f);
}
