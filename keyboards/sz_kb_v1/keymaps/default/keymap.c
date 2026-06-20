// Copyright 2025 saminzachariah
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers {
    _BASE,
    _FN,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // clang-format off
    [_BASE] = LAYOUT(
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,
        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,
        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,
        KC_MUTE, KC_LGUI, KC_LALT, KC_LCTL, MO(_FN), KC_SPC
    ),
    [_FN] = LAYOUT(
        RM_TOGG, RM_NEXT, RM_PREV, RM_VALU, RM_VALD, _______,
        _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, QK_BOOT
    )
    // clang-format on
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_FN]   = {ENCODER_CCW_CW(RM_VALD, RM_VALU)},
};
#endif
