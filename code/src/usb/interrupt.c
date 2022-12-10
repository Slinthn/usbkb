#include "descriptors.c"


/*
 * USB general interrupt
 */
void __attribute__((signal)) __vector_10(void) {
  if (UDINT & (1 << EORSTI)) {
    usb_endpoint0();
    // TODO ??
  }

  if (UDINT & (1 << SOFI) && g_usb_status) {
    UENUM = 3;  // TODO Endpoint

    if (UEINTX & (1 << RWAL)) {

      UEDATX = 0;
      UEDATX = 0;
      UEDATX = 0x9;
      UEDATX = 0;
      UEDATX = 0;
      UEDATX = 0;
      UEDATX = 0;
      UEDATX = 0;
      UEINTX = 0b00111010;
    }
  }

  UDINT = 0;
}


/*
 * USB endpoint interrupt
 */
void __attribute__((signal)) __vector_11(void) {
  // Currently, only the RXSTPI endpoint is enabled,
  // so we will assume that that is the only reason
  // for this interrupt to be triggered (setup packets).

  UENUM = 0;

  usb_setup_packet packet;
  packet.request_type = UEDATX;
  packet.request = UEDATX;
  packet.value = UEDATX;
  packet.value |= UEDATX << 8;
  packet.index = UEDATX;
  packet.index |= UEDATX << 8;
  packet.length = UEDATX;
  packet.length |= UEDATX << 8;

  UEINTX &= ~((1 << RXSTPI) | (1 << RXOUTI) | (1 << TXINI));

  switch (packet.request) {
  case USB_GET_DESCRIPTOR: {
    u8 *data = 0;
    u8 data_size = 0;

    switch (packet.value) {
    case 0x100: {
      data = (u8 *)&device_descriptor;
      data_size = sizeof(usb_device_descriptor);
    } break;

    case 0x200: {
      data = (u8 *)&complete_descriptor;
      data_size = sizeof(usb_complete_descriptor);
    } break;

    case 0x2100: {
      data = (u8 *)&complete_descriptor.hid_descriptor;
      data_size = sizeof(usb_hid_descriptor);
    } break;

    case 0x2200: {
      data = (u8 *)&bytes;
      data_size = sizeof(bytes);
    } break;

    default: {
      UECONX |= (1 << STALLRQ) | (1 << EPEN);
    } break;
    }
    
    if (data_size > packet.length) {
      data_size = packet.length;
    }

    while (data_size) {
      u8 transmit_size = data_size;
      if (transmit_size > 32) {
        transmit_size = 32;
      }

      while (!(UEINTX & (1 << TXINI)));

#if 0
      if (UEINTX & (1 << RXOUTI)) {
        return;
      }
#endif

      for (u8 i = 0; i < transmit_size; i++) {
        UEDATX = *data++;
      }

      UEINTX &= ~(1 << TXINI);

      data_size -= transmit_size;
    }

  } break;

  case USB_SET_CONFIGURATION: {
    g_usb_status = packet.value;
    
    UEINTX &= ~(1 << TXINI);

    UENUM = 3;  // TODO keyboard enpoint
    UECONX = 1;
    UECFG0X = 0b11000001;
    UECFG1X = 0b00000110;
    UERST = 0x1E;
    UERST = 0;
  } break;

  case USB_GET_CONFIGURATION: {
  } break;

  case USB_SET_ADDRESS: {
    UEINTX &= ~(1 << TXINI);
    while (!(UEINTX & (1 << TXINI)));

    UDADDR = (1 << ADDEN) | packet.value;
  } break;

  case USB_GET_STATUS: {
    while (!(UEINTX & (1 << TXINI)));

    UEDATX = 0;
    UEDATX = 0;
    
    UEINTX &= ~(1 << TXINI);
  } break;

  default: {
  } break;
  }

  static u8 idle_value = 0;  // TODO global variable?
  static u8 keyboard_protocol = 0;  // TODO global var

  if (packet.request_type == 0b10100001) {  // TODO 
    switch (packet.request) {
    case 0x1: {  // TODO GET_REPORT
      while (!(UEINTX & (1 << TXINI)));

      for (u8 i = 0; i < 6; i++) {
        UEDATX = 0;
      }

      UEINTX &= ~(1 << TXINI);
    } break;

    case 0x2: {  // TODO GET_IDLE
      while (!(UEINTX & (1 << TXINI)));

      UEDATX = idle_value;

      UEINTX &= ~(1 << TXINI);
    } break;

    case 0x3: { // TODO GET_PROTOCOL
      while (!(UEINTX & (1 << TXINI)));

      UEDATX = keyboard_protocol;

      UEINTX &= ~(1 << TXINI);
    } break;
    }
  } else if (packet.request_type == 0b00100001) {
    switch (packet.request) {
    case 0x9: {  // TODO SET_REPORT
      while (!(UEINTX & (1 << RXOUTI)));

      u8 some_fucking_variable = UEDATX;

      UEINTX &= ~(1 << TXINI);
      UEINTX &= ~(1 << RXOUTI);
    } break;

    case 0xA: {  // TODO SET_IDLE
      idle_value = packet.value;

      UEINTX &= ~(1 << TXINI);
    } break;

    case 0xB: { // TODO SET_PROTOCOL
      keyboard_protocol = packet.value;

      UEINTX &= ~(1 << TXINI);
    } break;
    }
  }
}
