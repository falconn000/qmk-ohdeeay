#include QMK_KEYBOARD_H
#include <stdbool.h>
#include <stdint.h>

#define LT46 LT(4, KC_OPER)
#define LT55 LT(5, KC_OUT)

enum layer_names {
    _BASE,
    _GAME,
    _COLOR,
    _CLMK,
    _MODS,
    _XTRAS,
    _3ROW,
};

 const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
        [_BASE] = LAYOUT(
                         KC_ESC,           KC_1,               KC_2,          KC_3,          KC_4,          KC_5,                                                                         KC_6,          KC_7,          KC_8,          KC_9,              KC_0,               KC_PSCR, 
                         KC_TAB,           KC_Q,               KC_W,          KC_E,          KC_R,          KC_T,                                                                         KC_Y,          KC_U,          KC_I,          KC_O,              KC_P,               KC_DQUO, 
                         KC_LSFT,          KC_A,               KC_S,          KC_D,          KC_F,          KC_G,                                                                         KC_H,          KC_J,          KC_K,          KC_L,              RALT(KC_COMM),      KC_RBRC, 
                         KC_LCTL,          KC_Z,               KC_X,          KC_C,          KC_V,          KC_B,          KC_QUOT,                                        KC_TILD,       KC_N,          KC_M,          KC_COMM,       KC_DOT,            KC_MINS,            KC_LBRC, 
                                                                                             KC_LALT,       LT55,          LT46,      KC_SPC,           KC_BSPC,           KC_ENT,        KC_CAPS,       RGUI(KC_D)),
/*
*
*
*/
        [_GAME] = LAYOUT(
                         KC_ESC,           KC_BSLS,            KC_1,          KC_2,          KC_3,          KC_4,                                                                         KC_5,          KC_6,          KC_7,          KC_8,              KC_9,               KC_PSCR, 
                         KC_L,             KC_TAB,             KC_Q,          KC_W,          KC_E,          KC_R,                                                                         KC_Y,          KC_U,          KC_I,          KC_O,              KC_P,               KC_NO, 
                         KC_M,             KC_LSFT,            KC_A,          KC_S,          KC_D,          KC_F,                                                                         KC_H,          KC_NO,         KC_K,          KC_NO,             KC_NO,              KC_TILD, 
                         KC_J,             KC_LCTL,            KC_Z,          KC_X,          KC_C,          KC_V,          KC_B,                                           KC_T,          KC_N,          KC_NO,         KC_F5,         KC_F6,             KC_F7,              KC_F8, 
                                                                                             TO(_BASE),     KC_G,          KC_LALT,   KC_SPC,           KC_BSPC,           KC_ENT,        KC_RGUI,       KC_F12),
/*
*
*
*/
        [_COLOR] = LAYOUT(
                         KC_ESC,          KC_NO,              RCS(KC_I),     LCTL(KC_I),    LCA(KC_F),     LCTL(KC_F),                                                                    KC_NO,         LCTL(KC_X),    LCTL(KC_C),    LCTL(KC_V),        SGUI(KC_D),         KC_PSCR, 
                         KC_TAB,          LCTL(KC_Q),         KC_BSLS,       KC_W,          LALT(KC_BSLS), KC_R,                                                                          KC_NO,         KC_NO,         KC_UP,         KC_NO,             KC_NO,              KC_NO, 
                         KC_LSFT,         LCTL(KC_S),         KC_A,          KC_S,          KC_D,          KC_F,                                                                          KC_NO,         KC_LEFT,       KC_DOWN,       KC_RGHT,           KC_NO,              KC_NO, 
                         KC_LCTL,         LSFT(KC_Z),         KC_Z,          KC_TRNS,       KC_C,          KC_V,           LCA(KC_C),                                      KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,             KC_NO,              KC_NO, 
                                                                                            TO(0),         LALT(KC_DOWN),  LT46,      KC_SPC,           KC_BSPC,           KC_ENT,        KC_NO,         KC_NO),
/*
*
*
*/
        [_CLMK] = LAYOUT(
                         KC_ESC,          KC_1,               KC_2,          KC_3,          KC_4,          KC_5,                                                                          KC_6,          KC_7,          KC_8,          KC_9,              KC_0,               KC_PSCR, 
                         KC_TAB,          KC_Q,               KC_W,          KC_F,          KC_P,          KC_B,                                                                          KC_J,          KC_L,          KC_U,          KC_Y,              KC_TILD,            LSFT(KC_QUOT), 
                         KC_LSFT,         KC_A,               KC_R,          KC_S,          KC_T,          KC_G,                                                                          KC_M,          KC_N,          KC_E,          KC_I,              KC_O,               KC_RBRC, 
                         KC_LCTL,         KC_Z,               KC_X,          KC_C,          KC_TRNS,       KC_V,           KC_QUOT,                                        RALT(KC_COMM), KC_K,          KC_H,          KC_COMM,       KC_DOT,            KC_MINS,            KC_LBRC, 
                                                                                            KC_LALT,       LT55,           LT46,      KC_SPC,           KC_BSPC,           KC_ENT,        KC_CAPS,       RGUI(KC_D)),
/*
*
*
*/
        [_MODS] = LAYOUT(
                         KC_PIPE,         KC_EXLM,            KC_AT,         KC_HASH,       KC_DLR,        KC_PERC,                                                                       KC_AMPR,       KC_SLSH,       KC_LPRN,       KC_RPRN,           KC_EQL,             LSFT(KC_PSCR), 
                         LALT(KC_F4),     LCA(KC_DOWN),       LCA(KC_M),     LCA(KC_U),     RCS(KC_T),     LCTL(KC_T),                                                                    LGUI(KC_TAB),  LCTL(KC_LEFT), KC_UP,         LCTL(KC_RGHT),     LCTL(KC_I),         KC_PLUS, 
                         KC_LSFT,         LCTL(KC_A),         LCTL(KC_X),    LCTL(KC_C),    LCTL(KC_V),    LGUI(KC_G),                                                                    LCTL(KC_F),    KC_LEFT,       KC_DOWN,       KC_RGHT,           LCTL(KC_B),         KC_ASTR, 
                         KC_LCTL,         LCTL(KC_Z),         RCS(KC_Z),     LCTL(KC_S),    RCS(KC_N),     KC_DEL,         KC_GRV,                                         KC_CIRC,       KC_QUES,       RALT(KC_5),    KC_SCLN,       KC_COLN,           KC_UNDS,            TO(_BASE),
                                                                                            LGUI(KC_SPC),  KC_LGUI,        KC_NO,     SGUI(KC_S),       LALT(KC_SPC),      LCTL(KC_LSFT), LCTL(KC_S),    LGUI(KC_L)),
/*
*
*
*/
        [_XTRAS] = LAYOUT(
                         KC_NO,           TO(_GAME),          TO(_COLOR),    TO(_CLMK),     KC_NO,         KC_NO,                                                                         KC_PSLS,       KC_P7,         KC_P8,         KC_P9,             KC_PMNS,            KC_NO, 
                         KC_NO,           KC_NO,              RCS(KC_TAB),   KC_F5,         LCTL(KC_TAB),  KC_NO,                                                                         KC_PAST,       KC_P4,         KC_P5,         KC_P6,             KC_PPLS,            KC_NO, 
                         KC_NO,           KC_NO,              KC_BTN4,       LCA(KC_W),     KC_BTN1,       KC_NO,                                                                         KC_HOME,       KC_P1,         KC_P2,         KC_P3,             KC_PCMM,            KC_GT, 
                         KC_NO,           KC_NO,              KC_NO,         KC_BTN2,       KC_NO,         KC_NO,          KC_NO,                                          KC_NO,         KC_END,        KC_P0,         KC_PDOT,       KC_DEL,            KC_PEQL,            KC_LT, 
                                                                                            KC_NO,         TO(_BASE),      KC_NO,     KC_SPC,           KC_BSPC,           KC_PENT,       KC_NO,         KC_NO),
/*
*
*
*/
        [_3ROW] = LAYOUT(KC_NO,           KC_NO,              KC_NO,         KC_NO,         KC_NO,         KC_NO,                                                                         KC_NO,         KC_NO,         KC_NO,         KC_NO,             KC_NO,              KC_NO, 
                         KC_F1,           KC_F2,              KC_F3,         KC_F4,         KC_F5,         KC_F6,                                                                         KC_F7,         KC_F8,         KC_F9,         KC_F10,            KC_F11,             KC_F12, 
                         KC_NO,           KC_1,               KC_2,          KC_3,          KC_4,          KC_5,                                                                          KC_6,          KC_7,          KC_8,          KC_9,              KC_0,               KC_NO, 
                         KC_NO,           KC_NO,              LCAG(KC_1),    LCAG(KC_2),    LCAG(KC_3),    KC_NO,          KC_NO,                                          KC_NO,         KC_NO,         KC_NO,         KC_HOME,       KC_END,            KC_NO,              KC_NO, 
                                                                                            KC_NO,         KC_NO,  TO(0),  KC_NO,     KC_NO,            KC_NO,             SGUI(KC_LEFT),         SGUI(KC_RGHT))
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(4, KC_OPER):
            if (record->tap.count && record->event.pressed) {
                layer_move(6); // Send TO6 on tap
                return false;  
            }
            break;
        case LT(5, KC_OUT):
            if (record->tap.count && record->event.pressed) {
                layer_move(5); // Send TO5 on tap
                return false;  
            }
            break;
    }
    return true;
}