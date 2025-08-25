
# SPDX-License-Identifier: CC0
# SPDX-CopyRightText: 2025 Julian Scheffers

cmake_minimum_required(VERSION 3.15.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS true)
set(CMAKE_C_COMPILER riscv32-esp-elf-cc)
set(CMAKE_CXX_COMPILER riscv32-esp-elf-c++)

project(badge_elf_app C)

add_compile_options(-march=rv32imafc_zicsr_zifencei -mabi=ilp32f -fPIC -mno-relax)
add_link_options(-nodefaultlibs -nostartfiles -lbadge -L${CMAKE_CURRENT_LIST_DIR}/sdk -Wl,-emain)

add_library(main SHARED
    src/main.c
)
target_include_directories(main PUBLIC sdk/include)
