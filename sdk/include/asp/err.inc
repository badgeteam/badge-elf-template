
// SPDX-License-Identiefier: MIT
// SPDX-CopyRightText: 2025 Badge.Team

#ifndef ASP_ERR_DEF
#define ASP_ERR_DEF(id, num, desc)
#endif

ASP_ERR_DEF(FAIL, 1, "Failed")
ASP_ERR_DEF(NOMEM, 2, "Out of memory")
ASP_ERR_DEF(PARAM, 3, "Invalid parameter")
ASP_ERR_DEF(UNSUPPORTED, 4, "Not supported")
ASP_ERR_DEF(NOT_FOUND, 5, "Not found")

#undef ASP_ERR_DEF
