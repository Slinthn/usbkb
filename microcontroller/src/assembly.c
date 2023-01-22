void cli(void) {
  __asm__("CLI");
}

void sei(void) {
  __asm__("SEI");
}

#define NOP() __asm__("NOP");

#define T0() NOP(); \
  NOP(); \
  NOP(); \
  NOP(); \
  NOP();

#define T1() NOP(); \
  NOP(); \
  NOP(); \
  NOP();

#define CODE0(port, pin) STS(port) |= 1 << pin; T1(); STS(port) &= ~(1 << pin); T0();

#define CODE1(port, pin) STS(port) |= 1 << pin; T0(); STS(port) &= ~(1 << pin); T1();

#define CODERESET(port, pin) STS(port) |= 1 << pin; STS(port) &= ~(1 << pin); T0(); T1();
