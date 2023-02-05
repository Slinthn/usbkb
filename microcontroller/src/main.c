/**
 * @brief Contains the entrypoint for the process
 */

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;

#define sizeof_array(x) (sizeof(x) / sizeof((x)[0]))

#include "atmega32u4.h"

#include "pixel/pixel.c"
#include "pixel/rgb/pixel_rgb.c"

//#include "usb/usb.c"

//#include "keyboard/usb_keyboard.c"
//#include "keyboard/keyboard.c"

/**
 * @brief Entrypoint for the ATMEGA32U4
 * 
 */
int main(void) {

  //keyboard_init();
  //usb_init();

  init_pixels_rgbwave();

  // TODO: temp DDR shits
  STS(DDRF) |= 1 << 5;
  STS(DDRF) &= ~(1 << 6);

  STS(PORTF) &= ~(1 << 5);
  STS(PORTF) |= (1 << 6);

  while (1) {
    //keyboard_poll();

    if (STS(PINF) & (1 << 6)) {
      update_pixels_rgbwave();
      write_pixels_rgbwave();
    }
  }
}
