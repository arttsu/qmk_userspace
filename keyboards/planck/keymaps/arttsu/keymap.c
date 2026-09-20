#include QMK_KEYBOARD_H

/*
 * Layers
 *
 * _BASE   - Main typing layer with home-row mods
 * _NUM    - Function keys + numbers
 * _SYM    - Symbols
 * _MEDIA
 * _SYS    - Numpad + firmware/system controls
 * _PLAIN  - Plain QWERTY fallback layer
 */
enum layer_names {
    _BASE,
    _NUM,
    _SYM,
    _MEDIA,
    _SYS,
    _PLAIN,
};

/*
 * Home-row mods
 *
 * Tap  -> letter
 * Hold -> modifier
 */
#define HRM_A    LGUI_T(KC_A)
#define HRM_S    LSFT_T(KC_S)
#define HRM_D    LALT_T(KC_D)
#define HRM_F    LCTL_T(KC_F)

#define HRM_J    RCTL_T(KC_J)
#define HRM_K    LALT_T(KC_K)
#define HRM_L    RSFT_T(KC_L)
#define HRM_SCLN RGUI_T(KC_SCLN)


/*
 * Thumb keys
 *
 * Tap  -> Space
 * Hold -> layer
 */
#define SPC_NUM LT(_NUM, KC_SPC)
#define SPC_SYM LT(_SYM, KC_SPC)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /*
     * BASE
     *
     * ,-----------------------------------------------------------------------------------.
     * | Tab  |  Q   |  W   |  E   |  R   |  T   |  Y   |  U   |  I   |  O   |  P   | Bspc |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Esc  | A/GUI| S/Sft| D/Alt| F/Ctl|  G   |  H   | J/Ctl| K/Alt| L/Sft| ;/GUI|  '   |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |Shift |  Z   |  X   |  C   |  V   |  B   |  N   |  M   |  ,   |  .   |  /   |Enter |
     * |------+------+------+------+-------------+-------------+------+------+------+------|
     * |Media | Ctrl | GUI  | Alt  |  Space/Num  |  Space/Sym  | RAlt |PrtSc | Ins  | Del  |
     * `-----------------------------------------------------------------------------------'
     */
    [_BASE] = LAYOUT_planck_2x2u(
        KC_TAB,     KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSPC,
        KC_ESC,     HRM_A,    HRM_S,    HRM_D,    HRM_F,    KC_G,     KC_H,     HRM_J,    HRM_K,    HRM_L,    HRM_SCLN, KC_QUOT,
        KC_LSFT,    KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_ENT,
        MO(_MEDIA), KC_LCTL,  KC_LGUI,  KC_LALT,  SPC_NUM,            SPC_SYM,            KC_RALT,  KC_PSCR,  KC_INS,   KC_DEL
    ),


    /*
     * NUM
     */
    [_NUM] = LAYOUT_planck_2x2u(
        KC_F13,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F16,   KC_ASTR,  KC_7,     KC_8,     KC_9,     KC_SLSH,  XXXXXXX,
        KC_F14,   KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F17,   KC_MINS,  KC_4,     KC_5,     KC_6,     KC_0,     KC_COMM,
        KC_F15,   KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_F18,   KC_PLUS,  KC_1,     KC_2,     KC_3,     KC_DOT,   XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            MO(_SYS),           XXXXXXX,  XXXXXXX,  XXXXXXX,  CW_TOGG
    ),


    /*
     * SYM
     */
    [_SYM] = LAYOUT_planck_2x2u(
        KC_TILD,  KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,  KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LBRC,  KC_RBRC,  XXXXXXX,
        XXXXXXX,  KC_PLUS,  KC_EQL,   KC_UNDS,  KC_MINS,  XXXXXXX,  XXXXXXX,  KC_LPRN,  KC_RPRN,  KC_LCBR,  KC_RCBR,  XXXXXXX,
        XXXXXXX,  KC_LT,    KC_GT,    KC_PIPE,  KC_BSLS,  XXXXXXX,  XXXXXXX,  KC_GRV,   KC_COMM,  KC_DOT,   KC_SLSH,  XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  MO(_SYS),           XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX
    ),


    /*
     * MEDIA
     */
    [_MEDIA] = LAYOUT_planck_2x2u(
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_MPRV,  KC_MNXT,  KC_MPLY,  XXXXXXX,  XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_VOLD,  KC_VOLU,  KC_MUTE,  XXXXXXX,  XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
        _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX
    ),


    /*
     * SYS
     */
    [_SYS] = LAYOUT_planck_2x2u(
        QK_BOOT,     XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
        XXXXXXX,     XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
        XXXXXXX,     XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
        TO(_PLAIN),  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX
    ),


    /*
     * PLAIN
     */
    [_PLAIN] = LAYOUT_planck_2x2u(
        KC_TAB,     KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSPC,
        KC_ESC,     KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,
        KC_LSFT,    KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_ENT,
        TO(_BASE),  KC_LCTL,  KC_LGUI,  KC_LALT,  KC_SPC,             KC_SPC,             KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT
    )

};

enum combos {
    UI_UP,
    IO_PGUP,
    OP_HOME,

    MCOMM_DOWN,
    COMMDOT_PGDN,
    DOTSLSH_END,

    TY_LEFT,
    YU_RIGHT,

    CV_F19
};

const uint16_t PROGMEM ui_combo[]       = {KC_U,    KC_I,    COMBO_END};
const uint16_t PROGMEM io_combo[]       = {KC_I,    KC_O,    COMBO_END};
const uint16_t PROGMEM op_combo[]       = {KC_O,    KC_P,    COMBO_END};

const uint16_t PROGMEM mcomm_combo[]    = {KC_M,    KC_COMM, COMBO_END};
const uint16_t PROGMEM commdot_combo[]  = {KC_COMM, KC_DOT,  COMBO_END};
const uint16_t PROGMEM dotslsh_combo[]  = {KC_DOT,  KC_SLSH, COMBO_END};

const uint16_t PROGMEM ty_combo[]       = {KC_T,    KC_Y,    COMBO_END};
const uint16_t PROGMEM yu_combo[]       = {KC_Y,    KC_U,    COMBO_END};

const uint16_t PROGMEM cv_combo[]       = {KC_C, KC_V, COMBO_END};

combo_t key_combos[] = {
    [UI_UP]        = COMBO(ui_combo,      KC_UP),
    [IO_PGUP]      = COMBO(io_combo,      KC_PGUP),
    [OP_HOME]      = COMBO(op_combo,      KC_HOME),

    [MCOMM_DOWN]   = COMBO(mcomm_combo,   KC_DOWN),
    [COMMDOT_PGDN] = COMBO(commdot_combo, KC_PGDN),
    [DOTSLSH_END]  = COMBO(dotslsh_combo, KC_END),

    [TY_LEFT]      = COMBO(ty_combo,      KC_LEFT),
    [YU_RIGHT]     = COMBO(yu_combo,      KC_RIGHT),

    [CV_F19]       = COMBO(cv_combo,      KC_F19),
};
