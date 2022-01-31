#include QMK_KEYBOARD_H
#define CC_PIPE LSFT(KC_NUBS)
#define CC_DQUO LSFT(KC_2)

enum layers {
    _alpha,
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
    MC_DOT,     // dot, or comma when shifted
    MC_MINS,    // dash, or pipe when shifted
    MC_COLN,    // colon, or ( when shifted
    MC_SCLN,    // semicolon, or ) when shifted
    MC_UHH,
    MC_EHH,
    MC_OAH
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_alpha] = LAYOUT(
        KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                           KC_J,    KC_L,    KC_U,    KC_Y,    KC_BSPC,
        KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                           KC_M,    KC_N,    KC_E,    KC_I,    KC_O,
        KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,                           KC_K,    KC_H,    MC_DOT,  MC_MINS, KC_ENT,
                                     LSFT_T(KC_SPC), LCTL_T_L0,    RALT_T_L1,    LGUI_T_TAB
    ),

    [_num_sym] = LAYOUT(
        KC_GRV,  KC_QUOT, CC_DQUO, MC_COLN, MC_SCLN,                        KC_EQL,  KC_7,    KC_8,    KC_9,    KC_BSPC,
        KC_NUBS, CC_PIPE, KC_SLSH, KC_LBRC, KC_RBRC,                        KC_MINS, KC_4,    KC_5,    KC_6,    KC_NUHS,
        MC_EHH,  MC_UHH,  MC_OAH,  KC_COMM, KC_DOT,                         KC_0,    KC_1,    KC_2,    KC_3,    KC_ENT,
                                     LSFT_T(KC_SPC), LCTL_T_L0,    RALT_T_L2,    LGUI_T_TAB
    ),

    [_nav] = LAYOUT(
        KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_ESC,                         KC_VOLU, KC_HOME, KC_PGDN, KC_PGUP, KC_END,
        KC_F5,   KC_F6,   KC_F7,   KC_F8,   TO(_games),                     KC_VOLD, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_INS,                         KC_MUTE, KC_TAB,  KC_NO,   KC_NO,   KC_ENT,
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

bool LCTL_T_L0_pressed;
bool LGUI_T_TAB_pressed;
bool RALT_T_L1_pressed;
bool RALT_T_L2_pressed;

bool delkey_registered;
bool MC_DOT_shifted;
bool MC_MINS_shifted;
bool MC_COLN_shifted;
bool MC_SCLN_shifted;

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
                    tap_code(KC_TAB);
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

        case KC_BSPC:
            if (record->event.pressed) {
                uint8_t mod_state = get_mods();
                if (mod_state & MOD_MASK_SHIFT) {
                    del_mods(MOD_MASK_SHIFT);
                    register_code(KC_DEL);
                    delkey_registered = true;
                    set_mods(mod_state);
                    return false;
                }
            } else {
                if (delkey_registered) {
                    unregister_code(KC_DEL);
                    delkey_registered = false;
                    return false;
                }
            }
            return true;
        
        case MC_DOT:
            if (record->event.pressed) {
                uint8_t mod_state = get_mods();
                if (mod_state & MOD_MASK_SHIFT) {
                    del_mods(MOD_MASK_SHIFT);
                    register_code(KC_COMM);
                    MC_DOT_shifted = true;
                    set_mods(mod_state);
                } else {
                    register_code(KC_DOT);
                }
            } else {
                if (MC_DOT_shifted) {
                    unregister_code(KC_COMM);
                    MC_DOT_shifted = false;
                } else {
                    unregister_code(KC_DOT);
                }
            }
            return false;
        
        case MC_MINS:
            if (record->event.pressed) {
                uint8_t mod_state = get_mods();
                if (mod_state & MOD_MASK_SHIFT) {
                    register_code(KC_NUBS);
                    MC_MINS_shifted = true;
                } else {
                    register_code(KC_MINS);
                }
            } else {
                if (MC_MINS_shifted) {
                    unregister_code(KC_NUBS);
                    MC_MINS_shifted = false;
                } else {
                    unregister_code(KC_MINS);
                }
            }
            return false;
        
        case MC_COLN:
            if (record->event.pressed) {
                uint8_t mod_state = get_mods();
                if (mod_state & MOD_MASK_SHIFT) {
                    register_code(KC_9);
                    MC_COLN_shifted = true;
                } else {
                    register_code(KC_LSFT);
                    register_code(KC_SCLN);
                }
            } else {
                if (MC_COLN_shifted) {
                    unregister_code(KC_9);
                    MC_COLN_shifted = false;
                } else {
                    unregister_code(KC_SCLN);
                    unregister_code(KC_LSFT);
                }
            }
            return false;

        case MC_SCLN:
            if (record->event.pressed) {
                uint8_t mod_state = get_mods();
                if (mod_state & MOD_MASK_SHIFT) {
                    register_code(KC_0);
                    MC_SCLN_shifted = true;
                } else {
                    register_code(KC_SCLN);
                }
            } else {
                if (MC_SCLN_shifted) {
                    unregister_code(KC_0);
                    MC_SCLN_shifted = false;
                } else {
                    unregister_code(KC_SCLN);
                }
            }
            return false;

        case MC_EHH:
            if (record->event.pressed) {
                uint8_t mod_state = get_mods();
                clear_mods();
                register_code(KC_LALT);
                if (mod_state & MOD_MASK_SHIFT) {
                    tap_code(KC_P1);
                    tap_code(KC_P4);
                    tap_code(KC_P2);
                } else {
                    tap_code(KC_P1);
                    tap_code(KC_P3);
                    tap_code(KC_P2);
                }
                unregister_code(KC_LALT);
                set_mods(mod_state);
            }
            return false;

        case MC_UHH:
            if (record->event.pressed) {
                uint8_t mod_state = get_mods();
                clear_mods();
                register_code(KC_LALT);
                if (mod_state & MOD_MASK_SHIFT) {
                    tap_code(KC_P1);
                    tap_code(KC_P5);
                    tap_code(KC_P3);
                } else {
                    tap_code(KC_P1);
                    tap_code(KC_P4);
                    tap_code(KC_P8);
                }
                unregister_code(KC_LALT);
                set_mods(mod_state);
            }
            return false;

        case MC_OAH:
            if (record->event.pressed) {
                uint8_t mod_state = get_mods();
                clear_mods();
                register_code(KC_LALT);
                if (mod_state & MOD_MASK_SHIFT) {
                    tap_code(KC_P1);
                    tap_code(KC_P4);
                    tap_code(KC_P3);
                } else {
                    tap_code(KC_P1);
                    tap_code(KC_P3);
                    tap_code(KC_P4);
                }
                unregister_code(KC_LALT);
                set_mods(mod_state);
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
