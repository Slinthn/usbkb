/*
 * USB general interrupt
 */
void __vector_10(void) {
  DDRC = 0xFF;
  PORTC = 0xFF;
}

typedef struct usb_setup_packet_t {
  u8 request_type;
  u8 request;
  u16 value;
  u16 index;
  u16 length;
} usb_setup_packet;

/*
 * USB endpoint interrupt
 */
void __vector_11(void) {
  // Currently, only the RXSTPI endpoint is enabled,
  // so we will assume that that is the only reason
  // for this interrupt to be triggered (setup packets).

  usb_setup_packet packet;
  packet.request_type = UEDATX;
  packet.request = UEDATX;
  packet.value = UEDATX;
  packet.value |= UEDATX << 8;
  packet.index = UEDATX;
  packet.index |= UEDATX << 8;
  packet.length = UEDATX;
  packet.length |= UEDATX << 8;

  UEINTX |= (1 << RXSTPI);
}

