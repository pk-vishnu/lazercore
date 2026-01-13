RGB_MATRIX_EFFECT(game_mode_effect)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static bool game_mode_effect(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  for (uint8_t i = led_min; i < led_max; i++) {
    rgb_matrix_set_color(i, 0x34, 0x01, 0x80);
  }

  rgb_matrix_set_color(47, 0xFF, 0x00, 0x00); // W
  rgb_matrix_set_color(51, 0xFF, 0x00, 0x00); // A
  rgb_matrix_set_color(52, 0xFF, 0x00, 0x00); // S
  rgb_matrix_set_color(53, 0xFF, 0x00, 0x00); // D

  return rgb_matrix_check_finished_leds(led_max);
}

#endif
