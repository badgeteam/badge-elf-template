
# SPDX-License-Identifier: CC0
# SPDX-CopyRightText: 2025 Julian Scheffers

if(EMULATOR_BUILD)
    add_compile_options(-g)
    add_definitions(-DEMULATOR_BUILD=1)
    
    add_subdirectory(sdk/pax-gfx)
    
    # Need to inform codecs how to get zlib.
    add_library(z INTERFACE)
    add_subdirectory(sdk/pax-codecs/zlib)
    target_link_libraries(z INTERFACE zlib)
    # Alias that explicitly exists for the old, broken (but still in use) codecs.
    add_library(pax_graphics INTERFACE)
    target_link_libraries(pax_graphics INTERFACE pax_gfx)
    # Aforementioned PNG codec.
    add_subdirectory(sdk/pax-codecs)

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
    install(TARGETS badge pax_gfx pax_codecs DESTINATION lib)

    link_libraries(-lpthread -lm badge pax_gfx pax_codecs)
else()
    add_compile_options(-march=rv32imafc_zicsr_zifencei -mabi=ilp32f -fPIC -mno-relax)

    add_link_options(-nostartfiles -Wl,-emain -shared -nodefaultlibs)
    link_libraries(-L${CMAKE_CURRENT_LIST_DIR}/lib -lbadge -lc -lpthread -lgcc -lm -lpax-gfx -lpax-codecs)
    include_directories(
        sdk/include
        sdk/pax-gfx/core/include
        sdk/pax-codecs/include
    )
endif()
