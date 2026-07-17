
# SPDX-License-Identifier: CC0
# SPDX-CopyRightText: 2025 Julian Scheffers

if(EMULATOR_BUILD)
    add_compile_options(-g)
    add_subdirectory(sdk/pax-gfx)

    add_library(badge SHARED
        sdk/emulator/src/audio.c
        sdk/emulator/src/device.c
        sdk/emulator/src/display.c
        sdk/emulator/src/emulator.c
        sdk/emulator/src/err.c
        sdk/emulator/src/file.c
        sdk/emulator/src/http.c
        sdk/emulator/src/input.c
        sdk/emulator/src/led.c
        sdk/emulator/src/log.c
        sdk/emulator/src/orientation.c
        sdk/emulator/src/power.c
    )
    target_include_directories(badge PRIVATE sdk/emulator/include)
    target_include_directories(badge PUBLIC sdk/include)
    target_link_libraries(badge PUBLIC pax_gfx)
    target_link_libraries(badge PRIVATE -lSDL3)
    install(TARGETS badge pax_gfx DESTINATION .)

    link_libraries(-lpthread -lm badge pax_gfx)
else()
    add_compile_options(-march=rv32imafc_zicsr_zifencei -mabi=ilp32f -fPIC -mno-relax)

    add_link_options(-nostartfiles -Wl,-emain)
    link_libraries(-L${CMAKE_CURRENT_LIST_DIR}/lib -lbadge -lc -lpthread -lgcc -lm -lpax-gfx -lpax-codecs)
    include_directories(sdk/include sdk/pax-gfx/core/include)
endif()
