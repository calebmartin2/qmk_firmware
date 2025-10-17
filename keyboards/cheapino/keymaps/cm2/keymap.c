#include "quantum.h"
#include "socd_cleaner.h"
#include "sentence_case.h"
//#include "orbital_mouse.h"

socd_cleaner_t socd_opposing_pairs[] = {
    {{KC_W, KC_S}, SOCD_CLEANER_LAST},
    {{KC_A, KC_D}, SOCD_CLEANER_LAST},
};

bool sentence_case_persist = true;
bool socd_cleaner_persist = true;

// TODO: The hue seems to be different than what is expected?
const uint8_t HUE_RED   = 85;
const uint8_t HUE_GREEN = 0;
const uint8_t HUE_BLUE  = 170;

enum layers {
    BASE,
    LEFT_1,
    LEFT_2,
    LEFT_3,
    RIGHT_1,
    RIGHT_2,
    RIGHT_3,
    GAMING,
    GAMING_AUXILLARY,
    KRITA,
    KRITA_AUXILLARY,
    BLANK
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case QK_MACRO_0:
                SEND_STRING(" => ");
                break;
            case QK_MACRO_1:
                SEND_STRING("/>");
                break;
            case QK_MACRO_2: // Next sentence macro.
                SEND_STRING(". ");
                add_oneshot_mods(MOD_BIT(KC_LSFT)); // Set one-shot mod for shift.
                break;
            case QK_MACRO_3:
                sentence_case_toggle();
                sentence_case_persist = is_sentence_case_on();
                break;
            case QK_MACRO_4:
                socd_cleaner_enabled = !socd_cleaner_enabled;
                rgblight_sethsv_noeeprom(socd_cleaner_enabled ? HUE_RED : HUE_BLUE, 255, 1);
                socd_cleaner_persist = socd_cleaner_enabled;
                break;
        }
    }
    return true;
}

// This is to keep state between callbacks, when it is 0 the
// initial RGB flash is finished
uint8_t _hue_countdown = 50;

// Do a little 2.5 seconds display of the different colors
// Use the deferred executor so the LED flash dance does not
// stop us from using the keyboard.
// https://docs.qmk.fm/#/custom_quantum_functions?id=deferred-executor-registration
uint32_t flash_led(uint32_t next_trigger_time, void *cb_arg) {
    rgblight_sethsv_noeeprom(_hue_countdown * 5, 230, 70);
    _hue_countdown--;
    if (_hue_countdown == 0) {
        rgblight_sethsv_noeeprom(0, 255, 0);
        return 0;
    } else {
        return 50;
    }
}

void keyboard_post_init_user(void) {
    // debug_enable=true;
    // debug_matrix=true;
    // debug_keyboard=true;
    // debug_mouse=true;

    rgblight_sethsv(0,0,0);
    sentence_case_on();
    // Flash a little on start
    defer_exec(50, flash_led, NULL);
}

uint8_t get_hue(enum layers layer) {
    switch (layer) {
        case KRITA_AUXILLARY:
            return HUE_RED;
        case KRITA:
        case BLANK:
        case GAMING_AUXILLARY:
            return HUE_GREEN;
        case GAMING:
            return socd_cleaner_enabled ? HUE_RED : HUE_BLUE;
        default:
            return 0;
    }
}

uint8_t get_val(enum layers layer) {
    switch (layer) {
        case BLANK:
        case KRITA:
        case KRITA_AUXILLARY:
        case GAMING:
        case GAMING_AUXILLARY:
            return 1;
        default:
            return 0;
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    if (IS_LAYER_ON_STATE(state, GAMING)) {
        socd_cleaner_enabled = socd_cleaner_persist;
        sentence_case_off();
    } else {
        sentence_case_persist ? sentence_case_on() : sentence_case_off();
        socd_cleaner_enabled = false;
    }

    uint8_t sat = rgblight_get_sat();
    uint8_t val = get_val(get_highest_layer(state));
    uint8_t hue = get_hue(get_highest_layer(state));
    rgblight_sethsv_noeeprom(hue, sat, val);
    return state;
}
