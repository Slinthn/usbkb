/**
 * @brief (RGB) LED backlighting, called pixels
 * 
 */

#define PIXEL_MAX_BRIGHTNESS 6

#define PIXEL_DDRx_REGISTER "0x0D"  // DDRE
#define PIXEL_REGISTER "0xE"  // PORTE
#define PIXEL_PORT "6"

struct pixelmeta {
  uint8_t flags;
  uint16_t waittime;
};

struct led_colour {
  uint8_t g;
  uint8_t r;
  uint8_t b;
};

union pixel {
  struct led_colour colour; 
  uint8_t data[3];
};

/**
 * @brief Write the pixels to the input of the led strip
 * 
 * @param pixels Array of pixels to output
 * @param led_count Count of the pixels array
 */
void write_pixels(union pixel *pixels, uint8_t led_count) {

  asm("CBI " PIXEL_REGISTER ", " PIXEL_PORT);

  for (uint8_t i = 0; i < led_count; i++) {
    for (uint8_t j = 0; j < 3; j++) {
      for (uint8_t k = 7; k < 8; k--) {
        uint8_t pixel = pixels[i].data[j] / PIXEL_MAX_BRIGHTNESS;

        if (pixel & (1 << k)) {
          asm("SBI " PIXEL_REGISTER ", " PIXEL_PORT);
          NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP;

          asm("CBI " PIXEL_REGISTER ", " PIXEL_PORT);
          NOP; NOP; NOP; NOP; NOP;
        } else {
          asm("SBI " PIXEL_REGISTER ", " PIXEL_PORT);
          NOP; NOP; NOP; NOP;

          asm("CBI " PIXEL_REGISTER ", " PIXEL_PORT);
          NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP;
        }
      }
    }
  }
}

/**
 * @brief Initialise the pixel component
 * 
 */
void init_pixels() {

  asm("SBI " PIXEL_DDRx_REGISTER ", " PIXEL_PORT);
}
