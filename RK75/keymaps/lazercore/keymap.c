// Copyright 2024 SDK (@sdk66)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H
#include "utils/indicators.h"
#include "utils/game_mode.h"
#include "utils/socd_cleaner.h"
#include "utils/audio_viz.h"
#include "utils/sentence_case.h"
#include "utils/type_alchemy.h"
#include "send_string.h"

enum custom_keycodes {
  GAME_MODE = SAFE_RANGE,
  AUDIO_VIZ = SAFE_RANGE+1,
  TOGG_SEN_CASE = SAFE_RANGE+2,
  TOGG_ALCH_TYPE = SAFE_RANGE+3,
  EM_DASH  = SAFE_RANGE+4
};

socd_cleaner_t socd_v = {{KC_W, KC_S}, SOCD_CLEANER_LAST};
socd_cleaner_t socd_h = {{KC_A, KC_D}, SOCD_CLEANER_LAST};
// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT( /* Base */
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_HOME,   KC_MUTE,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_DEL,  
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_PGUP,    
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,   KC_PGDN,          
        KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,            KC_UP,
        KC_LCTL,  KC_LCMD,  KC_LALT,                      KC_SPC,                                 KC_RALT,  MO(1),              KC_LEFT,  KC_DOWN,  KC_RGHT
        ),

    [1] = LAYOUT( /* FN -> RGB */
        _______,  TOGG_ALCH_TYPE,  UC_NEXT,  AC_TOGG ,  _______,  _______,  _______,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,   KC_SCRL,  QK_LAYER_LOCK,
        _______,  _______ ,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  EM_DASH,  _______,   _______,  _______,   
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_INS,    RGB_MOD,  KC_BRIU,  
        TOGG_SEN_CASE,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,             _______,  KC_BRID, 
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  MO(2),               RGB_VAI,
        _______,  GU_TOGG,  _______,                      EE_CLR,                                 _______,  _______,            RGB_SPD,  RGB_VAD,  RGB_SPI 
        ),

    [2] = LAYOUT( /* FN -> Bootloader*/
    QK_BOOTLOADER,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  AUDIO_VIZ,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  
    _______,  _______,  _______,  _______,  _______,  GAME_MODE,  _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______, 
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
    _______,  _______,  _______,                      _______,                                 _______,  _______,            _______,  _______,  _______ 
    ),

    [3] = LAYOUT( /* Audio Visualiser Layer */
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  AUDIO_VIZ,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______, 
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
    _______,  _______,  _______,                      _______,                                 _______,  _______,            _______,  _______,  _______ 
    ),
};
// clang-format on
#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},  // Volume control on layer 0
    [1] = {ENCODER_CCW_CW(KC_BRID, KC_BRIU)},  // Screen brightness on layer 1
    [2] = {ENCODER_CCW_CW(KC_MFFD, KC_MRWD)},  // Media fast forward/rewind on layer 2
    [3] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},  // Volume control on layer 3
};
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_type_alchemy(keycode, (char)(keycode - KC_A + 'a'), record->event.pressed)) {
        return false; // Skip further processing if type_alchemy handled the event
    }
    if (!process_socd_cleaner(keycode, record, &socd_v)) { return false; }
    if (!process_socd_cleaner(keycode, record, &socd_h)) { return false; }
    
    if (!process_sentence_case(keycode, record)) { return false; }
    if(game_mode_enabled){
        if(keycode == KC_LCMD){
            return false; // Block LGUI key
        }
    }
    if (keycode == GAME_MODE && record->event.pressed) {
        if (game_mode_enabled) {
            socd_cleaner_enabled = false;
            disable_game_mode();
            gpio_write_pin_high(LED_WIN_LOCK_PIN);
        } else {
            socd_cleaner_enabled = true;
            enable_game_mode();
            socd_cleaner_enabled = true;
            gpio_write_pin_low(LED_WIN_LOCK_PIN);
        }
        return false;
    }
    if (keycode == AUDIO_VIZ && record->event.pressed) {
        if(audio_viz_enabled){
            disable_audio_viz();
        } else { 
            enable_audio_viz();
        }
        return false;
    }
    if (keycode == TOGG_SEN_CASE && record->event.pressed) {
        sentence_case_toggle();
        return false;
    }

    if (keycode == TOGG_ALCH_TYPE && record->event.pressed){
        toggle_type_alchemy();
        return false;
    }

    if (keycode == EM_DASH && record->event.pressed) {
        send_unicode_string("—");
        return false;
    }
    return true;
}

