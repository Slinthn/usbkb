#define STS_BYTE(x) (*((u8 *)x))  // Used for AVR STS instruction

typedef unsigned char u8;
typedef unsigned short u16;

u8 g_keys[6] = {0};

#include "assembly.c"
#include "atmega32u4.c"
#include "usb/usb.c"


int main(void) {
  usb_init();

  // Setup INT0
  EICRA = 0b01;
  PCICR = 1;
  PCMSK0 = 1 << 0;
  EIMSK = 1 << 0;


  DDRB = ~0b01000000;
  PORTB = 0b01000000;

#if 0
  u8 a = 0, b = 0, c = 0;

  u8 keys[] = {0x1c, 0x12, 0x18, 0x15, 0x2c, 0x10, 0x12, 0x10, 0x10, 0x4, 0x2c};
  u8 keyi = 0;

  while (1) {
    if (!(a++))
      if (!(b++)) {
        if (c++ == 20) {
          c = 0;
          //usb_send_key(keys[keyi++]);
          if (keyi == 11)
            keyi = 0;
        }
          //usb_send_key(0);
    }
  }
#endif

  while (1) {
    
  //usb_send_keys(g_keys);
  }

  while (1) {
  }
}
