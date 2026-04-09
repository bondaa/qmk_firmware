#include QMK_KEYBOARD_H

enum layer_namKC {
    _BASE,
    _SYMBOLS,
    _NUMBERS,
    _FNS
};

enum custom_keycodes {
    CPI_DN = QK_KB_0,
    CPI_UP
};

#define CPI_STEP 100
#define CPI_MIN 100
#define CPI_MAX 1200
#define CPI_DEFAULT 300

void keyboard_post_init_user(void) {
    pointing_device_set_cpi(CPI_DEFAULT);
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // +------------------------------ BASE (EN|RU) -----------------------------------+
    // | TAB | Q Й | W Ц | E У | R К | T Е |       | Y Н | U Г | I Ш | O Щ | P З | [ Х |
    // | CTL | A Ф | S Ы | D В | F А | G П |       | H Р | J О | K Л | L Д | ; Ж | ' Э |
    // | SFT | Z Я | X Ч | C С | V М | B И |       | N Т | M Ь | , Б | . Ю | / . | LALT|
    //             | HOME| GUI | MO2 | SPC |       | ENT | MO1 | BSP | MUTE|            
    // +-------------------------------------------------------------------------------+
    [_BASE] = LAYOUT(
        LT(3, KC_TAB), KC_Q, KC_W, KC_E, KC_R, KC_T,                                  KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC,
        KC_LCTL,       KC_A, KC_S, KC_D, KC_F, KC_G,                                  KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
        KC_LSFT,       KC_Z, KC_X, KC_C, KC_V, KC_B,                                  KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, MT(MOD_LALT, KC_BSLS),
                              KC_HOME, _______, KC_LGUI, MO(2), KC_SPC,      KC_ENT, MO(1), KC_BSPC, _______, KC_MUTE
    ),
    // +------------------------------ SYMBOLS (EN|RU) --------------------------------+
    // | TAB | # № | [ х |  _  | ] ъ | @ " |       |  +  | --- | UP  | --- | PGUP| BSPC|
    // | CTL | $ ; | ( ( |  -  | ) ) | ! ! |       |  *  | LFT | DWN | RGT | PGDN| % % |
    // | SFT | ^ : | { Х | ~ Ë | } Ъ | & ? |       |  =  |  \  | | / | / . | < Б | > Ю |
    //             | HOME| GUI | --- | SPC |       | ENT | --- | DEL | MUTE|            
    // +-------------------------------------------------------------------------------+
    [_SYMBOLS] = LAYOUT(
        KC_ESC,  S(KC_3), KC_LBRC,    S(KC_MINS), KC_RBRC,    S(KC_2),               KC_PLUS, XXXXXXX, KC_UP,      XXXXXXX, KC_PGUP,    KC_BSPC,
        KC_LCTL, S(KC_4), S(KC_9),    KC_MINS,    S(KC_0),    S(KC_1),               KC_PAST, KC_LEFT, KC_DOWN,    KC_RGHT, KC_PGDN,    S(KC_5),
        KC_LSFT, S(KC_6), S(KC_LBRC), S(KC_GRV),  S(KC_RBRC), S(KC_7),               KC_EQL,  KC_BSLS, S(KC_BSLS), KC_SLSH, S(KC_COMM), S(KC_DOT),
                               QK_BOOT, _______, KC_LGUI, XXXXXXX, KC_SPC,    KC_ENT, XXXXXXX, KC_DEL, _______, QK_BOOT
    ),
    // +--------------------------- NUMBERS (EN=RU) -----------------------------------+
    // | ESC |  1  |  2  |  3  |  4  |  5  |       |  6  |  7  |  8  |  9  |  0  | ` ё |
    // | CTL | --- | --- | --- | --- | --- |       |  +  |  *  |  =  | --- | --- | --- |
    // | SFT | --- | --- | --- | --- | --- |       |  -  |  /  | / . | . Ю | / . | --- |
    //             | BOO | --- | --- | ENT |       | ENT | --- | BSP | BOO |
    // +-------------------------------------------------------------------------------+
    [_NUMBERS] = LAYOUT(
        KC_ESC,  KC_P1,   KC_P2,   KC_P3,   KC_P4,   KC_P5,                     KC_P6,   KC_P7,   KC_P8,      KC_P9,   KC_P0,   KC_GRV,
        KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   KC_PLUS, KC_PAST, KC_EQL,     XXXXXXX, XXXXXXX, XXXXXXX,
        KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   KC_MINS, KC_PSLS, S(KC_BSLS), KC_DOT,  KC_SLSH, XXXXXXX,
                                QK_BOOT, _______, XXXXXXX, XXXXXXX, KC_ENT,   KC_ENT, XXXXXXX, KC_BSPC, _______, QK_BOOT
    ),
    // +----------------------------- FNS (EN=RU) -------------------------------------+
    // | ESC | F1  | F2  | F8  | F4  | F5  |       | F6  | F7  | F8  | F9  | F10 | F11 |    
    // | CTL | --- | --- | --- | --- | --- |       | --- | --- | --- | --- | --- | F12 |
    // | SFT | --- | --- | --- | --- | --- |       | --- | --- | --- | --- | CPI-| CPI+|
    //             | BOO | MB1 | MB2 | MB3 |       | --- | --- | --- | BOO |
    // +-------------------------------------------------------------------------------+
    [_FNS] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_F12,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, CPI_DN,  CPI_UP,
                                QK_BOOT, _______, MS_BTN1, MS_BTN2, MS_BTN3,  KC_ENT, XXXXXXX, XXXXXXX, _______, QK_BOOT
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        return true;
    }

    switch (keycode) {
        case CPI_DN: {
            uint16_t cpi = pointing_device_get_cpi();
            if (cpi > CPI_MIN) {
                cpi = (cpi > (CPI_MIN + CPI_STEP)) ? (cpi - CPI_STEP) : CPI_MIN;
                pointing_device_set_cpi(cpi);
            }
            return false;
        }
        case CPI_UP: {
            uint16_t cpi = pointing_device_get_cpi();
            if (cpi < CPI_MAX) {
                cpi = (cpi < (CPI_MAX - CPI_STEP)) ? (cpi + CPI_STEP) : CPI_MAX;
                pointing_device_set_cpi(cpi);
            }
            return false;
        }
    }

    return true;
}

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE] = { ENCODER_CCW_CW(QK_MOUSE_WHEEL_UP, QK_MOUSE_WHEEL_DOWN ), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_SYMBOLS] = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) },
    [_NUMBERS] = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) },
    [_FNS] = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) }
};
#endif
