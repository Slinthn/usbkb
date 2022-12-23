#include "keys.h"


/**
 * DESCRIPTION: Call this function to initalise the keyboard matrix.
 */
void keyboard_init() {
  // Set all as input (by default)
  STS(DDRB) = 0;
  STS(DDRD) = 0;
  STS(DDRF) = 0;
  STS(PORTB) = 0xff;
  STS(PORTD) = 0xff;
  STS(PORTF) = 0xff;

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
    {{PINB, 5, KEY_GRAVE}, {PINB, 6, KEY_1}, {PINB, 7, KEY_2},
    {PIND, 0, KEY_3}, {PIND, 1, KEY_4}, {PIND, 2, KEY_5},
    {PIND, 3, KEY_6}, {PIND, 4, KEY_7}, {PIND, 5, KEY_8},
    {PIND, 6, KEY_9}, {PIND, 7, KEY_0}, {PINF, 0, KEY_MINUS},
    {PINF, 1, KEY_EQUAL}, {PINF, 4, KEY_BACKSPACE}, {PINF, 5, KEY_HOME}}
  },

  {
    PORTB, 1, 15,
    {{PINB, 5, KEY_TAB}, {PINB, 6, KEY_Q}, {PINB, 7, KEY_W},
    {PIND, 0, KEY_E}, {PIND, 1, KEY_R}, {PIND, 2, KEY_T},
    {PIND, 3, KEY_Y}, {PIND, 4, KEY_U}, {PIND, 5, KEY_I},
    {PIND, 6, KEY_O}, {PIND, 7, KEY_P}, {PINF, 0, KEY_LEFTBRACE},
    {PINF, 1, KEY_RIGHTBRACE}, {PINF, 4, KEY_BACKSLASH}, {PINF, 5, KEY_BACKSLASH}}
  },

  {
    PORTB, 2, 14,
    {{PINB, 5, KEY_CAPSLOCK}, {PINB, 6, KEY_A}, {PINB, 7, KEY_S},
    {PIND, 0, KEY_D}, {PIND, 1, KEY_F}, {PIND, 2, KEY_G},
    {PIND, 3, KEY_H}, {PIND, 4, KEY_J}, {PIND, 5, KEY_K},
    {PIND, 6, KEY_L}, {PIND, 7, KEY_SEMICOLON}, {PINF, 0, KEY_APOSTROPHE},
    {PINF, 1, KEY_ENTER}, {PINF, 4, KEY_PAGEDOWN}}
  },

  {
    PORTB, 3, 14,
    {{PINB, 5, KEY_LEFTSHIFT}, {PINB, 6, KEY_Z}, {PINB, 7, KEY_X},
    {PIND, 0, KEY_C}, {PIND, 1, KEY_V}, {PIND, 2, KEY_B},
    {PIND, 3, KEY_N}, {PIND, 4, KEY_M}, {PIND, 5, KEY_COMMA},
    {PIND, 6, KEY_DOT}, {PIND, 7, KEY_SLASH}, {PINF, 0, KEY_RIGHTSHIFT},
    {PINF, 1, KEY_UP}, {PINF, 4, KEY_END}}
  },

  {
    PORTB, 4, 10,
    {{PINB, 5, KEY_LEFTCTRL}, {PINB, 6, KEY_MOD_LMETA}, {PINB, 7, KEY_MOD_LALT},  // TODO meta correct?
    {PIND, 2, KEY_SPACE},
    {PIND, 5, KEY_MOD_RALT},
    {PIND, 6, KEY_MOD_RMETA}, {PIND, 7, KEY_MOD_RCTRL}, {PINF, 0, KEY_LEFT},  // TODO meta?
    {PINF, 1, KEY_DOWN}, {PINF, 4, KEY_RIGHT}}
  }
};


/**
 * DESCRIPTION: Check for any key presses/releases
 */
void keyboard_poll(void) {
  usb_reset_keys(g_keys);

  for (u8 i = 0; i < sizeof_array(scanrows); i++) {
    keyboard_row row = scanrows[i];
    STS(row.poutput) &= ~(1 << row.index);

    for (u8 j = 0; j < row.scancolumns; j++) {
      keyboard_column column = row.column[j];
      if (((~STS(column.pinput)) & (1 << column.index))) {
        usb_add_key(g_keys, column.scancode);
      }
    }
    
    STS(row.poutput) |= 1 << row.index;
  }

  usb_send_keys(g_keys);
}
