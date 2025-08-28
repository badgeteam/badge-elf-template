
// SPDX-License-Identiefier: MIT
// SPDX-CopyRightText: 2025 Badge.Team

#pragma once

// Error status codes returned by `asp_` functions.
typedef enum {
    ASP_OK = 0,
#define ASP_ERR_DEF(id, no, desc) ASP_ERR_##id = no,
#include "err.inc"
} asp_err_t;

// Return the error code if `ec` is an error.
#define ASP_RETURN_ON_ERR(ec, ...)    \
    ({                                \
        asp_err_t asp_err_rc_ = (ec); \
        if (asp_err_rc_ != ASP_OK) {  \
            __VA_ARGS__;              \
            return asp_err_rc_;       \
        }                             \
    })

// Get string ID of an `asp_err_t`.
char const* asp_err_id(asp_err_t ec);
// Get strinf description of an `asp_err_t`.
char const* asp_err_desc(asp_err_t ec);
