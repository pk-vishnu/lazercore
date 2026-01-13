/*
 * Copyright 2025 Lazercore
 * Author: P K, Vishnu
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "audio_ripple.h"

#include "quantum.h"
#include "rgb_matrix.h"
#include "print.h"
#include <math.h>

#ifdef VIA_ENABLE
#include "via.h"
#endif

static bool audio_ripple_enabled = false;

static audio_ripple_frame_t current_frame;
static bool frame_valid = false;

void audio_ripple_enable(void){
    audio_ripple_enabled = true;
    rgb_matrix_set_color(21, 255, 0, 0);
    layer_clear();
    layer_on(3);
}

void audio_ripple_disable(void){
    audio_ripple_enabled = false;
    layer_clear();
    layer_on(0);
}

bool audio_ripple_is_enabled(void){
    return audio_ripple_enabled;
}

void audio_ripple_set_frame(const audio_ripple_frame_t *frame){
    if(!frame){
        return;
    }

    current_frame = *frame;
    frame_valid = true;
}

#ifdef RAW_ENABLE
bool via_command_kb(uint8_t *data, uint8_t length) {
    // Copy Audio Data when on Layer3 [audio visualiser layer]
    if (get_highest_layer(layer_state | default_layer_state) == 3) {
        // We expect exactly the audio ripple frame payload
        if (length < sizeof(audio_ripple_frame_t)) {
            return false;
        }

        const audio_ripple_frame_t *frame = (const audio_ripple_frame_t *)data;

        if (frame->magic != AUDIO_RIPPLE_MAGIC) {
            return false;
        }

        if (frame->version != AUDIO_RIPPLE_VERSION) {
            return false;
        }

        if (frame->band_count != AUDIO_RIPPLE_BANDS) {
            return false;
        }

        audio_ripple_set_frame(frame);

        return true;
    } else {
        return false;
    }
}
#   if !defined(VIA_ENABLE)
// Weak override for raw_hid_receive_user, allowing keymap override
__attribute__((weak)) bool raw_hid_receive_user(uint8_t *data, uint8_t length) {
    return false;
}

// Simple implementation of raw_hid_receive with user-level override
void raw_hid_receive(uint8_t *data, uint8_t length) {
    // Check if keymap-level user function is implemented
    if (raw_hid_receive_user(data, length)) return;

    // If VIA is enabled and the custom function doesn't handle it, handle it here
    if (via_command_kb(data, length)) return;

    // If neither handler takes care of the data, respond with default action
    // You may want to implement a default behavior here (e.g., default raw HID handling)
    data[0] = 0;  // Clear the first byte
    replaced_hid_send(data, length); // Send the data back (or handle as necessary)
}
#   endif
#endif


bool rgb_matrix_indicators_user(void) {
    audio_ripple_render();
    return false;
}

static float center_x = 0.0f;
static float center_y = 0.0f;
static bool geometry_ready = false;

#define RIPPLE_SPEED  1.2f
#define RIPPLE_DECAY  0.92f
#define BASS_TRIGGER 40

static void audio_ripple_compute_center(void) {
    uint8_t led_g = 55;
    uint8_t led_h = 56;

    center_x = (g_led_config.point[led_g].x + g_led_config.point[led_h].x) * 0.5f;
    center_y = (g_led_config.point[led_g].y + g_led_config.point[led_h].y) * 0.5f;

    geometry_ready = true;
}

static float ripple_radius = 0.0f;
static float ripple_energy = 0.0f;

void audio_ripple_render(void) {
    if (!audio_ripple_enabled || !frame_valid) {
        return;
    }
    if (!geometry_ready) {
        audio_ripple_compute_center();
    }

    uint8_t bass = current_frame.bands[0];

    if (bass > BASS_TRIGGER) {
        ripple_energy = bass / 255.0f;
        ripple_radius = 0.0f;
    }

    ripple_energy *= RIPPLE_DECAY;
    ripple_radius += RIPPLE_SPEED;

    if (ripple_energy < 0.01f) {
        ripple_energy = 0.0f;
    }

    for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        float dx = g_led_config.point[i].x - center_x;
        float dy = g_led_config.point[i].y - center_y;

        float dist = sqrtf(dx * dx + dy * dy);

        float diff = fabsf(dist - ripple_radius);

        float brightness = 0.0f;

        if (diff < 6.0f) {
            brightness = ripple_energy * (1.0f - diff / 6.0f);
        }
        uint8_t value = (uint8_t)(brightness * 255.0f);
        rgb_matrix_set_color(i, value, value, value);
    }
}
