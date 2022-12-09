typedef struct usb_setup_packet {
  u8 request_type;
  u8 request;
  u16 value;
  u16 index;
  u16 length;
} usb_setup_packet;

typedef struct usb_device_descriptor {
  u8 length;
  u8 descriptor_type;
  u16 usb;
  u8 device_class;
  u8 device_subclass;
  u8 device_protocol;
  u8 max_packet_size;
  u16 id_vendor;
  u16 id_product;
  u16 device;
  u8 manufacturer;
  u8 product;
  u8 serial_number;
  u8 num_configurations;
} usb_device_descriptor;

usb_device_descriptor device_descriptor = {
  .length = sizeof(usb_device_descriptor),
  .descriptor_type = 0x1,
  .device_class = 0x0,
  .usb = 0x200,
  .device_subclass = 0x0,
  .device_protocol = 0x0,
  .max_packet_size = 32,
  .id_vendor = 0x03eb,  // TODO TEMp
  .id_product = 0x2ff4,  // TODO temp
  .device = 0x1,
  .manufacturer = 0,
  .product = 0,
  .serial_number = 0,
  .num_configurations = 1
};


/*
 * USB general interrupt
 */
void __attribute__((signal)) __vector_10(void) {
  if (UDINT & (1 << EORSTI)) {
    usb_endpoint0();
    // TODO ??
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
    
    switch (packet.value) {
    case 0x100: {
      while (!(UEINTX & (1 << TXINI)));

      u8 *ptr = (u8 *)&device_descriptor;
      for (u8 i = 0; i < sizeof(usb_device_descriptor); i++) {
        UEDATX = *ptr++;
      }

      UEINTX &= ~(1 << TXINI);
    } break;

    case 0x200: {
    } break;
    }
  } break;

  case SET_CONFIGURATION: {
  DDRC = 0xFF;
  PORTC = 0xFF;
  } break;

  case USB_SET_ADDRESS: {
    UEINTX &= ~(1 << TXINI);
    while (!(UEINTX & (1 << TXINI)));

    UDADDR = (1 << ADDEN) | packet.value;
  } break;

  default: {

    DDRC = 0xFF;
    PORTC = 0xFF;
  } break;
  }
}

