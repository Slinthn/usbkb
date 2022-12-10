#define STS_BYTE(x) (*((u8 *)x))  // Used for AVR STS instruction

#define VECTOR(X) __vector_ ## X

#define INTERRUPT(vector) __attribute__((signal, used)) void vector(void)


typedef unsigned char u8;
typedef unsigned short u16;

#include "assembly.c"
#include "atmega32u4.c"
#include "usb/usb.c"

int main(void) {
  usb_init();
  
  u8 a = 0, b = 0, c = 0;

  while (1) {
    a++;
    if (a == 0) {
      b++;
      if (b == 0) {
        c++;
        if (c == 100) {
          DDRC |= 0xFF;
          PORTC |= 0xFF;
        }
      }
    }
  }
}
