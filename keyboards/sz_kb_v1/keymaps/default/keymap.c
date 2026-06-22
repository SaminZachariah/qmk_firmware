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
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
        KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_MUTE,          KC_MPLY, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                          KC_LGUI, KC_LALT, KC_LCTL, MO(_FN), KC_ENT,           KC_SPC,  MO(_FN), KC_RCTL, KC_RALT, KC_RGUI
    ),
    [_FN] = LAYOUT(
        QK_BOOT, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                              KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        RM_TOGG, RM_NEXT, RM_PREV, RM_VALU, RM_VALD, _______,                             _______, _______, KC_UP,   _______, _______, KC_F12,
        _______, RM_HUEU, RM_HUED, RM_SATU, RM_SATD, _______,                             _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,            _______, _______, _______, _______, _______, _______, _______,
                          _______, _______, _______, _______, _______,            _______, _______, _______, EH_LEFT, EH_RGHT
    )

    // clang-format on
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_PGUP, KC_PGDN)},
    [_FN]   = {ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_BRID, KC_BRIU)},
};
#endif
