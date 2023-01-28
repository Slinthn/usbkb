/**
 * @brief USB initialisation
 * 
 */
#include "usb.h"
#include "descriptors.c"

/**
 * @brief Enable and setup USB (no endpoints, just
 *  allow USB detection by host)
 */
void usb_enable(void) {

  CLI;

  // Power on USB pads regulator
  STS(UHWCON) |= 1 << UVREGE;

  // Configure PLL interface and enable
  STS(PLLCSR) |= (1 << PINDIV) | (1 << PLLE);

  // Wait for PLL to lock
  while (!(STS(PLLCSR) & (1 << PLOCK)));

  // Enable USB interface, USB power pads, and disable clock freeze
  STS(USBCON) |= (1 << OTGPADE) | (1 << USBE);
  STS(USBCON) &= ~(1 << FRZCLK);

  // Set high speed mode
  STS(UDCON) &= ~(1 << LSM);

  // Attach USB
  STS(UDCON) &= ~(1 << DETACH);

  // Enable USB interrupts
  STS(UDIEN) |= (1 << EORSTE) | (1 << SOFE);
  STS(UEIENX) |= 1 << RXSTPE;

  SEI;
}

/**
 * @brief Enable endpoint 0 (control endpoint, obligatory,
 *   as per specification).
 * 
 */
void usb_enable_endpoint0(void) {

  // Select endpoint 0
  STS(UENUM) = 0;

  // Activate endpoint
  STS(UECONX) |= 1 << EPEN;

  // Configure endpoint as type control and direction out
  STS(UECFG0X) = 0;

  // Set size, bank bits, and allocate
  STS(UECFG1X) = (0b010 << EPSIZE) | (0b00 << EPBK) | (1 << ALLOC);

  // Check if endpoint was created successfully
  if (!(STS(UESTA0X) & (1 << CFGOK))) {
    // TODO Error handler?
  }

  STS(UERST) = 1 << EPEN;
  STS(UERST) = 0;
  STS(UEIENX) |= 1 << RXSTPE;
}

/**
 * @brief Call this function to initalise USB in its entirety.
 *   Later, interrupts will be triggered, in which
 *   descriptors will be exchanged
 * 
 */
void usb_init(void) {

  usb_enable();
}

/**
 * @brief Reply to invalid packet sent by the host
 * 
 */
void usb_invalid_packet(void) {

  STS(UECONX) |= (1 << STALLRQ) | (1 << EPEN);
}

/**
 * @brief Stall execution until current bank is free
 * 
 */
void usb_bank_wait(void) {

  while (!(STS(UEINTX) & (1 << TXINI)));
}

/**
 * @brief Parse SETUP descriptor request packets
 */
void usb_setup_descriptor(usb_setup_packet packet) {

  uint8_t *data = 0;
  uint8_t data_size = 0;

  switch (packet.value) {
  case USB_DEVICE_DESCRIPTOR: {
    data = (uint8_t *)&device_descriptor;
    data_size = sizeof(usb_device_descriptor);
  } break;

  case USB_CONFIGURATION_DESCRIPTOR: {
    data = (uint8_t *)&complete_descriptor;
    data_size = sizeof(usb_complete_descriptor);
  } break;

  case USB_HID_DESCRIPTOR: {
    data = (uint8_t *)&complete_descriptor.hid_descriptor;
    data_size = sizeof(usb_hid_descriptor);
  } break;

  case USB_KEYBOARD_REPORT_DESCRIPTOR: {
    data = (uint8_t *)&keyboard_report_descriptor;
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
    usb_bank_wait();

    uint8_t transmit_size = data_size;
    if (transmit_size > 32) {
      transmit_size = 32;
    }

    for (uint8_t i = 0; i < transmit_size; i++) {
      STS(UEDATX) = *data++;
    }

    STS(UEINTX) &= ~(1 << TXINI);

    data_size -= transmit_size;
  }
}

/**
 * @brief Parse SETUP set configuration packets
 * 
 */
void usb_setup_set_packet(usb_setup_packet packet) {

  STS(UEINTX) &= ~(1 << TXINI);

  STS(UENUM) = USB_KEYBOARD_ENDPOINT;
  STS(UECONX) = 1;
  STS(UECFG0X) = 0b11000001;
  STS(UECFG1X) = 0b00000110;
  STS(UERST) = 0x1E;
  STS(UERST) = 0;
}

/**
 * @brief Parse SETUP set address packets
 * 
 */
void usb_setup_set_address(usb_setup_packet packet) {

  STS(UEINTX) &= ~(1 << TXINI);
  usb_bank_wait();

  STS(UDADDR) = (1 << ADDEN) | packet.value;
}

/**
 * @brief Parse SETUP get status packets
 * 
 */
void usb_setup_get_status(void) {

  usb_bank_wait();

  STS(UEDATX) = 0;
  STS(UEDATX) = 0;
  
  STS(UEINTX) &= ~(1 << TXINI);
}

#include "interrupt.c"
