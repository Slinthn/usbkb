#include "usb.h"

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
