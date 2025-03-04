#include QMK_KEYBOARD_H
#include <stdbool.h>
#include <stdint.h>

#define LT46 LT(4, KC_OPER)
#define LT55 LT(5, KC_OUT)
#define CDL KC_EXEC
#define CDR KC_HELP
#define MRKR KC_MENU

enum layer_names {
    _BASE,
    _GAME,
    _COLOR,
    _CLMK,
    _MODS,
    _XTRAS,
    _3ROW,
};

#ifdef OLED_ENABLE

// Rotate OLED
// oled_rotation_t oled_init_user(oled_rotation_t rotation) {
//    return OLED_ROTATION_270;
// }

// Gimmick border

void oled_draw_border(void) {
    for (uint8_t x = 0; x < 128; x++) {  // Top & Bottom Borders
        oled_write_pixel(x, 0, true);
        oled_write_pixel(x, 31, true);
    }
    for (uint8_t y = 0; y < 32; y++) {   // Left & Right Borders
        oled_write_pixel(0, y, true);
        oled_write_pixel(127, y, true);
    }
}

// Display adjustments

static uint32_t oled_last_input = 0; // Track keypress

// Function for centered text
void oled_centered_text(const char *text, uint8_t row) {
    uint8_t screen_width = 128; 
    uint8_t char_width = 6;     
    uint8_t text_length = strlen(text);
    uint8_t x_start = (screen_width - (text_length * char_width)) / 2;
    uint8_t cursor_x = x_start / char_width; 
    oled_set_cursor(cursor_x, row);
    oled_write(text, false);
}

// Function to get caps/num/lock status
const char *get_lock_status(void) {
    static char status[12] = "";  // Buffer to hold lock status
    status[0] = '\0';  // Clear previous content

    led_t led_state = host_keyboard_led_state();

    if (led_state.caps_lock) {
        strcat(status, "CAPS\n");
    }
//    if (led_state.num_lock) {
//        strcat(status, "NUM\n");
//    }
    if (led_state.scroll_lock) {
        strcat(status, "SCR\n");
    }

    if (status[0] != '\0') {  // Remove trailing space if there's a status
        status[strlen(status) - 1] = '\0';
    }

    return status;
}

void oled_show_layer_and_lock(const char *layer_name, uint8_t row) {
    char display_text[20];  // Buffer to hold the final text
    strcpy(display_text, layer_name);  // Start with the layer name

    const char *lock_status = get_lock_status();
    if (strlen(lock_status) > 0) {  // If there's a lock status, append it
        strcat(display_text, " || ");
        strcat(display_text, lock_status);
    }

    oled_centered_text(display_text, row);
}

// Keypress changes

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        oled_last_input = timer_read32();  // Reset timeout
    }

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
        case KC_EXEC:
            if (record->event.pressed) {
                register_code(KC_LCTL);
                register_code(KC_LGUI);
                register_code(KC_LEFT);
                unregister_code(KC_LCTL);
                unregister_code(KC_LGUI);
                unregister_code(KC_LEFT);
                return false;
            }
            break;
        case KC_HELP:
            if (record->event.pressed) {
                register_code(KC_LCTL);
                register_code(KC_LGUI);
                register_code(KC_RIGHT);
                unregister_code(KC_LCTL);
                unregister_code(KC_LGUI);
                unregister_code(KC_RIGHT);
                return false;
            }
            break;
        case KC_MENU:
            if (record->event.pressed) {
                register_code(KC_BSLS);
                unregister_code(KC_BSLS);
                register_code(KC_M);
                unregister_code(KC_M);
                return false;
            }
            break;                   
    }

    return true;
}

// Active Layers + Caps 
bool oled_task_user(void) {
//    oled_invert(true);
    oled_clear();
    
    if (timer_elapsed32(oled_last_input) > OLED_TIMEOUT) {
        return false;
    }

    switch (get_highest_layer(layer_state)) {
        case _BASE:
            oled_show_layer_and_lock("B A S E", 2);
            break;
        case _GAME:
            oled_show_layer_and_lock("G A M E", 2);
            break;
        case _COLOR:
            oled_show_layer_and_lock("C O L O R", 2);
            break;
        case _CLMK:
            oled_show_layer_and_lock("C L M K", 2);
            break;
        case _MODS:
            oled_show_layer_and_lock("M O D S", 2);
            break;
        case _XTRAS:
            oled_show_layer_and_lock("X T R A S", 2);
            break;
        default:
            oled_show_layer_and_lock("Undefined", 2);
    }
  
    return false;
}

#endif


 const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
        [_BASE] = LAYOUT(
                         KC_ESC,           KC_1,               KC_2,          KC_3,          KC_4,          KC_5,                                                                         KC_6,          KC_7,          KC_8,          KC_9,              KC_0,               KC_PSCR, 
                         KC_TAB,           KC_Q,               KC_W,          KC_E,          KC_R,          KC_T,                                                                         KC_Y,          KC_U,          KC_I,          KC_O,              KC_P,               KC_DQUO, 
                         KC_LSFT,          KC_A,               KC_S,          KC_D,          KC_F,          KC_G,                                                                         KC_H,          KC_J,          KC_K,          KC_L,              RALT(KC_COMM),      KC_RBRC, 
                         KC_LCTL,          KC_Z,               KC_X,          KC_C,          KC_V,          KC_B,          KC_QUOT,                                        KC_TILD,       KC_N,          KC_M,          KC_COMM,       KC_DOT,            KC_MINS,            KC_LBRC, 
                                                                              KC_LALT,       MO(_XTRAS),    MO(_MODS),     KC_SPC,                                         KC_BSPC,       KC_ENT,        KC_CAPS,       RGUI(KC_D)),
/*
*
*
*/
        [_GAME] = LAYOUT(
                         KC_ESC,           KC_BSLS,            KC_1,          KC_2,          KC_3,          KC_4,                                                                         KC_5,          KC_6,          KC_7,          KC_8,              KC_9,               KC_PSCR, 
                         KC_L,             KC_TAB,             KC_Q,          KC_W,          KC_E,          KC_R,                                                                         KC_Y,          KC_U,          KC_I,          KC_O,              KC_P,               KC_NO, 
                         KC_M,             KC_LSFT,            KC_A,          KC_S,          KC_D,          KC_F,                                                                         KC_H,          KC_NO,         KC_K,          KC_NO,             KC_NO,              KC_TILD, 
                         KC_J,             KC_LCTL,            KC_Z,          KC_X,          KC_C,          KC_V,          KC_B,                                           KC_T,          KC_N,          KC_NO,         KC_F5,         KC_F6,             KC_F7,              KC_F8, 
                                                                              TO(_BASE),     KC_G,          KC_LALT,       KC_SPC,                                         KC_BSPC,       KC_ENT,        KC_RGUI,       KC_F12),
/*
*
*
*/
        [_COLOR] = LAYOUT(
                         KC_ESC,          KC_NO,              RCS(KC_I),     LCTL(KC_I),    KC_F12,        LCTL(KC_F),                                                                    KC_NO,         LCTL(KC_X),    LCTL(KC_C),      LCTL(KC_V),        SGUI(KC_D),         KC_PSCR, 
                         LCTL(KC_Q),      KC_TAB,             LALT(KC_BSLS), KC_W,          KC_BSLS,       MRKR,                                                                          KC_NO,         KC_NO,         KC_HOME,         KC_NO,             KC_NO,              KC_NO, 
                         LCTL(KC_S),      KC_LSFT,            KC_A,          KC_S,          KC_D,          KC_F,                                                                          KC_NO,         KC_NO,         KC_END,          KC_NO,             KC_NO,              KC_NO, 
                         LSFT(KC_Z),      KC_LCTL,            KC_Z,          KC_X,          KC_C,          LCA(KC_F),      LALT(KC_DOWN),                                  LCA(KC_C),     KC_NO,         KC_NO,         KC_NO,           KC_NO,             KC_NO,              KC_NO, 
                                                                             TO(_BASE),     KC_R,          MO(_MODS),      KC_SPC,                                         KC_BSPC,       KC_ENT,        KC_NO,         KC_NO),
/*
*
*
*/
        [_CLMK] = LAYOUT(
                         KC_ESC,          KC_1,               KC_2,          KC_3,          KC_4,          KC_5,                                                                          KC_6,          KC_7,          KC_8,          KC_9,              KC_0,               KC_PSCR, 
                         KC_TAB,          KC_Q,               KC_W,          KC_F,          KC_P,          KC_B,                                                                          KC_J,          KC_L,          KC_U,          KC_Y,              KC_TILD,            LSFT(KC_QUOT), 
                         KC_LSFT,         KC_A,               KC_R,          KC_S,          KC_T,          KC_G,                                                                          KC_M,          KC_N,          KC_E,          KC_I,              KC_O,               KC_RBRC, 
                         KC_LCTL,         KC_Z,               KC_X,          KC_C,          KC_D,          KC_V,           KC_QUOT,                                        RALT(KC_COMM), KC_K,          KC_H,          KC_COMM,       KC_DOT,            KC_MINS,            KC_LBRC, 
                                                                             KC_LALT,       MO(_XTRAS),    MO(_MODS),      KC_SPC,                                         KC_BSPC,       KC_ENT,        KC_CAPS,       RGUI(KC_D)),
/*
*
*
*/
        [_MODS] = LAYOUT(
                         KC_PIPE,         KC_EXLM,            KC_AT,         KC_HASH,       KC_DLR,        KC_PERC,                                                                       KC_AMPR,       KC_SLSH,       KC_LPRN,       KC_RPRN,           KC_EQL,             LSFT(KC_PSCR), 
                         LALT(KC_F4),     LCA(KC_DOWN),       LCA(KC_M),     LCA(KC_U),     RCS(KC_T),     LCTL(KC_T),                                                                    LGUI(KC_TAB),  LCTL(KC_LEFT), KC_UP,         LCTL(KC_RGHT),     LCTL(KC_I),         KC_PLUS, 
                         KC_LSFT,         LCTL(KC_A),         LCTL(KC_X),    LCTL(KC_C),    LCTL(KC_V),    LGUI(KC_G),                                                                    LCTL(KC_F),    KC_LEFT,       KC_DOWN,       KC_RGHT,           LCTL(KC_B),         KC_ASTR, 
                         KC_LCTL,         LCTL(KC_Z),         RCS(KC_Z),     LCTL(KC_S),    RCS(KC_N),     KC_DEL,         KC_GRV,                                         KC_CIRC,       KC_QUES,       RALT(KC_5),    KC_SCLN,       KC_COLN,           KC_UNDS,            LGUI(KC_L),
                                                                             LGUI(KC_SPC),  KC_LGUI,       KC_NO,          SGUI(KC_S),                                     LALT(KC_SPC),  LCTL(KC_LSFT), KC_HOME,       KC_END),
/*
*
*
*/
        [_XTRAS] = LAYOUT(
                         KC_NUBS,         TO(_GAME),          TO(_COLOR),    KC_NO,         KC_NO,         TO(_CLMK),                                                                     KC_NO,         KC_NO,         KC_NO,         KC_NO,             KC_NO,              KC_RCBR, 
                         LALT(KC_1),      KC_BTN2,            KC_BTN4,       LCA(KC_W),     KC_BTN1,       LCAG(KC_3),                                                                    KC_F11,        KC_F12,        KC_NO,         KC_NO,             KC_NO,              KC_LCBR, 
                         CDL,             KC_NO,              RCS(KC_TAB),   KC_F5,         LCTL(KC_TAB),  LCAG(KC_2),                                                                    KC_F6,         KC_F7,         KC_F8,         KC_F9,             KC_F10,             KC_GT, 
                         CDR,             KC_MPRV,            KC_MPLY,       KC_MNXT,       RCS(KC_V),     LCAG(KC_1),     KC_MSEL,                                          KC_PWR,      KC_F1,         KC_F2,         KC_F3,         KC_F4,             KC_F5,              KC_LT,
                                                                             LGUI(KC_R),    TO(_BASE),     KC_NO,          KC_SPC,                                           KC_BSPC,     LCAG(KC_4),    LGUI(KC_LEFT), LGUI(KC_RGHT)),
/*
*
*
*/
//        [_3ROW] = LAYOUT(KC_F1,           KC_F2,              KC_F3,         KC_F4,         KC_F5,         KC_F6,                                                                          KC_F7,         KC_F8,         KC_F9,         KC_F10,            KC_F11,             KC_F12, 
//                         KC_NO,           KC_NO,              KC_NO,         KC_NO,         KC_NO,         KC_NO,                                                                          KC_NO,         KC_NO,         KC_NO,         KC_NO,             KC_NO,              KC_NO, 
//                         KC_NO,           KC_NO,              KC_NO,         KC_NO,         KC_NO,         KC_NO,                                                                          KC_NO,         KC_NO,         KC_NO,         KC_NO,             KC_NO,              KC_NO, 
//                         KC_NO,           KC_NO,              KC_NO,         KC_NO,         KC_NO,         KC_NO,          KC_NO,                                          KC_NO,          KC_NO,         KC_NO,         KC_NO,         KC_NO,             KC_NO,              KC_NO, 
//                                                              KC_NO,         TO(_BASE),     KC_NO,         KC_NO,                                                                          KC_NO,         KC_NO,         KC_NO,         KC_NO),
/*
*
*
*/
//        [_3ROW] = LAYOUT(KC_F1,           KC_F2,              KC_F3,         KC_F4,         KC_F5,         KC_F6,                                                                          KC_F7,         KC_F8,         KC_F9,         KC_F10,            KC_F11,             KC_F12, 
//                         KC_NO,           KC_NO,              KC_NO,         KC_NO,         KC_NO,         KC_NO,                                                                          KC_NO,         KC_NO,         KC_NO,         KC_NO,             KC_NO,              KC_NO, 
//                         KC_NO,           KC_NO,              KC_NO,         KC_NO,         KC_NO,         KC_NO,                                                                          KC_NO,         KC_NO,         KC_NO,         KC_NO,             KC_NO,              KC_NO, 
//                         KC_NO,           KC_NO,              KC_NO,         KC_NO,         KC_NO,         KC_NO,          KC_NO,                                          KC_NO,          KC_NO,         KC_NO,         KC_NO,         KC_NO,             KC_NO,              KC_NO, 
//                                                              KC_NO,         TO(_BASE),     KC_NO,         KC_NO,                                                                          KC_NO,         KC_NO,         KC_NO,         KC_NO),
//    
};
