/*
 * Contains the main entrypoint for the program
 */


typedef unsigned char u8;
typedef unsigned short u16;


#define sizeof_array(x) (sizeof(x) / sizeof((x)[0]))


#include "assembly.c"
#include "atmega32u4.c"
#include "usb/usb.c"


typedef struct fuse_bits {
  u8 low;
  u8 high;
  u8 extended;
} fuse_bits;


#pragma config SUT_CKSEL = 12  // TODO default


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
