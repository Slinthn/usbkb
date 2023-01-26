#define PIXEL_FLAG_CYCLER 0x1
#define PIXEL_FLAG_CYCLEG 0x2
#define PIXEL_FLAG_CYCLEB 0x4
#define PIXEL_FLAG_DIRECTIONR 0x8
#define PIXEL_FLAG_DIRECTIONG 0x10
#define PIXEL_FLAG_DIRECTIONB 0x20

struct pixelmeta {
  u8 flags;
  u8 waittime;
};

#pragma pack(push, 1)
struct led_colour {
  u8 g;
  u8 r;
  u8 b;
};
#pragma pack(pop)

#pragma pack(push, 1)
union pixel {
  struct led_colour colour; 
  u8 data[3];
};
#pragma pack(pop)

void write_pixels(union pixel *pixels, u8 led_count) {
  asm("CBI 0x0E, 6");

  for (u8 i = 0; i < led_count; i++) {
    for (u8 j = 0; j < 3; j++) {
      for (u8 k = 7; k < 8; k--) {
        if (pixels[i].data[j] & (1 << k)) {
          asm("SBI 0x0E, 6");
          NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP;

          asm("CBI 0x0E, 6");
          NOP; NOP; NOP; NOP; NOP;
        } else {
          asm("SBI 0x0E, 6");
          NOP; NOP; NOP; NOP;

          asm("CBI 0x0E, 6");
          NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP;
        }
      }
    }
  }
}

void update_pixel_colour(u8 *colour, struct pixelmeta *meta, u8 cycle_flag, u8 next_cycle_flag, u8 direction_flag) {

  if (meta->flags & cycle_flag) {
    if (meta->flags & direction_flag) {
      (*colour)--;
    } else {
      (*colour)++;
    }

    if (*colour == 255) {  // TODO: 255?
      meta->flags |= direction_flag;
    } else if (*colour == 0) {
      meta->flags &= ~direction_flag;
      meta->flags &= ~cycle_flag;
      meta->flags |= next_cycle_flag;
    }
  }
}

union pixel pixels[60] = {0};
struct pixelmeta meta[60] = {0};

void update_pixels() {
  for (u8 i = 0; i < 60; i++) {
    if (meta[i].waittime) {
      meta[i].waittime--;
      continue;
    }

    update_pixel_colour(&pixels[i].colour.r, &meta[i], PIXEL_FLAG_CYCLER, PIXEL_FLAG_CYCLEB, PIXEL_FLAG_DIRECTIONR);
    update_pixel_colour(&pixels[i].colour.g, &meta[i], PIXEL_FLAG_CYCLEG, PIXEL_FLAG_CYCLER, PIXEL_FLAG_DIRECTIONG);
    update_pixel_colour(&pixels[i].colour.b, &meta[i], PIXEL_FLAG_CYCLEB, PIXEL_FLAG_CYCLEG, PIXEL_FLAG_DIRECTIONB);
  }
}

void init_pixels(void) {
  for (u8 i = 0; i < 60; i++) {
    pixels[i].colour.r = 0xFF;
    meta[i].flags |= PIXEL_FLAG_CYCLER;
    meta[i].flags |= PIXEL_FLAG_DIRECTIONR;
    pixels[i].colour.g = 0;
    meta[i].flags |= PIXEL_FLAG_CYCLEG;
    pixels[i].colour.b = 0;
    meta[i].waittime = i * 4;
  }
}
