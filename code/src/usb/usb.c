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

#define UEINTX STS_BYTE(0xE8)
#define RXSTPI 3
#define RXOUTI 2
#define TXINI 0

#define USB_UNINITIALISED 0
#define USB_ACIVE 1

#define UECONX STS_BYTE(0xEB)
#define EPEN 0

#define UENUM STS_BYTE(0xE9)
#define EPNUM 0

#define UECFG0X STS_BYTE(0xEC)
#define EPTYPE 6
#define EPDIR 0

#define UECFG1X STS_BYTE(0xED)
#define EPSIZE 4
#define EPBK 2
#define ALLOC 1

#define UESTA0X STS_BYTE(0xEE)
#define CFGOK 7

#define UERST STS_BYTE(0xEA)
#define EPRST 0

#define UEIENX STS_BYTE(0xF0)
#define RXSTPE 3

#define UEDATX STS_BYTE(0xF1)

#define UDINT STS_BYTE(0xE1)
#define EORSTI 3
#define SOFI 2

#define UDADDR STS_BYTE(0xE3)
#define ADDEN 7

#define USB_SET_ADDRESS 0x5
#define USB_GET_DESCRIPTOR 0x6
#define SET_CONFIGURATION 0x9

u8 g_usb_status = USB_UNINITIALISED;

/*
 * Enable and setup USB (no endpoints, just
 * allow USB detection by host)
 */
void usb_enable(void) {
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

  // Enable USB interrupts
  UDIEN |= (1 << EORSTE) | (1 << SOFE);
  UEIENX |= 1 << RXSTPE;

  sei();
}

/*
 * Enable endpoint 0 (control endpoint, obligatory, as per specification).
 */
void usb_endpoint0(void) {
  // Select endpoint 0
  UENUM = 0;

  // Activate endpoint
  UECONX |= 1 << EPEN;

  // Configure endpoint as type control and direction out
  UECFG0X = 0;

  // Set size, bank bits, and allocate
  UECFG1X = (0b010 << EPSIZE) | (0b00 << EPBK) | (1 << ALLOC);

  // Check if endpoint was created successfully
  if (!(UESTA0X & (1 << CFGOK))) {
    // TODO Error handler?
  }

  UERST = 1 << EPEN;
  UERST = 0;
  UEIENX |= (1 << RXSTPE);
}

/*
 * Call this function to initalise USB in its entirety.
 * Later, interrupts will be triggered, in which
 * descriptors will be exchanged.
 */
void usb_init(void) {
  usb_enable();
}

#include "interrupt.c"
