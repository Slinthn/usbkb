#define STS_BYTE(x) (*((unsigned char *)x))  // Used for AVR STS instruction

#define VECTOR(X) __vector_ ## X

#define INTERRUPT(vector) __attribute__((signal, used)) void vector(void)

#include "assembly.c"
#include "atmega32u4.c"
#include "usb/usb.c"

int main() {
  usb_init();
  
  while (1) {
  }
}

