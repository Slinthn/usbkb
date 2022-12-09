usb_device_descriptor device_descriptor = {
  .length = sizeof(usb_device_descriptor),
  .descriptor_type = 0x1,  // TODO
  .device_class = 0x0,
  .usb = 0x200,
  .device_subclass = 0x0,
  .device_protocol = 0x0,
  .max_packet_size = 32,
  .id_vendor = 0,  // TODO TEMp
  .id_product = 0x0,  // TODO temp
  .device = 0x1,
  .manufacturer = 0,
  .product = 0,
  .serial_number = 0,
  .num_configurations = 1
};

usb_complete_descriptor complete_descriptor = {
  .configuration_descriptor.length = sizeof(usb_configuration_descriptor),
  .configuration_descriptor.descriptor_type = 0x2,  // TODO
  .configuration_descriptor.total_length = sizeof(usb_configuration_descriptor)
    + sizeof(usb_interface_descriptor) + sizeof(usb_hid_descriptor), 
  .configuration_descriptor.num_interfaces = 1,
  .configuration_descriptor.configuration_value = 1,
  .configuration_descriptor.configuration = 0,
  .configuration_descriptor.attributes = (1 << 7) | (1 << 6),  // TODO
  .configuration_descriptor.max_power = 50,

  .interface_descriptor.length = sizeof(usb_interface_descriptor),
  .interface_descriptor.descriptor_type = 0x4, // TODO
  .interface_descriptor.interface_number = 0,
  .interface_descriptor.alternate_setting = 0,
  .interface_descriptor.num_endpoints = 1,
  .interface_descriptor.interface_class = 0x3,  // TODO HID
  .interface_descriptor.interface_subclass = 0x1,  // TODO
  .interface_descriptor.interface_protocol = 0x1,
  .interface_descriptor.interface = 0,

  .hid_descriptor.length = sizeof(usb_hid_descriptor),
  .hid_descriptor.descriptor_type = 0x21,  // TODO
  .hid_descriptor.hid = 0x101,  // TODO check
  .hid_descriptor.country_code = 0,
  .hid_descriptor.num_descriptors = 0x1,
  .hid_descriptor.report_descriptor_type = 0x22,  // TODO check
  .hid_descriptor.descriptor_length = 0x3F,  // TODO check

  .endpoint_descriptor.length = sizeof(usb_endpoint_descriptor),
  .endpoint_descriptor.descriptor_type = 0x5,  // TODO
  .endpoint_descriptor.endpoint_address = (1 << 7) | 1,
  .endpoint_descriptor.attributes = 0b11,
  .endpoint_descriptor.max_packet_size = 0x8,
  .endpoint_descriptor.interval = 0x1
};

u8 bytes[] = {
  0x05, 0x01,
  0x09, 0x06,
  0xA1, 0x01,
  0x05, 0x07,
  0x19, 0xE0,
  0x29, 0xE7,
  0x15, 0x00,
  0x25, 0x01,
  0x75, 0x01,
  0x95, 0x08,
  0x81, 0x02,
  0x95, 0x01,
  0x75, 0x08,
  0x81, 0x01,
  0x95, 0x05,
  0x75, 0x01,
  0x05, 0x08,
  0x19, 0x01,
  0x29, 0x05,
  0x91, 0x02,
  0x95, 0x01,
  0x75, 0x03,
  0x91, 0x01,
  0x95, 0x06,
  0x75, 0x08,
  0x15, 0x00,
  0x25, 0x65,
  0x05, 0x07,
  0x19, 0x00,
  0x29, 0x65,
  0x81, 0x00,
  0xC0
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
    u8 *data;
    u8 data_size;

    switch (packet.value) {
    case 0x100: {
      data = (u8 *)&device_descriptor;
      data_size = sizeof(usb_device_descriptor);
    } break;

    case 0x200: {
      data = (u8 *)&complete_descriptor;
      data_size = sizeof(complete_descriptor);
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
      return;
    } break;
    }
    
    while (!(UEINTX & (1 << TXINI)));

    for (u8 i = 0; i < data_size; i++) {
      DDRC = 0xFF;
      PORTC = 0xFF;
      UEDATX = *data++;
    }

    UEINTX &= ~(1 << TXINI);
  } break;

  case USB_SET_CONFIGURATION: {
  } break;

  case USB_SET_ADDRESS: {
    UEINTX &= ~(1 << TXINI);
    while (!(UEINTX & (1 << TXINI)));

    UDADDR = (1 << ADDEN) | packet.value;
  } break;

  default: {
  } break;
  }
}

