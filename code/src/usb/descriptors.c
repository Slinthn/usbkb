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
    + sizeof(usb_interface_descriptor) + sizeof(usb_hid_descriptor) + sizeof(usb_endpoint_descriptor), 
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
  .hid_descriptor.descriptor_length = sizeof(bytes),  // TODO check

  .endpoint_descriptor.length = sizeof(usb_endpoint_descriptor),
  .endpoint_descriptor.descriptor_type = 0x5,  // TODO
  .endpoint_descriptor.endpoint_address = (1 << 7) | 3,  // TODO keyboad endpoint num
  .endpoint_descriptor.attributes = 0b11,
  .endpoint_descriptor.max_packet_size = 0x8,
  .endpoint_descriptor.interval = 0x1
};
