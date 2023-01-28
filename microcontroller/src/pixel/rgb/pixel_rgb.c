/**
 * @brief Backlighting RGB wave effect
 * 
 */

#define PIXEL_COUNT 68

union pixel g_pixels[PIXEL_COUNT] = {0};
struct pixelmeta g_meta[PIXEL_COUNT] = {0};

#define PIXEL_FLAG_CYCLER 0x1
#define PIXEL_FLAG_CYCLEG 0x2
#define PIXEL_FLAG_CYCLEB 0x4
#define PIXEL_FLAG_DIRECTIONR 0x8
#define PIXEL_FLAG_DIRECTIONG 0x10
#define PIXEL_FLAG_DIRECTIONB 0x20

/**
 * @brief Updates a specific led pixel colour (red, green, OR blue) to create
 *   an RGB wave
 * 
 * @param colour Pointer to the value of the current value of the brighness of
 *   the colour. Will be written to with the new value
 * @param meta This colour's led's meta
 * @param cycle_flag The cycle flag applicable to this colour
 * @param next_cycle_flag The next cycle flag to update with regards to this
 *   colour (for an RGB wave effect)
 * @param direction_flag The direction flag applicable to this colour
 */
void update_pixel_rgbwave(uint8_t *colour, struct pixelmeta *meta,
  uint8_t cycle_flag, uint8_t next_cycle_flag, uint8_t direction_flag) {

  if (meta->flags & cycle_flag) {
    if (meta->flags & direction_flag)
      (*colour)--;
    else
      (*colour)++;

    if (*colour == 255) {
      meta->flags |= direction_flag;
    } else if (*colour == 0) {
      meta->flags &= ~direction_flag;
      meta->flags &= ~cycle_flag;
      meta->flags |= next_cycle_flag;
    }
  }
}


/**
 * @brief Updates the light of each led in the led backlightings for an RGB wave
 * 
 */
void update_pixels_rgbwave(void) {

  for (uint8_t i = 0; i < 60; i++) {
    struct pixelmeta *meta = &g_meta[i];
    union pixel *pixel = &g_pixels[i];

    if (meta->waittime) {
      meta->waittime--;
      continue;
    }


    update_pixel_rgbwave(&pixel->colour.r, meta,
      PIXEL_FLAG_CYCLER, PIXEL_FLAG_CYCLEB, PIXEL_FLAG_DIRECTIONR);

    update_pixel_rgbwave(&pixel->colour.g, meta,
      PIXEL_FLAG_CYCLEG, PIXEL_FLAG_CYCLER, PIXEL_FLAG_DIRECTIONG);

    update_pixel_rgbwave(&pixel->colour.b, meta,
      PIXEL_FLAG_CYCLEB, PIXEL_FLAG_CYCLEG, PIXEL_FLAG_DIRECTIONB);
  }
}

/**
 * @brief Initialises the led backlighting (WS2812B currently).
 *   Should be proceeded by calls to update_pixels to constanly
 *   update the gradient.
 * 
 */
void init_pixels_rgbwave(void) {

  for (uint8_t i = 0; i < 60; i++) {
    g_pixels[i].colour.r = 0xFF;
    g_pixels[i].colour.g = 0;
    g_pixels[i].colour.b = 0;
    g_meta[i].flags |= PIXEL_FLAG_CYCLER | PIXEL_FLAG_DIRECTIONR
      | PIXEL_FLAG_CYCLEG;

    g_meta[i].waittime = i * 8;
  }

  init_pixels();
}

/**
 * @brief Writes the RGB data out to the led port
 * 
 */
void write_pixels_rgbwave(void) {

  write_pixels(g_pixels, PIXEL_COUNT);
}
