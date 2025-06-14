#include QMK_KEYBOARD_H
#include "features/orbital_mouse.h"
#include "features/socd_cleaner.h"
#if __has_include("keymap.h")
#    include "keymap.h"
#endif

socd_cleaner_t socd_v = {{KC_W, KC_S}, SOCD_CLEANER_LAST};
socd_cleaner_t socd_h = {{KC_A, KC_D}, SOCD_CLEANER_LAST};

void housekeeping_task_user(void) {
    orbital_mouse_task();
}

// This is to keep state between callbacks, when it is 0 the
// initial RGB flash is finished
uint8_t _hue_countdown = 50;

// These are to keep track of user selected color, so we
// can restore it after RGB flash
uint8_t _hue;
uint8_t _saturation;
uint8_t _value;
bool socd_cleaner_toggled;

// Do a little 2.5 seconds display of the different colors
// Use the deferred executor so the LED flash dance does not
// stop us from using the keyboard.
// https://docs.qmk.fm/#/custom_quantum_functions?id=deferred-executor-registration
uint32_t flash_led(uint32_t next_trigger_time, void *cb_arg) {
    rgblight_sethsv(_hue_countdown * 5, 230, 70);
    _hue_countdown--;
    if (_hue_countdown == 0) {
        // Finished, reset to user chosen led color
        rgblight_sethsv(_hue, _saturation, _value);
        return 0;
    } else {
        return 50;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Your macros ...
    if (keycode == SOCDOFF && record->event.pressed) {
        socd_cleaner_enabled = false;
            socd_cleaner_toggled = false;
            rgblight_sethsv(120, 230, 1);
            return true;
    }
    if (keycode == SOCDON && record->event.pressed) {
        socd_cleaner_enabled = true;
        socd_cleaner_toggled = true;
        rgblight_sethsv(180, 230, 1);

        return true;
    }
    if (!process_socd_cleaner(keycode, record, &socd_v)) {
        return false;
    }
    if (!process_socd_cleaner(keycode, record, &socd_h)) {
        return false;
    }
    if (!process_orbital_mouse(keycode, record)) { return false; }
    switch (keycode) {
        case QK_MACRO_0:
            if (record->event.pressed) {
                SEND_STRING(" => ");
            }
            break;
        case QK_MACRO_1:
            if (record->event.pressed) {
                SEND_STRING("/>");
            }
            break;
        case QK_MACRO_2:  // Next sentence macro.
            if (record->event.pressed) {
                SEND_STRING(". ");
                add_oneshot_mods(MOD_BIT(KC_LSFT));  // Set one-shot mod for shift.
            }
    }
    return true;
}


void keyboard_post_init_user(void) {
    debug_enable=true;
    debug_matrix=true;
    debug_keyboard=true;
    // debug_mouse=true;

    // Store user selected rgb hsv:
    _hue        = rgblight_get_hue();
    _saturation = rgblight_get_sat();
    _value      = rgblight_get_val();

    // Flash a little on start
    defer_exec(50, flash_led, NULL);
}

uint8_t get_hue(uint8_t layer) {
    if (socd_cleaner_enabled && layer == 7) {
        return 180;
    }
    switch (layer) {
        case 8:
            return 30;
        case 7:
            return 120;
        default:
            return 0;
    }
}

uint8_t get_val(uint8_t layer) {
    switch (layer) {
        case 8:
        case 7:
            return 2;
        default:
            return 0;
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    if (!IS_LAYER_ON_STATE(state, 7) && !IS_LAYER_ON_STATE(state, 8)) {
        socd_cleaner_enabled = false;
    } else {
        socd_cleaner_enabled = socd_cleaner_toggled;
    }
    uint8_t sat          = rgblight_get_sat();
    uint8_t val          = get_val(get_highest_layer(state));
    uint8_t hue          = get_hue(get_highest_layer(state));
    rgblight_sethsv(hue, sat, val);
    return state;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x5_3(
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        LGUI_T(KC_A), LALT_T(KC_S), LCTL_T(KC_D), LSFT_T(KC_F), KC_G,   KC_H, RSFT_T(KC_J), LCTL_T(KC_K), LALT_T(KC_L), LGUI_T(KC_SCLN),
        KC_Z,    KC_X,    KC_C,    KC_V,    LT(3,KC_B),                 KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,
                       LT(1,KC_ESC), LT(2,KC_SPC), LT(3,KC_TAB),        LT(4,KC_DEL), LT(5,KC_BSPC), LT(6,KC_ENT)
    ),
    [1] = LAYOUT_split_3x5_3(
        KC_GRV,  KC_NO,   KC_NO,   KC_HASH, KC_NO,       KC_EQL,  KC_PPLS, KC_PSLS, KC_PAST, KC_PMNS,
        KC_1,    KC_2,    KC_3,    KC_4,        KC_5,    KC_6,    KC_7,    KC_8,    KC_9, KC_0,
        KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT, KC_NO,       KC_NO,   KC_SPC,  KC_NO,   KC_COMM, KC_DOT,
                              KC_NO, KC_NO, KC_NO,       KC_NUM, KC_BSPC, KC_ENT
    ),
    [2] = LAYOUT_split_3x5_3(
        KC_LGUI, KC_HOME, KC_PGUP, LGUI(KC_4),   MS_WHLU,     KC_AT,   KC_UNDS, KC_PIPE, KC_GRV,  KC_PERC,
        LGUI(KC_1), LGUI(KC_2), LGUI(KC_3), KC_LSFT, KC_EQL,    KC_HASH, KC_MINS, KC_EXLM,   KC_DQUO,KC_QUOT,
        KC_UNDO,   KC_CUT,  KC_COPY, KC_PSTE,   MS_WHLD,     KC_ASTR, KC_DLR,  KC_BSLS, KC_SLSH, KC_AMPR,
                                KC_NO, KC_NO, KC_NO,     KC_NO, QK_MACRO_2, KC_APP
    ),
    [3] = LAYOUT_split_3x5_3(
        KC_NO,   KC_NUM,  KC_PSCR, KC_SCRL, KC_PAUS,     KC_F17,  KC_F9,   KC_F10,  KC_F11,  KC_F12,
        KC_CAPS, LCTL(KC_EQL), LCTL(KC_0), LCTL(KC_1), TO(7), KC_F16, KC_F5, KC_F6, KC_F7, KC_F8,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   TO(0),       KC_F15,  KC_F1,   KC_F2,   KC_F3,   KC_F4,
                              KC_NO, KC_NO, KC_NO,       KC_F19, KC_F18, KC_F13
    ),
    [4] = LAYOUT_split_3x5_3(
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,       KC_NO,   KC_NO,   KC_WAKE,   KC_SLEP,   KC_PWR,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                              KC_NO, KC_NO, KC_NO,       KC_NO, KC_NO, KC_NO
    ),
    [5] = LAYOUT_split_3x5_3(
        KC_CAPS, KC_INS,  KC_HOME, KC_PGUP, KC_NO,       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT, KC_NO,       QK_MACRO_0, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,
        KC_NO,   KC_DEL,  KC_END,  KC_PGDN, KC_NO,       KC_NO,   KC_NO,   KC_NO,   KC_NO,   QK_MACRO_1,
                              KC_NO, KC_NO, KC_NO,       KC_NO, KC_NO, KC_NO
    ),
    [6] = LAYOUT_split_3x5_3(
        KC_EQL,  KC_CIRC, KC_LT,   KC_GT,   KC_SCLN,     KC_NO, KC_WSCH, OM_W_D, OM_W_U, KC_WREF,
        KC_LCBR, KC_RCBR, KC_LPRN, KC_RPRN, KC_AT,       KC_NO, OM_L,    OM_U,     OM_R,    KC_WBAK,
        KC_MINS, KC_EXLM, KC_LBRC, KC_RBRC, KC_NO,       KC_NO,  KC_NO,  OM_D, KC_NO,  KC_WFWD,
                        MS_BTN2, MS_BTN1, MS_BTN3,       KC_NO,  KC_NO, KC_NO
    ),
    // Gaming
    [7] = LAYOUT_split_3x5_3(
        KC_ESC,  KC_Q,    KC_X,    KC_E,    KC_R,        KC_Y,    KC_U,    KC_I,    SOCDON,    SOCDOFF,
        KC_LSFT, KC_A,    KC_W,    KC_D,    KC_F,        KC_H,    KC_J,    KC_K,    KC_L,    LGUI(KC_F),
        KC_LCTL, KC_Z,    KC_S,    KC_C,    KC_V,        KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
                                KC_1, KC_SPC, MO(8),      KC_ESC, KC_BSPC, TO(0)
    ),
    // Gaming - Numbers
    [8] = LAYOUT_split_3x5_3(
        KC_7,  KC_8,    KC_4,    KC_9,    KC_T,        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        KC_2, KC_3,    KC_4,    KC_5,    KC_TAB,        KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,
        KC_LCTL, KC_Z,    KC_X,    KC_6,    TO(0),        KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
                                KC_1, KC_NO, KC_NO,      KC_ESC, TO(0), TO(0)
    )
};
