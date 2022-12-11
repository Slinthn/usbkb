#include "usb.h"
#include "descriptors.c"


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


/*
 * Call when an invalid packet has been sent by the host
 */
void usb_invalid_packet(void) {
  UECONX |= (1 << STALLRQ) | (1 << EPEN);
}


/*
 * Call to stall execution until current bank is free
 */
void usb_bank_wait(void) {
  while (!(UEINTX & (1 << TXINI)));
}


/*
 * Parse SETUP descriptor request packets
 */
void usb_setup_descriptor(usb_setup_packet packet) {
  u8 *data = 0;
  u8 data_size = 0;

  switch (packet.value) {
  case USB_DEVICE_DESCRIPTOR: {
    data = (u8 *)&device_descriptor;
    data_size = sizeof(usb_device_descriptor);
  } break;

  case USB_CONFIGURATION_DESCRIPTOR: {
    data = (u8 *)&complete_descriptor;
    data_size = sizeof(usb_complete_descriptor);
  } break;

  case USB_HID_DESCRIPTOR: {
    data = (u8 *)&complete_descriptor.hid_descriptor;
    data_size = sizeof(usb_hid_descriptor);
  } break;

  case USB_KEYBOARD_REPORT_DESCRIPTOR: {
    data = (u8 *)&keyboard_report_descriptor;
    data_size = sizeof(keyboard_report_descriptor);
  } break;

  default: {
    usb_invalid_packet();
  } break;
  }
  
  if (data_size > packet.length) {
    data_size = packet.length;
  }

  while (data_size) {
    // Wait until can write
    usb_bank_wait();

    u8 transmit_size = data_size;
    if (transmit_size > 32) {
      transmit_size = 32;
    }

    for (u8 i = 0; i < transmit_size; i++) {
      UEDATX = *data++;
    }

    UEINTX &= ~(1 << TXINI);

    data_size -= transmit_size;
  }
}



/*
 * Parse SETUP set configuration packets
 */
void usb_setup_set_packet(usb_setup_packet packet) {
  g_usb_status = packet.value;
  
  UEINTX &= ~(1 << TXINI);

  UENUM = 3;  // TODO keyboard enpoint
  UECONX = 1;
  UECFG0X = 0b11000001;
  UECFG1X = 0b00000110;
  UERST = 0x1E;
  UERST = 0;
}


/*
 * Parse SETUP set address packets
 */
void usb_setup_set_address(usb_setup_packet packet) {
  UEINTX &= ~(1 << TXINI);
  usb_bank_wait();

  UDADDR = (1 << ADDEN) | packet.value;
}


/*
 * Parse SETUP get status packets
 */
void usb_setup_get_status(void) {
  usb_bank_wait();

  UEDATX = 0;
  UEDATX = 0;
  
  UEINTX &= ~(1 << TXINI);
}


/*
 * Send single key press
 */
void usb_send_key(u8 key) {
  UENUM = 3;  // TODO keyboard endpoint
  UEDATX = 0;
  UEDATX = 0;
  UEDATX = key;
  UEDATX = 0;
  UEDATX = 0;
  UEDATX = 0;
  UEDATX = 0;
  UEDATX = 0;
  UEINTX = 0b00111010;
}


#include "interrupt.c"
