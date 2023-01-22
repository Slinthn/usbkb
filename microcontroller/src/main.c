/*
 * Contains the main entrypoint for the program
 */


typedef unsigned char u8;
typedef unsigned short u16;


#define sizeof_array(x) (sizeof(x) / sizeof((x)[0]))


#include "assembly.c"
#include "atmega32u4.c"

#pragma config SUT_CKSEL = 14
#pragma config CKDIV8 = 1

#if 0
#include "usb/usb.c"


typedef struct fuse_bits {
  u8 low;
  u8 high;
  u8 extended;
} fuse_bits;



u8 g_keys[USB_HID_MAX_KEYS] = {0};


#include "keyboard/keyboard.c"
#endif

void write_byte(u8 byte) {
  STS(PORTE) &= ~(1 << 6);

  // NOTE: 250 ns per instruction cycle

  for (u8 i = 7; i < 8; i--) {
    if (byte & (1 << i)) {
      // 1
      STS(PORTE) |= 1 << 6;

      // Wait 800 ns (+- 150 ns)
      NOP(); NOP(); NOP();

      STS(PORTE) &= ~(1 << 6);

      // Wait 450 ns (+- 150 ns)
      NOP(); NOP(); NOP();
    } else {
      // 0
      STS(PORTE) |= 1 << 6;

      // Wait 400 ns (+- 150 ns)
      //NOP();

      STS(PORTE) &= ~(1 << 6);

      // Wait 850 ns (+- 150 ns)
      NOP(); NOP(); NOP();
    }
  }
}

/*
 * Entrypoint for the microcontroller
 */
int main(void) {
  //keyboard_init();
  //usb_init();

#if 0
  // Constantly poll keyboard matrix
  while (1) {
    keyboard_poll();
  }
#endif

  // LED matrix
  STS(PORTE) &= ~(1 << 6);
  STS(DDRE) |= 1 << 6;


  cli();

  for (u8 i = 0; i < 3; i++) {
    write_byte(0xFF);
    write_byte(0);
    write_byte(0);
  }

  CODERESET(PORTE, 6);
  sei();
  while (1) {
  }
}
