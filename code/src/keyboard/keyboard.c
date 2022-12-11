#include "keys.h"


/*
 * Call this function to initalise the keyboard matrix.
 */
void keyboard_init() {
  DDRD = 0;

  // Set outputs of matrix
  DDRD |= (1 << 0) | (1 << 1);

  PORTD |= (1 << 2) | (1 << 3);
}


/*
 * Check for any key presses/releases
 */
void keyboard_poll(void) {
  for (u8 i = 0; i < 6; i++) {
    g_keys[i] = 0;
  }

  PORTD &= ~(1 << 1);
  PORTD |= (1 << 0);
  nop();
  nop();
  if (!(PIND & (1 << 2))) {
    usb_add_key(g_keys, KEY_S);
  }

  if (!(PIND & (1 << 3))) {
    usb_add_key(g_keys, KEY_A);
  }

  PORTD &= ~(1 << 0);
  nop();
  nop();
  PORTD |= (1 << 1);
  nop();
  nop();
  if (!(PIND & (1 << 2))) {
    usb_add_key(g_keys, KEY_W);
  }

  if (!(PIND & (1 << 3))) {
    usb_add_key(g_keys, KEY_D);
  }

  usb_send_keys(g_keys);
}
