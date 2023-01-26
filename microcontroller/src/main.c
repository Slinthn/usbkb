/*
 * Contains the main entrypoint for the program
 */


typedef unsigned char u8;
typedef unsigned short u16;


#define sizeof_array(x) (sizeof(x) / sizeof((x)[0]))


#include "assembly.c"
#include "atmega32u4.c"
#include "pixel/pixel.c"
#include "usb/usb.c"

#include "keyboard/keyboard.c"




/**
 * @brief Entrypoint for the ATMEGA32U4
 */
int main(void) {
  //keyboard_init();
  //usb_init();

  // LED matrix
  STS(PORTE) = 0;
  NOP;
  STS(DDRE) = 0xff;

  init_pixels();

  while (1) {
    // keyboard_poll();
    
    update_pixels();
    write_pixels(pixels, 60);
  }
}
