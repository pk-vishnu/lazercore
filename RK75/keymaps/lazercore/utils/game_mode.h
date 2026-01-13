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

#ifndef GAME_MODE_H
#define GAME_MODE_H

#include "quantum.h"

extern bool game_mode_enabled;

void enable_game_mode(void);
void disable_game_mode(void);

#endif
