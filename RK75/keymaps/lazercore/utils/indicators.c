#include "indicators.h"
#include "sentence_case.h"
#include "type_alchemy.h"

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t layer = get_highest_layer(layer_state | default_layer_state);

    for (uint8_t i = led_min; i < led_max; i++) {
        if (layer == 0) {
            if (i == 79) {
                rgb_matrix_set_color(i, 0, 0, 0);
            }

            if (is_sentence_case_on() && i == 50) rgb_matrix_set_color(i, 0xFF, 0x00, 0x00);

            if (is_type_alchemy_on() && i == 20) {
                uint8_t unicode_mode = get_unicode_input_mode();
                if (unicode_mode == 4) rgb_matrix_set_color(i, 0x00, 0xFF, 0x00);
                else if (unicode_mode == 1) rgb_matrix_set_color(i, 0xFF, 0x00, 0x00);
                else if (unicode_mode == 0) rgb_matrix_set_color(i, 0x00, 0x00, 0xFF);
                else rgb_matrix_set_color(i, 0xFF, 0xFF, 0x00);
            }

            if (autocorrect_is_enabled() && i == 18) rgb_matrix_set_color(i, 0x00, 0xFF, 0x00);
        }

        if (layer == 1) {
            if (i == 6) rgb_matrix_set_color(i, 0xFF, 0xFF, 0xFF);
            else if (i == 3 || i == 63) rgb_matrix_set_color(i, 0xE4, 0x00, 0xFF);
            else if (i == 2 || i == 4) rgb_matrix_set_color(i, 0xFB, 0x98, 0xFF);
            else if (i == 64) rgb_matrix_set_color(i, 0xFF, 0x00, 0x12);
            else if (i == 50 || i == 19 || i == 20 || i == 18) rgb_matrix_set_color(i, 0xFF, 0x00, 0x00);
        }

        if (layer == 2) {
            if (i == 21 || i == 55 || i == 79) {
                rgb_matrix_set_color(i, 0xFF, 0x00, 0x00);
            }
        }
    }

    if (layer == 3) {
        audio_ripple_render();
    }

    return false;
}
