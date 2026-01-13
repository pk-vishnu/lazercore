// Copyright 2024 SDK (@sdk66)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H
#include "rgb_matrix.h"
#include "utils/type_alchemy.h"
#define LED_ENABLE_PIN A5

void keyboard_pre_init_kb(void) {
    gpio_set_pin_output(LED_ENABLE_PIN);
    gpio_write_pin_high(LED_ENABLE_PIN);

    gpio_set_pin_output(LED_WIN_LOCK_PIN);
    gpio_write_pin_high(LED_WIN_LOCK_PIN);
    gpio_set_pin_output(LED_MAC_PIN);
    gpio_write_pin_high(LED_MAC_PIN);

    keyboard_pre_init_user();
}

void keyboard_pre_init_user(){
    debug_enable=true;
    init_type_alchemy();
}

void suspend_power_down_kb(void) {
    gpio_write_pin_low(LED_ENABLE_PIN);
    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
    gpio_write_pin_high(LED_ENABLE_PIN);
    suspend_wakeup_init_user();
}

void housekeeping_task_kb(void) {
    if (keymap_config.no_gui) {
        gpio_write_pin_low(LED_MAC_PIN);      // Turn on Mac LED
        gpio_write_pin_low(LED_WIN_LOCK_PIN);  // Turn on Win Lock LED
    } else {
        gpio_write_pin_high(LED_MAC_PIN);     // Turn off Mac LED
        gpio_write_pin_high(LED_WIN_LOCK_PIN); // Turn off Win Lock LED
    }
}
