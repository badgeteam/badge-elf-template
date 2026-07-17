// SPDX-License-Identifier: MIT
// SPDX-CopyrightText: 2026 Badge.Team

#include "asp/http.h"

asp_err_t asp_net_is_connected(bool* out_connected) {
    // TODO: implement emulator network backend.
    if (!out_connected) {
        return ASP_ERR_PARAM;
    }
    *out_connected = false;
    return ASP_OK;
}

asp_err_t asp_http_get(const char* url, char* response, size_t max_len, int* out_status_code) {
    // TODO: implement emulator network backend.
    (void)url;
    (void)response;
    (void)max_len;
    (void)out_status_code;
    return ASP_ERR_UNSUPPORTED;
}

asp_err_t asp_http_post(const char* url, const char* body, char* response, size_t max_len, int* out_status_code) {
    // TODO: implement emulator network backend.
    (void)url;
    (void)body;
    (void)response;
    (void)max_len;
    (void)out_status_code;
    return ASP_ERR_UNSUPPORTED;
}
