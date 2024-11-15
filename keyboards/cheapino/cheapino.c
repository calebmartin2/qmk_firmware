#include "wait.h"
#include "quantum.h"
#include "features/socd_cleaner.h"


socd_cleaner_t socd_v = {{KC_W, KC_S}, SOCD_CLEANER_LAST};
socd_cleaner_t socd_h = {{KC_A, KC_D}, SOCD_CLEANER_LAST};


bool process_record_user(uint16_t keycode, keyrecord_t* record) {
  if (!process_socd_cleaner(keycode, record, &socd_v)) { return false; }
  if (!process_socd_cleaner(keycode, record, &socd_h)) { return false; }
  // Your macros...

    return true;
}
// This is to keep state between callbacks, when it is 0 the
// initial RGB flash is finished
uint8_t _hue_countdown = 50;

// These are to keep track of user selected color, so we
// can restore it after RGB flash
uint8_t _hue;
uint8_t _saturation;
uint8_t _value;

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

void keyboard_post_init_user(void) {
    //debug_enable=true;
    //debug_matrix=true;
    //debug_keyboard=true;
    //debug_mouse=true;

    // Store user selected rgb hsv:
    _hue = rgblight_get_hue();
    _saturation = rgblight_get_sat();
    _value = rgblight_get_val();

    // Flash a little on start
    defer_exec(50, flash_led, NULL);
}

// Make the builtin RGB led show different colors per layer:
// This seemed like a good idea but turned out pretty annoying,
// to me at least... Uncomment the lines below to enable

uint8_t get_hue(uint8_t layer) {
    switch (layer) {
        case 8:
            return 180;
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
            return 1;
        default:
            return 0;
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    socd_cleaner_enabled = IS_LAYER_ON_STATE(state, 7);
    uint8_t sat = rgblight_get_sat();
    uint8_t val = get_val(get_highest_layer(state));
    uint8_t hue = get_hue(get_highest_layer(state));
    rgblight_sethsv(hue, sat, val);
    return state;
}

