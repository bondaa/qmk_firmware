#include QMK_KEYBOARD_H

enum layer_namKC {
    _BASE,
    _NUMBERS,
    _SYMBOLS,
    _FNS,
};

enum custom_keycodes {
    LG_LBR = QK_KB_0, // [
    LG_RBR,           // ]
    LG_LCBR,          // {
    LG_RCBR,          // }
    LG_LT,            // <
    LG_GT,            // >
    LG_GRAVE,         // `
    LG_TILD,          // ~
    LG_AT,            // @
    LG_HASH,          // #
    LG_DLR,           // $
    LG_CIRC,          // ^
    LG_AMPR,          // &
    LG_PIPE,          // |
    LG_QUOTE,         // '
    LG_SCLN,          // ;
    LG_COLON,         // :
    LG_DQUO,          // "
    LG_QUES,          // ?
    LG_SLASH,         // /
    LG_DOT,           // .
    LG_COMMA,         // ,
    LG_RU_BE,         // Б (RU only)
    LG_RU_YU,         // Ю (RU only)
    LG_RU_ZHE,        // Ж (RU only)
    LG_RU_E,          // Э (RU only)
    LG_RU_KHA,        // Х (RU only)
    LG_RU_HARD,       // Ъ (RU only)
    LG_RU_YO,         // Ё (RU only)
    RU_TOG,
    CPI_DN,
    CPI_UP
};

#define CPI_STEP 100
#define CPI_MIN 100
#define CPI_MAX 1200
#define RU_TOG_COOLDOWN 180
#define RU_LANG_HOTKEY_DELAY 30

bool RU_LANG = false;
static uint16_t ru_tog_timer = 0;

static void send_lang_hotkey(void) {
    register_code(KC_LCTL);
    wait_ms(RU_LANG_HOTKEY_DELAY);
    tap_code(KC_SPC);
    wait_ms(RU_LANG_HOTKEY_DELAY);
    unregister_code(KC_LCTL);
    wait_ms(RU_LANG_HOTKEY_DELAY);
}

static void send_lg_symbol(uint16_t keycode) {
    if (!RU_LANG) {
        tap_code16(keycode);
    } else {
        send_lang_hotkey();
        tap_code16(keycode);
        send_lang_hotkey();
    }
}

static void send_ru_only(uint16_t keycode) {
    if (RU_LANG) {
        tap_code16(keycode);
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // +------------------------------ BASE (EN|RU) -------------------------------+
    // | TAB | Q Й | W Ц | E У | R К | T Е |       | Y Н | U Г | I Ш | O Щ | P З |   Х |
    // | CTL | A Ф | S Ы | D В | F А | G П |       | H Р | J О | K Л | L Д |   Ж |   Э |
    // | SFT | Z Я | X Ч | C С | V М | B И |       | N Т | M Ь |   Б |   Ю | ALT | TOG |
    //             | HOME| GUI | MO2 | SPC |       | ENT | MO1 | BSP | MUTE|            
    // +---------------------------------------------------------------------------+
    [_BASE] = LAYOUT(
        LT(3, KC_TAB), KC_Q, KC_W, KC_E, KC_R, KC_T,                                   KC_Y, KC_U, KC_I,     KC_O,     KC_P,      LG_RU_KHA,
        KC_LCTL,       KC_A, KC_S, KC_D, KC_F, KC_G,                                   KC_H, KC_J, KC_K,     KC_L,     LG_RU_ZHE, LG_RU_E,
        KC_LSFT,       KC_Z, KC_X, KC_C, KC_V, KC_B,                                   KC_N, KC_M, LG_RU_BE, LG_RU_YU, KC_LALT,   RU_TOG,
                              KC_HOME, XXXXXXX, KC_LGUI, MO(2), KC_SPC,      KC_ENT, MO(1), KC_BSPC, XXXXXXX, KC_KB_MUTE
    ),
    // +--------------------------- NUMBERS (EN=RU) ----------------------------+
    // | ESC |  1  |  2  |  3  |  4  |  5  |       |  6  |  7  |  8  |  9  |  0  | --- |
    // | CTL | --- | --- | --- | --- | --- |       | --- | LFT | DWN | UP  | RGT | --- |
    // | SFT | --- | --- | --- | --- | --- |       | --- | --- | --- | PGU | PGD | --- |
    //             | BOO | --- | MO2 | ENT |       | ENT | --- | --- | BOO |
    // +------------------------------------------------------------------------+
    [_NUMBERS] = LAYOUT(
        KC_ESC,  KC_P1,   KC_P2,   KC_P3,   KC_P4,   KC_P5,                               KC_P6,   KC_P7,   KC_P8,   KC_P9,   KC_P0,   XXXXXXX,
        KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                             XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX,
        KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                             XXXXXXX, XXXXXXX, XXXXXXX, KC_PGUP, KC_PGDN, XXXXXXX,
                                QK_BOOT, XXXXXXX, XXXXXXX, MO(2), KC_ENT,   KC_ENT, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT
    ),
    // +---------------------------- SYMBOLS (EN|RU) ---------------------------+
    // | ESC | --- | [   | _   | ]   |  *  |       |  #  |  \  |  |  |  /  |  <  |  >  |
    // | CTL | --- | (   | -   | )   |  +  |       |  =  |  ?  |  `  |  "  |  @  |  ^  |
    // | SFT | --- | {   | ~   | }   |  .  |       |  ,  |  :  |  ;  |  &  |  $  | --- |
    //             | BOO | GUI | --- | ENT |       | ENT | MO1 | DEL | BOO |
    // +------------------------------------------------------------------------+

    [_SYMBOLS] = LAYOUT(
        KC_ESC,  XXXXXXX, LG_LBR,  S(KC_MINS), LG_RBR,  KC_PAST,                      LG_HASH,  KC_BSLS,  LG_PIPE,  LG_SLASH, LG_LT,  LG_GT,
        KC_LCTL, XXXXXXX, S(KC_9), KC_PMNS,    S(KC_0), KC_PLUS,                      KC_EQL,   LG_QUES,  LG_GRAVE, LG_DQUO,  LG_AT,  LG_CIRC,
        KC_LSFT, XXXXXXX, LG_LCBR, LG_TILD,    LG_RCBR, LG_DOT,                       LG_COMMA, LG_COLON, LG_SCLN,  LG_AMPR,  LG_DLR, XXXXXXX,
                               QK_BOOT, XXXXXXX, KC_LGUI, XXXXXXX, KC_ENT,    KC_ENT, MO(1), KC_DEL, XXXXXXX, QK_BOOT
    ),

    // +----------------------------- FNS (EN=RU) ------------------------------+
    // | ESC | MB1 | F7  | F8  | F9  | --- |       | --- | --- | UP  | --- | PGU | --- |
    // | CTL | MB2 | F4  | F5  | F6  | --- |       | --- | LFT | DN  | RGT | PGD | --- |
    // | SFT | MB3 | F1  | F2  | F3  | --- |       | --- | --- | --- | --- | CPI-| CPI+|
    //             | BOO | --- | --- | --- |       | --- | --- | --- | BOO |
    // +------------------------------------------------------------------------+
    [_FNS] = LAYOUT(
        KC_ESC, MS_BTN1, KC_F7, KC_F8, KC_F9, XXXXXXX,                              XXXXXXX, XXXXXXX, KC_UP, XXXXXXX, KC_PGUP, XXXXXXX,
        KC_LCTL, MS_BTN2, KC_F4, KC_F5, KC_F6, XXXXXXX,                             XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, XXXXXXX,
        KC_LSFT, MS_BTN3, KC_F1, KC_F2, KC_F3, XXXXXXX,                             XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, CPI_DN, CPI_UP,
                                QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        return true;
    }

    switch (keycode) {
        case RU_TOG:
            // Toggle RU_LANG and send system language hotkey.
            if (timer_elapsed(ru_tog_timer) < RU_TOG_COOLDOWN) {
                return false;
            }
            ru_tog_timer = timer_read();
            RU_LANG = !RU_LANG;
            send_lang_hotkey();
            return false;
        case LG_LBR:
            // Prints '[' (with RU->EN->RU wrap when RU_LANG is true).
            send_lg_symbol(KC_LBRC);
            return false;
        case LG_RBR:
            // Prints ']' (with RU->EN->RU wrap when RU_LANG is true).
            send_lg_symbol(KC_RBRC);
            return false;
        case LG_LCBR:
            // Prints '{' (with RU->EN->RU wrap when RU_LANG is true).
            send_lg_symbol(KC_LCBR);
            return false;
        case LG_RCBR:
            // Prints '}' (with RU->EN->RU wrap when RU_LANG is true).
            send_lg_symbol(KC_RCBR);
            return false;
        case LG_LT:
            // Prints '<' (with RU->EN->RU wrap when RU_LANG is true).
            send_lg_symbol(KC_LT);
            return false;
        case LG_GT:
            // Prints '>' (with RU->EN->RU wrap when RU_LANG is true).
            send_lg_symbol(KC_GT);
            return false;
        case LG_GRAVE:
            // Prints '`' (with RU->EN->RU wrap when RU_LANG is true).
            send_lg_symbol(KC_GRV);
            return false;
        case LG_TILD:
            // Prints '~' (with RU->EN->RU wrap when RU_LANG is true).
            send_lg_symbol(KC_TILD);
            return false;
        case LG_AT:
            // Prints '@' (with RU->EN->RU wrap when RU_LANG is true).
            send_lg_symbol(KC_AT);
            return false;
        case LG_HASH:
            // Prints '#' (with RU->EN->RU wrap when RU_LANG is true).
            send_lg_symbol(KC_HASH);
            return false;
        case LG_DLR:
            // Prints '$' (with RU->EN->RU wrap when RU_LANG is true).
            send_lg_symbol(KC_DLR);
            return false;
        case LG_CIRC:
            // Prints '^' (with RU->EN->RU wrap when RU_LANG is true).
            send_lg_symbol(KC_CIRC);
            return false;
        case LG_AMPR:
            // Prints '&' (with RU->EN->RU wrap when RU_LANG is true).
            send_lg_symbol(KC_AMPR);
            return false;
        case LG_PIPE:
            // Prints '|' (with RU->EN->RU wrap when RU_LANG is true).
            send_lg_symbol(KC_PIPE);
            return false;
        case LG_QUOTE:
            // Prints '\'' (with RU->EN->RU wrap when RU_LANG is true).
            send_lg_symbol(KC_QUOT);
            return false;
        case LG_SCLN:
            // Prints ';' without layout switching: RU -> Shift+4, EN -> KC_SCLN.
            tap_code16(RU_LANG ? S(KC_4) : KC_SCLN);
            return false;
        case LG_COLON:
            // Prints ':' without layout switching: RU -> Shift+6, EN -> KC_COLN.
            tap_code16(RU_LANG ? S(KC_6) : KC_COLN);
            return false;
        case LG_DQUO:
            // Prints '"' without layout switching: RU -> Shift+2, EN -> KC_DQUO.
            tap_code16(RU_LANG ? S(KC_2) : KC_DQUO);
            return false;
        case LG_QUES:
            // Prints '?' without layout switching: RU -> Shift+7, EN -> KC_QUES.
            tap_code16(RU_LANG ? S(KC_7) : KC_QUES);
            return false;
        case LG_SLASH:
            // Prints '/' without layout switching: RU -> Shift+Backslash, EN -> KC_SLSH.
            tap_code16(RU_LANG ? S(KC_BSLS) : KC_SLSH);
            return false;
        case LG_DOT:
            // Prints '.' without layout switching: RU -> KC_SLSH, EN -> KC_DOT.
            tap_code16(RU_LANG ? KC_SLSH : KC_DOT);
            return false;
        case LG_COMMA:
            // Prints ',' without layout switching: RU -> Shift+Slash, EN -> KC_COMM.
            tap_code16(RU_LANG ? S(KC_SLSH) : KC_COMM);
            return false;
        case LG_RU_BE:
            // Prints 'Б' only when RU_LANG is true; no-op in EN.
            send_ru_only(KC_COMM);
            return false;
        case LG_RU_YU:
            // Prints 'Ю' only when RU_LANG is true; no-op in EN.
            send_ru_only(KC_DOT);
            return false;
        case LG_RU_ZHE:
            // Prints 'Ж' only when RU_LANG is true; no-op in EN.
            send_ru_only(KC_SCLN);
            return false;
        case LG_RU_E:
            // Prints 'Э' only when RU_LANG is true; no-op in EN.
            send_ru_only(KC_QUOT);
            return false;
        case LG_RU_KHA:
            // Prints 'Х' only when RU_LANG is true; no-op in EN.
            send_ru_only(KC_LBRC);
            return false;
        case LG_RU_HARD:
            // Prints 'Ъ' only when RU_LANG is true; no-op in EN.
            send_ru_only(KC_RBRC);
            return false;
        case LG_RU_YO:
            // Prints 'Ё' only when RU_LANG is true; no-op in EN.
            send_ru_only(KC_GRV);
            return false;
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
    [_BASE] = { ENCODER_CCW_CW(MS_WHLD, MS_WHLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_NUMBERS] = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) },
    [_SYMBOLS] = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) },
    [_FNS] = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) }
};
#endif