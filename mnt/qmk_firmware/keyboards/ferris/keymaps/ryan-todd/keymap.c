#include QMK_KEYBOARD_H

#define CC_CUT  LCTL(KC_X)
#define CC_COPY LCTL(KC_C)
#define CC_PSTE LCTL(KC_V)
#define CC_AT   LSFT(KC_QUOT)
#define CC_TILD LSFT(KC_NUHS)
#define CC_PIPE LSFT(KC_NUBS)

enum layers {
    _alpha,
    _num_sym,
    _nav,
    _games
};

enum my_keycodes { 
    LCTL_T_L0 = SAFE_RANGE,
    RALT_T_L1,
    RALT_T_L2,
    RALT_T_L3
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_alpha] = LAYOUT(
        KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                           KC_J,    KC_L,    KC_U,    KC_Y,    KC_SLSH,
        KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                           KC_M,    KC_N,    KC_E,    KC_I,    KC_O,
        KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,                           KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_ENT,
                                     LSFT_T(KC_SPC), LCTL_T_L0,    RALT_T_L1,    KC_BSPC
    ),

	[_num_sym] = LAYOUT(
        KC_GRV,  KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR,                        KC_DEL,  KC_7,    KC_8,    KC_9,    KC_EQL,
        KC_TAB,  KC_COLN, CC_AT,   CC_TILD, CC_PIPE,                        KC_INS,  KC_4,    KC_5,    KC_6,    KC_MINS,
        KC_NUBS, KC_SCLN, KC_QUOT, KC_NUHS, KC_NO,                          KC_0,    KC_1,    KC_2,    KC_3,    KC_ENT,
                                     LSFT_T(KC_SPC), LCTL_T_L0,    RALT_T_L2,    KC_BSPC
    ),

	[_nav] = LAYOUT(
        KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_ESC,                         KC_VOLU, KC_HOME, KC_PGDN, KC_PGUP, KC_END,
        KC_F5,   KC_F6,   KC_F7,   KC_F8,   TO(3),                          KC_VOLD, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_LGUI,                        KC_MUTE, CC_CUT,  CC_COPY, CC_PSTE, KC_ENT,
                                     LSFT_T(KC_SPC), LCTL_T_L0,    RALT_T_L2,    KC_BSPC
    ),

	[_games] = LAYOUT(
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                           KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_LSFT, KC_A,    KC_W,    KC_D,    KC_E,                           KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_LCTL, KC_Q,    KC_S,    KC_R,    KC_ESC,                         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                                     KC_TAB,         KC_SPC,       KC_NO,        LCTL_T_L0
    )
};

uint16_t timer_LCTL_T_L0;
uint16_t timer_RALT_T_L1;
uint16_t timer_RALT_T_L2;
uint16_t timer_RALT_T_L3;

bool LCTL_T_L0_pressed;
bool RALT_T_L1_pressed;
bool RALT_T_L2_pressed;
bool RALT_T_L3_pressed;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LCTL_T_L0:
            if (record->event.pressed) {
                timer_LCTL_T_L0 = timer_read();
                LCTL_T_L0_pressed = true;
            } else {
                LCTL_T_L0_pressed = false;
                unregister_code(KC_LCTL);
                if (timer_elapsed(timer_LCTL_T_L0) < TAPPING_TERM) {
                    layer_clear();
                }
            }
            return false;

        case RALT_T_L1:
            if (record->event.pressed) {
                timer_RALT_T_L1 = timer_read();
                RALT_T_L1_pressed = true;
            } else {
                RALT_T_L1_pressed = false;
                unregister_code(KC_LALT);
                if (timer_elapsed(timer_RALT_T_L1) < TAPPING_TERM) {
                    layer_move(1);
                }
            }
            return false;

        case RALT_T_L2:
            if (record->event.pressed) {
                timer_RALT_T_L2 = timer_read();
                RALT_T_L2_pressed = true;
            } else {
                RALT_T_L2_pressed = false;
                unregister_code(KC_LALT);
                if (timer_elapsed(timer_RALT_T_L2) < TAPPING_TERM) {
                    layer_move(2);
                }
            }
            return false;

        case RALT_T_L3:
            if (record->event.pressed) {
                timer_RALT_T_L3 = timer_read();
                RALT_T_L3_pressed = true;
            } else {
                RALT_T_L3_pressed = false;
                unregister_code(KC_LALT);
                if (timer_elapsed(timer_RALT_T_L3) < TAPPING_TERM) {
                    layer_move(3);
                }
            }
            return false;

        default:
            return true;
    }
}

void matrix_scan_user(void) {
    if (LCTL_T_L0_pressed && timer_elapsed(timer_LCTL_T_L0) >= TAPPING_TERM) {
        register_code(KC_LCTL);
        LCTL_T_L0_pressed = false;
    }
    
    if (RALT_T_L1_pressed && timer_elapsed(timer_RALT_T_L1) >= TAPPING_TERM) {
        register_code(KC_LALT);
        RALT_T_L1_pressed = false;
    }
    
    if (RALT_T_L2_pressed && timer_elapsed(timer_RALT_T_L2) >= TAPPING_TERM) {
        register_code(KC_LALT);
        RALT_T_L2_pressed = false;
    }
    
    if (RALT_T_L3_pressed && timer_elapsed(timer_RALT_T_L3) >= TAPPING_TERM) {
        register_code(KC_LALT);
        RALT_T_L3_pressed = false;
    }
}