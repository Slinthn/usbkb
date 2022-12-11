/*
 * USB general interrupt
 */
void __attribute__((signal)) __vector_10(void) {
  if (UDINT & (1 << EORSTI)) {
    usb_endpoint0();
  }

  // NOTE Do nothing for a Start of Frame packet

  UDINT = 0;
}


/*
 * USB endpoint interrupt
 */
void __attribute__((signal)) __vector_11(void) {
  // NOTE Currently, only the RXSTPI interrupt is enabled,
  // so we will assume that that is the only reason
  // for this interrupt to be triggered (setup packets),
  // other than device endpoint interrupts.

  UENUM = 0;

  // Parse packet header
  usb_setup_packet packet;
  packet.request_type = UEDATX;
  packet.request = UEDATX;
  packet.value = UEDATX;
  packet.value |= UEDATX << 8;
  packet.index = UEDATX;
  packet.index |= UEDATX << 8;
  packet.length = UEDATX;
  packet.length |= UEDATX << 8;

  // Handshake any possible interrupts
  UEINTX &= ~((1 << RXSTPI) | (1 << RXOUTI) | (1 << TXINI));

  static u8 idle_value = 0;  // TODO global variable?
  static u8 keyboard_protocol = 0;  // TODO global var

  if (packet.request_type == 0b10100001) {  // TODO 
    usb_bank_wait();

    switch (packet.request) {
    case USB_ENDPOINT_GET_REPORT: {
      for (u8 i = 0; i < 8; i++) {
        UEDATX = 0;
      }
    } break;

    case USB_ENDPOINT_GET_IDLE: {
      UEDATX = idle_value;
    } break;

    case USB_ENDPOINT_GET_PROTOCOL: {
      UEDATX = keyboard_protocol;
    } break;

    default: {
      usb_invalid_packet();
    } break;
    }
    
    UEINTX &= ~(1 << TXINI);
  } else if (packet.request_type == 0b00100001) {  // TODO 
    usb_invalid_packet();
  } else {
    switch (packet.request) {
    case USB_GET_DESCRIPTOR: {
      usb_setup_descriptor(packet);
    } break;

    case USB_SET_CONFIGURATION: {
      usb_setup_set_packet(packet);
    } break;

    case USB_SET_ADDRESS: {
      usb_setup_set_address(packet);
    } break;

    case USB_GET_STATUS: {
      usb_setup_get_status();
    } break;

    default: {
      usb_invalid_packet();
    } break;
    }
  }
}
