
// SPDX-License-Identiefier: MIT
// SPDX-CopyRightText: 2025 Badge.Team

#include "asp/err.h"
#include <stddef.h>

static char const* const asp_err_id_table[] = {
    [ASP_OK] = "ASP_OK",
#define ASP_ERR_DEF(id, no, desc) [ASP_ERR_##id] = #id,
#include "asp/err.inc"
};

static char const* const asp_err_desc_table[] = {
    [ASP_OK] = "Ok",
#define ASP_ERR_DEF(id, no, desc) [ASP_ERR_##id] = desc,
#include "asp/err.inc"
};

// Get string ID of an `asp_err_t`.
char const* asp_err_id(asp_err_t ec) {
    if (ec < 0 || ec > sizeof(asp_err_id_table) / sizeof(char const* const)) {
        return NULL;
    } else {
        return asp_err_id_table[ec];
    }
}

// Get strinf description of an `asp_err_t`.
char const* asp_err_desc(asp_err_t ec) {
    if (ec < 0 || ec > sizeof(asp_err_desc_table) / sizeof(char const* const)) {
        return NULL;
    } else {
        return asp_err_desc_table[ec];
    }
}