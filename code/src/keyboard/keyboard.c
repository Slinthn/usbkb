#include "keys.h"


/**
 * DESCRIPTION: Call this function to initalise the keyboard matrix.
 */
void keyboard_init() {
  // Set all as input (by default)
  STS(DDRB) = 0;
  STS(DDRD) = 0;
  STS(DDRF) = 0;

  // Set outputs of matrix (rows)
  STS(DDRB) |= 0x1f;
}


typedef struct keyboard_column {
  u8 pinput;
  u8 index;
  u8 scancode;
} keyboard_column;


typedef struct keyboard_row {
  u8 poutput;
  u8 index;
  u8 scancolumns;
  keyboard_column column[15];
} keyboard_row;


keyboard_row scanrows[] = {
  {
    PORTB, 0, 15,
    {{PORTB, 5, KEY_GRAVE}, {PORTB, 6, KEY_1}, {PORTB, 7, KEY_2},
    {PORTD, 0, KEY_3}, {PORTD, 1, KEY_4}, {PORTD, 2, KEY_5},
    {PORTD, 3, KEY_6}, {PORTD, 4, KEY_7}, {PORTD, 5, KEY_8},
    {PORTD, 6, KEY_9}, {PORTD, 7, KEY_0}, {PORTF, 0, KEY_MINUS},
    {PORTF, 1, KEY_EQUAL}, {PORTF, 4, KEY_BACKSPACE}, {PORTF, 5, KEY_HOME}}
  },

  {
    PORTB, 1, 15,
    {{PORTB, 5, KEY_TAB}, {PORTB, 6, KEY_Q}, {PORTB, 7, KEY_W},
    {PORTD, 0, KEY_E}, {PORTD, 1, KEY_R}, {PORTD, 2, KEY_T},
    {PORTD, 3, KEY_Y}, {PORTD, 4, KEY_U}, {PORTD, 5, KEY_I},
    {PORTD, 6, KEY_O}, {PORTD, 7, KEY_P}, {PORTF, 0, KEY_LEFTBRACE},
    {PORTF, 1, KEY_RIGHTBRACE}, {PORTF, 4, KEY_BACKSLASH}, {PORTF, 5, KEY_BACKSLASH}}
  },

  {
    PORTB, 2, 14,
    {{PORTB, 5, KEY_CAPSLOCK}, {PORTB, 6, KEY_A}, {PORTB, 7, KEY_S},
    {PORTD, 0, KEY_D}, {PORTD, 1, KEY_F}, {PORTD, 2, KEY_G},
    {PORTD, 3, KEY_H}, {PORTD, 4, KEY_J}, {PORTD, 5, KEY_K},
    {PORTD, 6, KEY_L}, {PORTD, 7, KEY_SEMICOLON}, {PORTF, 0, KEY_APOSTROPHE},
    {PORTF, 1, KEY_ENTER}, {PORTF, 4, KEY_PAGEDOWN}}
  }
};


/**
 * DESCRIPTION: Check for any key presses/releases
 */
void keyboard_poll(void) {
  usb_reset_keys(g_keys);

  for (u8 i = 0; i < sizeof_array(scanrows); i++) {
    keyboard_row row = scanrows[i];
    STS(row.poutput) |= 1 << row.index;

    for (u8 j = 0; j < row.scancolumns; j++) {
      keyboard_column column = row.column[j];
      if (!(STS(column.pinput) & (1 << column.index))) {
        usb_add_key(g_keys, column.scancode);
      }
    }
    
    STS(row.poutput) &= ~(1 << row.index);
  }

  usb_send_keys(g_keys);
}
