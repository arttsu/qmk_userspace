#include QMK_KEYBOARD_H

/*
 * Layers
 *
 * _BASE   - Main typing layer with home-row mods
 * _NUM    - Function keys + numbers
 * _SYM    - Symbols
 * _NAV    - Navigation, held via Escape
 * _MEDIA  - Volume + playback controls
 * _SYS    - Firmware/system controls
 * _PLAIN  - Plain QWERTY fallback
 */
enum layer_names {
    _BASE,
    _NUM,
    _SYM,
    _NAV,
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
 * Layer-tap keys
 *
 * Holding both Space keys activates _SYS.
 */
#define SPC_NUM LT(_NUM, KC_SPC)
#define SPC_SYM LT(_SYM, KC_SPC)
#define ESC_NAV LT(_NAV, KC_ESC)


/*
 * Dedicated Shift double-tap detection
 *
 * Both taps must be short, with no intervening key presses.
 * Home-row Shift mods do not participate.
 */
#define CAPS_SHIFT_TAP_TERM 200

static bool     caps_shift_down        = false;
static bool     caps_shift_interrupted = false;
static bool     caps_shift_pending     = false;
static uint16_t caps_shift_pressed_at  = 0;
static uint16_t caps_shift_released_at = 0;


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /*
     * BASE
     *
     * Escape: tap for Escape, hold for navigation.
     * Dedicated Shift: double-tap for Caps Word.
     */
    [_BASE] = LAYOUT_planck_2x2u(
        KC_TAB,     KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSPC,
        ESC_NAV,    HRM_A,    HRM_S,    HRM_D,    HRM_F,    KC_G,     KC_H,     HRM_J,    HRM_K,    HRM_L,    HRM_SCLN, KC_QUOT,
        KC_LSFT,    KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_ENT,
        MO(_MEDIA), KC_LCTL,  KC_LGUI,  KC_LALT,  SPC_NUM,            SPC_SYM,            KC_RALT,  KC_PSCR,  KC_LEFT,  KC_RIGHT
    ),


    /*
     * NUM
     */
    [_NUM] = LAYOUT_planck_2x2u(
        KC_F13,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F16,   KC_ASTR,  KC_7,     KC_8,     KC_9,     KC_SLSH,  XXXXXXX,
        KC_F14,   KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F17,   KC_MINS,  KC_4,     KC_5,     KC_6,     KC_0,     KC_COMM,
        KC_F15,   KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_F18,   KC_PLUS,  KC_1,     KC_2,     KC_3,     KC_DOT,   XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  _______,            _______,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX
    ),


    /*
     * SYM
     */
    [_SYM] = LAYOUT_planck_2x2u(
        KC_TILD,  KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,  KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LBRC,  KC_RBRC,  XXXXXXX,
        XXXXXXX,  KC_PLUS,  KC_EQL,   KC_UNDS,  KC_MINS,  XXXXXXX,  XXXXXXX,  KC_LPRN,  KC_RPRN,  KC_LCBR,  KC_RCBR,  XXXXXXX,
        XXXXXXX,  KC_LT,    KC_GT,    KC_PIPE,  KC_BSLS,  XXXXXXX,  XXXXXXX,  KC_GRV,   KC_COMM,  KC_DOT,   KC_SLSH,  XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  _______,            _______,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX
    ),


    /*
     * NAV
     *
     * H/J/K/L -> Left/Down/Up/Right
     * U/M     -> Page Up/Page Down
     * I/,     -> Home/End
     *
     * Dedicated modifiers remain available for selection
     * and modified navigation shortcuts.
     */
    [_NAV] = LAYOUT_planck_2x2u(
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
        _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RIGHT, XXXXXXX,  XXXXXXX,
        KC_LSFT,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_HOME,  KC_PGDN,  KC_PGUP,  KC_END,   XXXXXXX,  XXXXXXX,
        XXXXXXX,  KC_LCTL,  KC_LGUI,  KC_LALT,  XXXXXXX,            XXXXXXX,            KC_RALT,  XXXXXXX,  XXXXXXX,  XXXXXXX
    ),


    /*
     * MEDIA
     *
     * Playback and volume only.
     */
    [_MEDIA] = LAYOUT_planck_2x2u(
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_MPRV,  KC_MNXT,  KC_MPLY,  XXXXXXX,  XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_BRID,  KC_BRIU,  XXXXXXX,  XXXXXXX,  XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_VOLD,  KC_VOLU,  KC_MUTE,  XXXXXXX,  XXXXXXX,
        _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX
    ),


    /*
     * SYS
     *
     * Activated by holding both thumb layer keys:
     * _NUM + _SYM -> _SYS
     */
    [_SYS] = LAYOUT_planck_2x2u(
        QK_BOOT,     XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
        XXXXXXX,     XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
        XXXXXXX,     XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
        TO(_PLAIN),  XXXXXXX,  XXXXXXX,  XXXXXXX,  _______,            _______,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX
    ),


    /*
     * PLAIN
     *
     * No home-row mods, layer-taps, combos, or Caps Word.
     * Bottom-left returns to _BASE.
     */
    [_PLAIN] = LAYOUT_planck_2x2u(
        KC_TAB,     KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSPC,
        KC_ESC,     KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,
        KC_LSFT,    KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_ENT,
        TO(_BASE),  KC_LCTL,  KC_LGUI,  KC_LALT,  KC_SPC,             KC_SPC,             KC_LEFT,  KC_DOWN,  KC_UP,    KC_RIGHT
    )

};


/*
 * Tri-layer and Caps Word isolation.
 */
layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _NUM, _SYM, _SYS);

    /* Do not carry a Shift double-tap sequence across layers. */
    caps_shift_pending = false;

    if (caps_shift_down) {
        caps_shift_interrupted = true;
    }

    if (get_highest_layer(state | default_layer_state) == _PLAIN) {
        caps_word_off();
    }

    return state;
}


/*
 * Double-tap the dedicated Shift to activate Caps Word.
 *
 * Shift events pass through unchanged, preserving ordinary
 * tapping and holding behavior. Activation happens on release
 * of the second tap.
 */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    const bool on_base =
        get_highest_layer(layer_state | default_layer_state) == _BASE;

    /*
     * Home-row Shift keys retain their mod-tap keycodes, so they
     * do not match KC_LSFT here.
     */
    if (keycode == KC_LSFT) {
        if (record->event.pressed) {
            caps_shift_down        = true;
            caps_shift_interrupted = !on_base;
            caps_shift_pressed_at  = timer_read();

            if (!on_base ||
                timer_elapsed(caps_shift_released_at) >= CAPS_SHIFT_TAP_TERM) {
                caps_shift_pending = false;
            }
        } else {
            const bool short_tap =
                caps_shift_down &&
                on_base &&
                !caps_shift_interrupted &&
                timer_elapsed(caps_shift_pressed_at) < CAPS_SHIFT_TAP_TERM;

            caps_shift_down = false;

            if (!short_tap) {
                caps_shift_pending = false;
            } else if (caps_shift_pending) {
                caps_shift_pending = false;
                caps_word_on();
            } else {
                caps_shift_pending     = true;
                caps_shift_released_at = timer_read();
            }
        }

        return true;
    }

    /* Any other key press breaks the double-tap sequence. */
    if (record->event.pressed) {
        caps_shift_pending = false;

        if (caps_shift_down) {
            caps_shift_interrupted = true;
        }
    }

    return true;
}
