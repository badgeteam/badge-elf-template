// SPDX-License-Identifier: MIT
// SPDX-CopyrightText: 2026 Badge.Team

#include "asp/log.h"

#include <stdarg.h>
#include <stdio.h>

static void asp_log_write(char const* level, char const* tag, char const* fmt, va_list args) {
    fprintf(stderr, "%s %s: ", level, tag);
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\033[0m\n");
}

void asp_log_info(const char* tag, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    asp_log_write("\033[32mINFO ", tag, fmt, args);
    va_end(args);
}

void asp_log_warn(const char* tag, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    asp_log_write("\033[33mWARN ", tag, fmt, args);
    va_end(args);
}

void asp_log_error(const char* tag, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    asp_log_write("\033[31mERROR", tag, fmt, args);
    va_end(args);
}
