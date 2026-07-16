
// SPDX-License-Identiefier: MIT
// SPDX-CopyRightText: 2025 Badge.Team

#include "asp/err.h"

// Get string ID of an `asp_err_t`.
char const* asp_err_id(asp_err_t ec) {
    switch (ec) {
        case ASP_OK:
            return "OK";
#define ASP_ERR_DEF(id, no, desc) \
    case ASP_ERR_##id:            \
        return #id;
#include "asp/err.inc"
        default:
            return "UNKNOWN";
    }
}

// Get strinf description of an `asp_err_t`.
char const* asp_err_desc(asp_err_t ec) {
    switch (ec) {
        case ASP_OK:
            return "Success";
#define ASP_ERR_DEF(id, no, desc) \
    case ASP_ERR_##id:            \
        return desc;
#include "asp/err.inc"
        default:
            return "Unknown error";
    }
}
