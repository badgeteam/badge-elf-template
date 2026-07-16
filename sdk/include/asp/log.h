// SPDX-License-Identifier: MIT
// SPDX-CopyrightText: 2026 Rene Schickbauer

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// Log an informational message.
void asp_log_info(const char* tag, const char* fmt, ...);

// Log a warning message.
void asp_log_warn(const char* tag, const char* fmt, ...);

// Log an error message.
void asp_log_error(const char* tag, const char* fmt, ...);

#ifdef __cplusplus
}
#endif
