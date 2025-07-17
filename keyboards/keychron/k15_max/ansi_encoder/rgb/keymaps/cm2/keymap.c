/* Copyright 2024 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "keychron_common.h"

enum layers {
    MAC_BASE,
    MAC_FN,
    WIN_BASE,
    WIN_FN,
    LEFT_LEFT,
    LEFT_MID,
    LEFT_RIGHT,
    RIGHT_LEFT,
    RIGHT_MID,
    RIGHT_RIGHT
};
// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_ansi_90(
        KC_MUTE,  KC_ESC,   KC_BRID,  KC_BRIU,  KC_MCTRL, KC_LNPAD, RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY, KC_MNXT,   KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_INS,             KC_DEL,
        MC_1,     KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,    KC_9,      KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_PGUP,
        MC_2,     KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,    KC_O,      KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_PGDN,
        MC_3,     KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,    KC_L,      KC_SCLN,  KC_QUOT,            KC_ENT,             KC_HOME,
        MC_4,     KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_B,     KC_N,    KC_M,      KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_UP,
        MC_5,     KC_LCTL,  KC_LOPTN,           KC_LCMMD, KC_SPC,  MO(MAC_FN),                    KC_SPC,             KC_RCMMD, KC_RCTL,             KC_LEFT,  KC_DOWN,  KC_RGHT),

    [MAC_FN] = LAYOUT_ansi_90(
        RGB_TOG,  _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,     KC_F8,    KC_F9,   KC_F10,   KC_F11, KC_F12,   _______,            _______,
        _______,  _______,  BT_HST1,  BT_HST2,  BT_HST3,  P2P4G,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  _______,  _______,  _______,  _______,  _______,  _______,            _______,            KC_END,
        _______,  _______,            _______,  _______,  _______,  _______,  BAT_LVL,  BAT_LVL,  NK_TOGG,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,            _______,  _______,  _______,                      _______,            _______,  _______,            _______,  _______,  _______),

    [WIN_BASE] = LAYOUT_ansi_90(
        KC_MUTE,  KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_INS,             KC_DEL,
        MC_1,     KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_PGUP,
        MC_2,     KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_PGDN,
        MC_3,     KC_CAPS,  LGUI_T(KC_A),     LALT_T(KC_S),     LCTL_T(KC_D),     LSFT_T(KC_F),     KC_G,     KC_H,     RSFT_T(KC_J),     LCTL_T(KC_K),     LALT_T(KC_L),     LGUI_T(KC_SCLN),  KC_QUOT,            KC_ENT,             KC_HOME,
        MC_4,     KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     LT(RIGHT_LEFT,KC_B),     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_UP,
        MC_5,     KC_LCTL,  KC_LWIN,            LT(LEFT_LEFT,KC_ESC),  LT(LEFT_MID,KC_SPC),  LT(LEFT_RIGHT,KC_TAB),                    LT(RIGHT_MID,KC_BSPC),             LT(RIGHT_RIGHT,KC_ENT),  MO(WIN_FN),            KC_LEFT,  KC_DOWN,  KC_RGHT),

    [WIN_FN] = LAYOUT_ansi_90(
        RGB_TOG,  _______,  KC_BRID,  KC_BRIU,  KC_TASK,  KC_FILE,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,            _______,
        _______,  _______,  BT_HST1,  BT_HST2,  BT_HST3,  P2P4G,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  _______,  _______,  _______,  _______,  _______,  _______,            _______,            KC_END,
        _______,  _______,            _______,  _______,  _______,  _______,  BAT_LVL,  BAT_LVL,  NK_TOGG,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,            _______,  _______,  _______,                      _______,            _______,  _______,            _______,  _______,  _______),

    [LEFT_LEFT] = LAYOUT_ansi_90(
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  KC_GRV,KC_NO,KC_NO,KC_HASH,KC_NO,               KC_EQL,KC_PPLS,KC_PSLS,KC_PAST,KC_PMNS,  _______,  _______,  _______,            _______,
        _______,  _______,  KC_1,KC_2,KC_3,KC_4,KC_5,                       KC_6,KC_7,KC_8,KC_9,KC_0,  _______,            _______,            _______,
        _______,  _______,           KC_LEFT,KC_UP,KC_DOWN,KC_RGHT,KC_NO,            KC_NO,KC_SPC,KC_NO,KC_COMM,KC_DOT,  _______,  _______,  _______,
        _______,  _______,  _______,            _______,  _______,  _______,                      _______,            _______,  _______,            _______,  _______,  _______),
    [LEFT_MID] = LAYOUT_ansi_90(
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  KC_LGUI,KC_HOME,KC_PGUP,LGUI(KC_4),KC_MS_WH_UP,            KC_AT,KC_UNDS,KC_PIPE,KC_GRV,KC_PERC,  _______,  _______,  _______,            _______,
        _______,  _______, LGUI(KC_1),LGUI(KC_2),LGUI(KC_3),KC_LSFT,KC_EQL,            KC_HASH,KC_MINS,KC_EXLM,KC_DQUO,KC_QUOT,  _______,            _______,            _______,
        _______,  _______,            KC_UNDO,KC_CUT,KC_COPY,KC_PSTE,KC_MS_WH_DOWN,            KC_ASTR,KC_DLR,KC_BSLS,KC_SLSH,KC_AMPR,  _______,  _______,  _______,
        _______,  _______,  _______,            _______,  _______,  _______,                      KC_NO,QK_MACRO_2,KC_APP,            _______,  _______,  _______),
    [LEFT_RIGHT] = LAYOUT_ansi_90(
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  KC_NO,KC_NUM,KC_PSCR,KC_SCRL,KC_PAUS,            KC_F17,KC_F9,KC_F10,KC_F11,KC_F12,  _______,  _______,  _______,            _______,
        _______,  _______,  LGUI(KC_1),LGUI(KC_2),LGUI(KC_3),TO(7),LCTL(KC_1),            KC_F16,KC_F5,KC_F6,KC_F7,KC_F8,  _______,            _______,            _______,
        _______,  _______,           KC_CAPS,LCTL(KC_EQL),LCTL(KC_0),KC_NO,TO(9),            KC_F15,KC_F1,KC_F2,KC_F3,KC_F4,  _______,  _______,  _______,
        _______,  _______,  _______,            _______,  _______,  _______,                      KC_F19,KC_F18,KC_F13,            _______,  _______,  _______),
    [RIGHT_LEFT] = LAYOUT_ansi_90(
        _______,  QK_BOOT,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______, KC_WAKE,KC_SLEP,KC_PWR,  _______,  _______,  _______,            _______,
        _______,  _______,  _______, _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,            _______,
        _______,  _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,            _______,  _______,  _______,                      _______,            _______,  _______,            _______,  _______,  _______),
    [RIGHT_MID] = LAYOUT_ansi_90(
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  KC_CAPS,KC_INS,KC_HOME,KC_PGUP,KC_NO,        KC_NO,KC_NO,KC_NO,KC_NO,KC_NO, _______,  _______,  _______,            _______,
        _______,  _______,  KC_LEFT,KC_UP,KC_DOWN,KC_RGHT,KC_NO,         QK_MACRO_0,KC_LSFT,KC_LCTL,KC_LALT,KC_LGUI, _______,            _______,            _______,
        _______,  _______,            KC_NO,KC_DEL,KC_END,KC_PGDN,KC_NO,           KC_NO,KC_NO,KC_NO,KC_NO,QK_MACRO_1,  _______,  _______,  _______,
        _______,  _______,  _______,            KC_NO,QK_MACRO_3,KC_NO,                      _______,            _______,  _______,            _______,  _______,  _______),
    [RIGHT_RIGHT] = LAYOUT_ansi_90(
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,   KC_EQL,KC_CIRC,KC_LT,KC_GT,KC_SCLN,            KC_NO,KC_WSCH,KC_NO,KC_NO,KC_WREF,  _______,  _______,  _______,            _______,
        _______,  _______, KC_LCBR,KC_RCBR,KC_LPRN,KC_RPRN,KC_AT,            KC_NO,KC_NO,KC_NO,KC_NO,KC_WBAK,  _______,            _______,            _______,
        _______,  _______,           KC_MINS,KC_EXLM,KC_LBRC,KC_RBRC,KC_NO,            KC_NO,KC_NO,KC_NO,KC_NO,KC_WFWD, _______,  _______,  _______,
        _______,  _______,  _______,            KC_NO,KC_NO,KC_NO,                      _______,            _______,  _______,            _______,  _______,  _______)
};

#if defined(ENCODER_MAP_ENABLE)
    const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
        [MAC_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
        [MAC_FN] = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
        [WIN_BASE]  = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
        [WIN_FN]  = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
      [   LEFT_LEFT]= { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
  [  LEFT_MID]= { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
  [  LEFT_RIGHT]= { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
   [ RIGHT_LEFT]= { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
   [ RIGHT_MID]= { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
   [ RIGHT_RIGHT]= { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    };
#endif // ENCODER_MAP_ENABLE

// clang-format on
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_keychron_common(keycode, record)) {
        return false;
    }
    return true;
}
