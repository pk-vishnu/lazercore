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
    if (length < 3) return false;
    if (data[0] != AUDIO_RIPPLE_MAGIC) return false;
    if (data[1] != AUDIO_RIPPLE_VERSION) return false;

    uint8_t type = data[2];

    if (type == RIPPLE_PKT_AUDIO) {
        if (length < sizeof(audio_ripple_frame_t)) return false;

        const audio_ripple_frame_t *frame = (const audio_ripple_frame_t *)data;
        audio_ripple_set_frame(frame);
        return true;
    }

    if (type == RIPPLE_PKT_CONTROL) {
        if (length < sizeof(ripple_control_packet_t)) return false;

        const ripple_control_packet_t *pkt = (const ripple_control_packet_t *)data;
        audio_ripple_handle_control(pkt);
        return true;
    }

    return false;
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

// geometry (setting center)
static float center_x = 0.0f;
static float center_y = 0.0f;
static bool geometry_ready = false;

static void audio_ripple_compute_center(void) {
    uint8_t led_g = 55;
    uint8_t led_h = 56;

    center_x = (g_led_config.point[led_g].x + g_led_config.point[led_h].x) * 0.5f;
    center_y = (g_led_config.point[led_g].y + g_led_config.point[led_h].y) * 0.5f;

    geometry_ready = true;
}

// visual parameters
typedef struct {
    float speed;
    float decay;
    float base_width;
    float mid_width_gain;
    float sparkle_strength;
    float sparkle_scale;
    float bass_threshold;
} ripple_params_t;

static ripple_params_t params = {
    .speed = 2.5f,
    .decay = 0.97f,
    .base_width = 6.0f,
    .mid_width_gain = 14.0f,
    .sparkle_strength = 0.6f,
    .sparkle_scale = 200.0f,
    .bass_threshold = 20.0f,
};

#define MAX_RIPPLES 4

typedef struct {
    float radius;
    float energy;
    bool  active;
} ripple_t;

static ripple_t ripples[MAX_RIPPLES];

void audio_ripple_render(void) {
    if (!audio_ripple_enabled || !frame_valid) {
        return;
    }

    if (!geometry_ready) {
        audio_ripple_compute_center();
    }

    uint8_t bass = current_frame.bands[0];
    float bass_norm = bass / 255.0f;

    float mid  = (current_frame.bands[2] + current_frame.bands[3]) * 0.5f / 255.0f;
    float high = (current_frame.bands[4] + current_frame.bands[5]) * 0.5f / 255.0f;

    if (bass > params.bass_threshold) {
        // Find a free ripple slot
        for (int i = 0; i < MAX_RIPPLES; i++) {
            if (!ripples[i].active) {
                ripples[i].active = true;
                ripples[i].radius = 0.0f;
                ripples[i].energy = bass_norm;
                break;
            }
        }
    }

    for (int i = 0; i < MAX_RIPPLES; i++) {
        if (!ripples[i].active) continue;

        ripples[i].radius += params.speed;
        ripples[i].energy *= params.decay;

        if (ripples[i].energy < 0.01f) {
            ripples[i].active = false;
        }
    }

    for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        float dx = g_led_config.point[i].x - center_x;
        float dy = g_led_config.point[i].y - center_y;
        float dist = sqrtf(dx * dx + dy * dy);

        float ring_width = params.base_width + mid * params.mid_width_gain;
        float brightness = 0.0f;

        for (int r = 0; r < MAX_RIPPLES; r++) {
            if (!ripples[r].active) continue;

            float diff = fabsf(dist - ripples[r].radius);
            if (diff < ring_width) {
                brightness += ripples[r].energy * (1.0f - diff / ring_width);
            }
        }

        // High-frequency sparkle on outer keys
        float sparkle = high * (dist / params.sparkle_scale);
        brightness += sparkle * params.sparkle_strength;

        if (brightness > 1.0f) brightness = 1.0f;

        uint8_t r = (uint8_t)(brightness * 255.0f * bass_norm);
        uint8_t g = (uint8_t)(brightness * 80.0f  * mid);
        uint8_t b = (uint8_t)(brightness * 255.0f * high);

        rgb_matrix_set_color(i, r, g, b);
    }
}

void audio_ripple_handle_control(const ripple_control_packet_t *pkt) {
    float v = pkt->value;

    switch (pkt->param) {
        case RIPPLE_PARAM_SPEED:
            params.speed = v / 100.0f;
            break;

        case RIPPLE_PARAM_DECAY:
            params.decay = v / 1000.0f;
            break;

        case RIPPLE_PARAM_BASE_WIDTH:
            params.base_width = v / 100.0f;
            break;

        case RIPPLE_PARAM_MID_GAIN:
            params.mid_width_gain = v / 100.0f;
            break;

        case RIPPLE_PARAM_SPARKLE:
            params.sparkle_strength = v / 100.0f;
            break;
    }
}
