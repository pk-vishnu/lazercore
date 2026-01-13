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

#pragma once

#include<stdint.h>
#include<stdbool.h>

#define AUDIO_RIPPLE_MAGIC 0xA5
#define AUDIO_RIPPLE_VERSION 0x01
#define AUDIO_RIPPLE_BANDS 6

typedef struct{
    uint8_t magic;
    uint8_t version;
    uint8_t band_count;
    uint8_t bands[AUDIO_RIPPLE_BANDS];
} audio_ripple_frame_t;

void audio_ripple_enable(void);
void audio_ripple_disable(void);
bool audio_ripple_is_enabled(void);

void audio_ripple_set_frame(const audio_ripple_frame_t *frame);
void audio_ripple_render(void);
