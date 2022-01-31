#include QMK_KEYBOARD_H

#define CC_CUT  LCTL(KC_X)
#define CC_COPY LCTL(KC_C)
#define CC_PSTE LCTL(KC_V)
#define CC_AT   LSFT(KC_QUOT)
#define CC_TILD LSFT(KC_NUHS)
#define CC_PIPE LSFT(KC_NUBS)

enum layers {
    _alpha,
    _alpha_shifted,
    _num_sym,
    _nav,
    _games,
    _games_shifted
};

enum my_keycodes { 
    LCTL_T_L0 = SAFE_RANGE,
    LGUI_T_TAB,
    RALT_T_L1,
    RALT_T_L2,
    MC_LSFT_0  // space, or "shift" alpha layer when held
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_alpha] = LAYOUT(
        KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                           KC_J,    KC_L,    KC_U,    KC_Y,    KC_BSPC,
        KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                           KC_M,    KC_N,    KC_E,    KC_I,    KC_O,
        KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,                           KC_K,    KC_H,    KC_DOT,  KC_MINS, KC_ENT,
                                     MC_LSFT_0,      LCTL_T_L0,    RALT_T_L1,    LGUI_T_TAB
    ),

    [_alpha_shifted] = LAYOUT(
        LSFT(KC_Q), LSFT(KC_W), LSFT(KC_F), LSFT(KC_P), LSFT(KC_B),            LSFT(KC_J), LSFT(KC_L), LSFT(KC_U), LSFT(KC_Y), KC_DEL,
        LSFT(KC_A), LSFT(KC_R), LSFT(KC_S), LSFT(KC_T), LSFT(KC_G),            LSFT(KC_M), LSFT(KC_N), LSFT(KC_E), LSFT(KC_I), LSFT(KC_O),
        LSFT(KC_Z), LSFT(KC_X), LSFT(KC_C), LSFT(KC_D), LSFT(KC_V),            LSFT(KC_K), LSFT(KC_H), KC_COMM,    CC_PIPE,    LSFT(KC_ENT),
                                                 MC_LSFT_0,   LCTL_T_L0,   RALT_T_L1,    LGUI_T_TAB
    ),

    [_num_sym] = LAYOUT(
        KC_GRV,  KC_LBRC, KC_RBRC, KC_COMM, KC_DOT,                         KC_EQL,  KC_7,    KC_8,    KC_9,    KC_BSPC,
        KC_TAB,  KC_COLN, CC_AT,   CC_TILD, CC_PIPE,                        KC_MINS, KC_4,    KC_5,    KC_6,    KC_DOT,
        KC_NUBS, KC_SCLN, KC_QUOT, KC_NUHS, KC_SLSH,                        KC_0,    KC_1,    KC_2,    KC_3,    KC_ENT,
                                     LSFT_T(KC_SPC), LCTL_T_L0,    RALT_T_L2,    LGUI_T_TAB
    ),

    [_nav] = LAYOUT(
        KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_ESC,                         KC_VOLU, KC_HOME, KC_PGDN, KC_PGUP, KC_END,
        KC_F5,   KC_F6,   KC_F7,   KC_F8,   TO(_games),                     KC_VOLD, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_INS,                         KC_MUTE, CC_CUT,  CC_COPY, CC_PSTE, KC_ENT,
                                     LSFT_T(KC_SPC), LCTL_T_L0,    RALT_T_L2,    LGUI_T_TAB
    ),

    [_games] = LAYOUT(
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                           KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_LSFT, KC_A,    KC_W,    KC_D,    KC_R,                           KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_LCTL, KC_Q,    KC_S,    KC_E,    KC_F,                           KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                                     MO(_games_shifted), KC_SPC,   KC_ESC,       LCTL_T_L0
    ),

    [_games_shifted] = LAYOUT(
        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,                           KC_NO,   KC_NO,   KC_NO,   KC_NO,   LCTL_T_L0,
        KC_LSFT, KC_A,    KC_W,    KC_D,    KC_T,                           KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_LCTL, KC_Z,    KC_S,    KC_C,    KC_G,                           KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                                     MO(_games_shifted), KC_SPC,   KC_ESC,       KC_NO
    )
};

uint16_t timer_LCTL_T_L0;
uint16_t timer_LGUI_T_TAB;
uint16_t timer_RALT_T_L1;
uint16_t timer_RALT_T_L2;
uint16_t timer_MC_LSFT_0;

bool LCTL_T_L0_pressed;
bool LGUI_T_TAB_pressed;
bool RALT_T_L1_pressed;
bool RALT_T_L2_pressed;

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
            
        case LGUI_T_TAB:
            if (record->event.pressed) {
                timer_LGUI_T_TAB = timer_read();
                LGUI_T_TAB_pressed = true;
            } else {
                LGUI_T_TAB_pressed = false;
                unregister_code(KC_LGUI);
                if (timer_elapsed(timer_LGUI_T_TAB) < TAPPING_TERM) {
                    register_code(KC_TAB);
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
                    layer_move(_num_sym);
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
                    layer_move(_nav);
                }
            }
            return false;

        case MC_LSFT_0:
            if (record->event.pressed) {
                layer_move(_alpha_shifted);
                timer_MC_LSFT_0 = timer_read();
            } else {
                layer_clear();
                if (timer_elapsed(timer_MC_LSFT_0) < TAPPING_TERM) {
                    tap_code(KC_SPC);
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
    
    if (LGUI_T_TAB_pressed && timer_elapsed(timer_LGUI_T_TAB) >= TAPPING_TERM) {
        register_code(KC_LGUI);
        LGUI_T_TAB_pressed = false;
    }
    
    if (RALT_T_L1_pressed && timer_elapsed(timer_RALT_T_L1) >= TAPPING_TERM) {
        register_code(KC_LALT);
        RALT_T_L1_pressed = false;
    }
    
    if (RALT_T_L2_pressed && timer_elapsed(timer_RALT_T_L2) >= TAPPING_TERM) {
        register_code(KC_LALT);
        RALT_T_L2_pressed = false;
    }
}
