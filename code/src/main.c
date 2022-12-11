#define STS_BYTE(x) (*((u8 *)x))  // Used for AVR STS instruction

typedef unsigned char u8;
typedef unsigned short u16;

#include "assembly.c"
#include "atmega32u4.c"
#include "usb/usb.c"

int main(void) {
  usb_init();

  DDRB = ~0b01000000;
  PORTB = 0b01000000;

  u8 a = 0, b = 0, c = 0;

  while (1) {
    if (!(a++))
      if (!(b++)) {
        if (c++ == 5) {
          c = 0;
          PORTB ^= 1 << 5;
          if (UEINTX & (1 << RWAL) && g_usb_status && PINB & 0b01000000) {
            usb_send_key(0x8);
          } else {
            usb_send_key(0);
          }
        }
    }
  }
}
