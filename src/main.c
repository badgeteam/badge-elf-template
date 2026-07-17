// SPDX-License-Identifier: CC0
// SPDX-CopyRightText: 2025 Julian Scheffers

#include <stdint.h>
#include <stdio.h>
#include <sys/unistd.h>
#include <unistd.h>
#include "asp/display.h"
#include "asp/input.h"
#include "asp/input_types.h"
#include "pax_gfx.h"

int main(int argc, char** argv) {
    printf("Hello, World!\n");

    pax_buf_t* gfx;
    asp_disp_get_pax_buf(&gfx);
    pax_background(gfx, 0xffff3f3f);

    while (1) {

        char const* const msg = "Hello, World!";
        pax_draw_text_adv(gfx, 0xffffffff, pax_font_saira_condensed, pax_font_saira_condensed->default_size,
                          pax_buf_get_widthf(gfx) / 2, pax_buf_get_heightf(gfx) / 2, msg, strlen(msg), PAX_ALIGN_CENTER,
                          PAX_ALIGN_CENTER, -1);

        asp_disp_write_pax(gfx);
        pax_background(gfx, 0xffff3f3f);

        asp_input_event_t event;
        asp_input_poll(&event, INT64_MAX);
        if (event.type == ASP_INPUT_EVENT_TYPE_NAVIGATION &&
            (event.args_navigation.key == ASP_INPUT_NAVIGATION_KEY_ESC ||
             event.args_navigation.key == ASP_INPUT_NAVIGATION_KEY_F1)) {
            break;
        }

        if (event.type == ASP_INPUT_EVENT_TYPE_KEYBOARD) {
            pax_draw_text_adv(gfx, 0xffffffff, pax_font_saira_regular, pax_font_saira_regular->default_size,
                              pax_buf_get_widthf(gfx) / 2, pax_buf_get_heightf(gfx), event.args_keyboard.utf8,
                              strlen(event.args_keyboard.utf8), PAX_ALIGN_CENTER, PAX_ALIGN_END, -1);
        }
    }

    return 0;
}