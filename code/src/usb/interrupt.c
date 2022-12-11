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

  if ((packet.request_type | ~0b00100001) == 0xFF) {  // TODO
    if (packet.request_type & (1 << 7)) {  // TODO
      usb_bank_wait();

      switch (packet.request) {
      case USB_ENDPOINT_GET_REPORT: {
        for (u8 i = 0; i < 8; i++) {
          UEDATX = 0;
        }
      } break;

      case USB_ENDPOINT_GET_IDLE:
      case USB_ENDPOINT_GET_PROTOCOL: {
        UEDATX = 0;
      } break;

      default: {
        usb_invalid_packet();
      } break;
      }
      
      UEINTX &= ~(1 << TXINI);
    } else {
      usb_invalid_packet();
    }
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


/*
 * Test INT0
 */
void __attribute__((signal)) __vector_1(void) {


    PORTB ^= (1 << 5);
return;
  if (usb_check_key(g_keys, 0x8) == 0xFF) {
    usb_add_key(g_keys, 0x8);
    PORTB |= 1 << 5;
  } else {
    usb_remove_key(g_keys, 0x8);
    PORTB &= ~(1 << 5);
    g_keys[0] = 0;
    g_keys[1] = 0;
    g_keys[2] = 0;
    g_keys[3] = 0;
    g_keys[4] = 0;
    g_keys[5] = 0;
  }
}