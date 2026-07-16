
# SPDX-License-Identifier: CC0
# SPDX-CopyRightText: 2025 Julian Scheffers

cmake_minimum_required(VERSION 3.15.0)

# Optional; for IDE/language server integration.
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

project(badge_elf_app C CXX)

# This sets up the SDK for the app and the emulator; it is required.
include(sdk/sdk.cmake)

# PAX graphics is optional; remove these two lines if you don't want to use it.
link_libraries(pax-gfx)

add_executable(main
    src/main.c
)

install(TARGETS main DESTINATION .)
