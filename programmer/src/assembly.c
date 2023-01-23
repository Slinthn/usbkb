void cli(void) {
  __asm__("CLI");
}

void sei(void) {
  __asm__("SEI");
}

#define NOP() __asm__("NOP");
