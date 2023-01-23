/*
 * Contains the main entrypoint for the program
 */

typedef unsigned char u8;
typedef unsigned short u16;

#define sizeof_array(x) (sizeof(x) / sizeof((x)[0]))

#include "assembly.c"
#include "atmega32u4.c"
#include "usb/usb.c"

/**
 * @brief Entrypoint
 */
int main(void) {
  usb_init();

  while (1) {
  }
}
