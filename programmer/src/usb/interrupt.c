/**
 * @brief USB general interrupt
 */
void __attribute__((signal)) __vector_10(void) {

  // On reset, setup endpoint 0
  if (STS(UDINT) & (1 << EORSTI)) {
    usb_endpoint0();
  }

  STS(UDINT) = 0;
  
  // NOTE Do nothing for a Start of Frame packet
}

/**
 * @brief USB endpoint interrupt
 */
void __attribute__((signal)) __vector_11(void) {

  // NOTE Currently, only the RXSTPI interrupt is enabled,
  // so we will assume that that is the only reason
  // for this interrupt to be triggered (setup packets),
  // other than device endpoint interrupts.

  STS(UENUM) = 0;

  // Parse packet header
  usb_setup_packet packet;
  packet.request_type = STS(UEDATX);
  packet.request = STS(UEDATX);
  packet.value = STS(UEDATX);
  packet.value |= STS(UEDATX) << 8;
  packet.index = STS(UEDATX);
  packet.index |= STS(UEDATX) << 8;
  packet.length = STS(UEDATX);
  packet.length |= STS(UEDATX) << 8;

  // Handshake any possible interrupts
  STS(UEINTX) &= ~((1 << RXSTPI) | (1 << RXOUTI) | (1 << TXINI));

  // Check if request is an interface
  if ((packet.request_type | ~(USB_TYPE_CLASS | USB_RECIPIENT_INTERFACE)) == 0xFF) {
    // Check if device is required to send data to host
    // NOTE We will not send keyboard strokes here
    if (packet.request_type & USB_TRANSFER_DEVICE_TO_HOST) {
      usb_bank_wait();

      switch (packet.request) {
      case USB_ENDPOINT_GET_REPORT: {
        for (u8 i = 0; i < 8; i++) {
          STS(UEDATX) = 0;
        }
      } break;

      case USB_ENDPOINT_GET_IDLE:
      case USB_ENDPOINT_GET_PROTOCOL: {
        STS(UEDATX) = 0;
      } break;

      default: {
        usb_invalid_packet();
      } break;
      }
      
      STS(UEINTX) &= ~(1 << TXINI);
    } else {
      // Since host to device requests are optional,
      //   we will opt to not implement them
      usb_invalid_packet();
    }
  } else {
    // This packet was not destined for an interface, but rather
    // the configuration as a whole
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
