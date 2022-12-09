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
  
  while (1) {
  }
}
