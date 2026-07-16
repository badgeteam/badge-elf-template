
# SPDX-License-Identifier: CC0
# SPDX-CopyRightText: 2025 Julian Scheffers

if(EMULATOR_BUILD)
    add_subdirectory(sdk/pax-gfx)
    # So that you can also link the the name `pax-gfx`.
    add_library(pax-gfx INTERFACE)
    target_link_libraries(pax-gfx INTERFACE pax_gfx)

    add_library(badge SHARED
        sdk/emulator/audio.c
        sdk/emulator/device.c
        sdk/emulator/display.c
        sdk/emulator/err.c
        sdk/emulator/file.c
        sdk/emulator/http.c
        sdk/emulator/input.c
        sdk/emulator/led.c
        sdk/emulator/log.c
        sdk/emulator/orientation.c
        sdk/emulator/power.c
    )
    target_include_directories(badge PUBLIC sdk/include)
    target_link_libraries(badge PUBLIC pax_gfx)

    link_libraries(-lpthread -lm badge)
else()
    add_compile_options(-march=rv32imafc_zicsr_zifencei -mabi=ilp32f -fPIC -mno-relax)

    add_link_options(-nostartfiles -Wl,-emain)
    link_libraries(-L${CMAKE_CURRENT_LIST_DIR}/lib -lbadge -lc -lpthread -lgcc -lm -lpax-codecs)
    include_directories(sdk/include sdk/pax-gfx/core/include)
endif()
