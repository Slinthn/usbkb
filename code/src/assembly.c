#if 0
u8 __attribute__((naked)) lpm(u16 address) {
  __asm__("MOV R31, R25");
  __asm__("MOV R30, R24");
  __asm__("LPM R24, Z");
  __asm__("RET");
}
#endif

void cli(void) {
  __asm__("CLI");
}

void sei(void) {
  __asm__("SEI");
}
