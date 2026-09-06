#include "config.h"
#include QMK_KEYBOARD_H

#define LAYOUT_kyps75( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, \
    k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, \
    k50, k51, k52, k53, k54, k55, k56, k57, k58, k59, \
    k60, k61, k62, k63, k64, k65, k66, k67, k68, k69, \
    k70, k71, k72, k73, k74, k75, k76, k77, k78, k79, \
    k80, k81, k82, k83, k84, k85, k86, k87, k88, k89  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09 }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19 }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29 }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39 }, \
    { k40, k41, k42, k43, k44, k45, k46, k47, k48, k49 }, \
    { k50, k51, k52, k53, k54, k55, k56, k57, k58, k59 }, \
    { k60, k61, k62, k63, k64, k65, k66, k67, k68, k69 }, \
    { k70, k71, k72, k73, k74, k75, k76, k77, k78, k79 }, \
    { k80, k81, k82, k83, k84, k85, k86, k87, k88, k89 }  \
}

const uint16_t PROGMEM keymaps[][9][10] = {
    [0] = LAYOUT_kyps75(
        KC_ESC,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,         // Row 0
        KC_F10,  KC_F11,  KC_F12,  KC_DELETE, KC_GRAVE, KC_1,   KC_2,   KC_3,   KC_4,   KC_KB_MUTE,    // Row 1
        KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BACKSPACE, KC_TAB, KC_Q, KC_KB_POWER, // Row 2
        KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,   KC_NO,         // Row 3
        KC_LEFT_BRACKET, KC_RIGHT_BRACKET, KC_BACKSLASH, KC_CAPS_LOCK, KC_A, KC_S, KC_D, KC_F, KC_G, KC_NO, // Row 4
        KC_H,    KC_J,    KC_K,    KC_L,    KC_SEMICOLON, KC_QUOTE, KC_ENTER, KC_LEFT_SHIFT, KC_Z, KC_NO, // Row 5
        KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMMA, KC_DOT, KC_SLASH, KC_NO,       // Row 6
        KC_RIGHT_SHIFT, KC_LEFT_CONTROL, KC_LEFT_GUI, KC_LEFT_ALT, KC_SPACE, KC_RIGHT_ALT, KC_RIGHT_GUI, KC_RIGHT_CTRL, KC_LEFT, KC_NO, // Row 7
        KC_DOWN, KC_RIGHT, KC_UP,   KC_PRINT_SCREEN, KC_SPACE, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO       // Row 8
    )
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_KB_VOLUME_UP);
        } else {
            tap_code(KC_KB_VOLUME_DOWN);
        }
    } else if (index == 1) {
        if (clockwise) {
            tap_code(KC_BRIGHTNESS_UP);
        } else {
            tap_code(KC_BRIGHTNESS_DOWN);
        }
    }
    return false;
}

#ifdef OLED_ENABLE
static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };
    oled_set_cursor(0, 1);
    oled_write_P(qmk_logo, false);
}

bool oled_task_user(void) {
    oled_write_P(PSTR("ay wasup hello\n"), false);
    render_logo();
    return false; 
}
#endif
