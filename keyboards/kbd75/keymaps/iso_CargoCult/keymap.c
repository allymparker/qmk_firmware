#include QMK_KEYBOARD_H

#define RGBLIGHT_SLEEP

//Tap Dance Declarations
enum {
  TD_CAPSLOCK = 0
};

//Custom Keycodes
#define _______ KC_TRNS
#define TD_CPL TD(TD_CAPSLOCK)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[0] = LAYOUT(
    KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_PSCR,  KC_PAUS,  KC_DEL,
    KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_DEL,   KC_BSPC,  KC_HOME,
    KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_PGUP,
    TD_CPL,   KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,                      KC_ENT,   KC_PGDN,
    KC_LSFT,  KC_NUBS,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,            KC_UP,    KC_END,
    KC_LCTL,  KC_LGUI,  KC_LALT,                      KC_SPC,   KC_SPC,   KC_SPC,                       KC_RALT,  MO(1),    KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT
  ),

	[1] = LAYOUT(
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  RESET,    _______,
    _______,  RGB_TOG,  RGB_MOD,  RGB_HUI,  RGB_HUD,  RGB_SAI,  RGB_SAD,  RGB_VAI,  RGB_VAD,  _______,  _______,  _______,  _______,  _______,            _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,                      _______,  _______,
    _______,  _______,  _______,  _______,  BL_DEC,   BL_TOGG,  BL_INC,   BL_STEP,  _______,  _______,  _______,  _______,  _______,            KC_VOLU,  _______,
    _______,  _______,  _______,                      KC_MPLY,  KC_MPLY,  KC_MPLY,                      _______,  _______,  _______,  KC_MPRV,  KC_VOLD,  KC_MNXT
  )
};

void led_set_user(uint8_t usb_led) {
	if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
		DDRB |= (1 << 2); PORTB &= ~(1 << 2);
	} else {
		DDRB &= ~(1 << 2); PORTB &= ~(1 << 2);
	}
}

qk_tap_dance_action_t tap_dance_actions[] = {
  //Double tap for Caps Lock
  [TD_CAPSLOCK]  = ACTION_TAP_DANCE_DOUBLE(KC_TRNS, KC_CAPS)
};

static bool lalt_held = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode){
    case KC_LALT:
      lalt_held = record->event.pressed;
      return true;
    case KC_PAUS:
      // If Left ALT is held, send INSERT instead of PAUSE
      if (lalt_held && record->event.pressed) {
        SEND_STRING(SS_TAP(X_INSERT));
        return false;
      } else {
        return true;
      }
    default: return true;   // Let QMK handle the rest as usual
  }
}
