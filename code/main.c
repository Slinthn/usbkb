#define STS_BYTE(x) (*((unsigned char *)x))  // Used for AVR STS instruction

#define USBCON STS_BYTE(0xD8)
#define FRZCLK 5
#define OTGPADE 4

#define PLLCSR STS_BYTE(0x49)
#define USBE 7
#define PINDIV 4
#define PLLE 1
#define PLOCK 0

#define UDCON STS_BYTE(0xE0)
#define LSM 2
#define DETACH 0

#define UHWCON STS_BYTE(0xD7)
#define UVREGE 0

#define UDIEN STS_BYTE(0xE2)
#define EORSTE 3
#define SOFE 2

#define VECTOR(X) __vector_ ## X

#define INTERRUPT(vector) __attribute__((signal, used)) void vector(void)

#define USB_UNINITIALISED 0
#define USB_ACIVE 1

int g_usb_status = USB_UNINITIALISED;

void cli(void) {
  __asm__("CLI");
}

void sei(void) {
  __asm__("SEI");
}

INTERRUPT(VECTOR(1)) {

}

/*
 * Call this function to initalise USB.
 * Later, interrupts will be triggered, in which
 * descriptors will be exchanged.
 */
void usb_init(void) {
  cli();
  // Power on USB pads regulator
  UHWCON |= 1 << UVREGE;

  // Configure PLL interface and enable
  PLLCSR |= (1 << PINDIV) | (1 << PLLE);

  // Wait for PLL to lock
  while (!(PLLCSR & (1 << PLOCK)));

  // Enable USB interface, USB power pads, and disable clock freeze
  USBCON |= (1 << OTGPADE) | (1 << USBE);
  USBCON &= ~(1 << FRZCLK);

  // Set high speed mode
  UDCON &= ~(1 << LSM);

  // Attach USB
  UDCON &= ~(1 << DETACH);

  UDIEN |= (1 << EORSTE) | (1 << SOFE);
  sei();
}

int main() {
  usb_init();
  
  while (1) {
  }
}

