// SPDX-License-Identifier: CC0
// SPDX-CopyRightText: 2025 Julian Scheffers

#include <stdint.h>
#include <stdio.h>
#include <sys/unistd.h>
#include "asp/display.h"
#include "asp/input.h"
#include "pax_gfx.h"

int main(int argc, char** argv) {
    printf("Hello, World!\n");

    pax_buf_t* gfx;
    asp_disp_get_pax_buf(&gfx);
    pax_background(gfx, 0xffff3f3f);

    char const* const msg = "Hello, World!";
    pax_draw_text_adv(gfx, 0xffffffff, pax_font_saira_condensed, pax_font_saira_condensed->default_size,
                      pax_buf_get_widthf(gfx) / 2, pax_buf_get_heightf(gfx) / 2, msg, strlen(msg), PAX_ALIGN_CENTER,
                      PAX_ALIGN_CENTER, -1);

    asp_disp_write_pax(gfx);

    while (1) {
        asp_input_event_t event;
        asp_input_poll(&event, INT64_MAX);
        if (event.type == ASP_INPUT_EVENT_TYPE_NAVIGATION && event.args_navigation.state &&
            event.args_navigation.key == ASP_INPUT_NAVIGATION_KEY_ESC) {
            break;
        }
    }

    return 0;
}