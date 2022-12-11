u8 keyboard_report_descriptor[] = {
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
  .descriptor_type = USB_DESCRIPTOR_TYPE_DEVICE,
  .device_class = 0x0,
  .usb = USB_VERSION,
  .device_subclass = 0x0,
  .device_protocol = 0x0,
  .max_packet_size = 32,
  .id_vendor = 0,
  .id_product = 0,
  .device = 0x1,
  .manufacturer = 0,
  .product = 0,
  .serial_number = 0,
  .num_configurations = 1
};


usb_complete_descriptor complete_descriptor = {
  .configuration_descriptor.length = sizeof(usb_configuration_descriptor),
  .configuration_descriptor.descriptor_type = USB_DESCRIPTOR_TYPE_CONFIGURATION,
  .configuration_descriptor.total_length = sizeof(usb_configuration_descriptor)
    + sizeof(usb_interface_descriptor) + sizeof(usb_hid_descriptor) + sizeof(usb_endpoint_descriptor), 
  .configuration_descriptor.num_interfaces = 1,
  .configuration_descriptor.configuration_value = 1,
  .configuration_descriptor.configuration = 0,
  .configuration_descriptor.attributes = USB_CONFIGURATION_BUS_POWERED,
  .configuration_descriptor.max_power = 1,  // 1 * 2mA

  .interface_descriptor.length = sizeof(usb_interface_descriptor),
  .interface_descriptor.descriptor_type = USB_DESCRIPTOR_TYPE_INTERFACE,
  .interface_descriptor.interface_number = 0,
  .interface_descriptor.alternate_setting = 0,
  .interface_descriptor.num_endpoints = 1,
  .interface_descriptor.interface_class = USB_HID_CLASSCODE,
  .interface_descriptor.interface_subclass = USB_BOOT_INTERFACE_SUBCLASS,
  .interface_descriptor.interface_protocol = USB_PROTOCOL_KEYBOARD,
  .interface_descriptor.interface = 0,

  .hid_descriptor.length = sizeof(usb_hid_descriptor),
  .hid_descriptor.descriptor_type = USB_DESCRIPTOR_TYPE_HID,
  .hid_descriptor.hid = USB_VERSION_HID,
  .hid_descriptor.country_code = USB_COUNTRYCODE_NONE,
  .hid_descriptor.num_descriptors = 0x1,
  .hid_descriptor.report_descriptor_type = USB_CLASS_DESCRIPTOR_TYPE_REPORT,
  .hid_descriptor.descriptor_length = sizeof(keyboard_report_descriptor),

  .endpoint_descriptor.length = sizeof(usb_endpoint_descriptor),
  .endpoint_descriptor.descriptor_type = USB_DESCRIPTOR_TYPE_ENDPOINT,
  .endpoint_descriptor.endpoint_address = USB_CONTROL_ENDPOINT_IN | USB_KEYBOARD_ENDPOINT,
  .endpoint_descriptor.attributes = 0b11,
  .endpoint_descriptor.max_packet_size = 0x8,
  .endpoint_descriptor.interval = 0x1
};
