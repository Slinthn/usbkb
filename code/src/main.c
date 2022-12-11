/*
 * Contains the main entrypoint for the program
 */

typedef unsigned char u8;
typedef unsigned short u16;


#include "assembly.c"
#include "atmega32u4.c"
#include "usb/usb.c"


u8 g_keys[USB_HID_MAX_KEYS] = {0};


#include "keyboard/keyboard.c"


/*
 * Entrypoint for the microcontroller
 */
int main(void) {
  keyboard_init();
  usb_init();

  // Constantly poll keyboard matrix
  while (1) {
    keyboard_poll();
  }
}
