// USB SETUP packet types
#define USB_SET_ADDRESS 0x5
#define USB_GET_DESCRIPTOR 0x6
#define USB_SET_CONFIGURATION 0x9
#define USB_GET_CONFIGURATION 0x8
#define USB_GET_STATUS 0

#define USB_ENDPOINT_GET_REPORT 0x1
#define USB_ENDPOINT_GET_IDLE 0x2
#define USB_ENDPOINT_GET_PROTOCOL 0x3

#define USB_ENDPOINT_SET_REPORT 0x9
#define USB_ENDPOINT_SET_IDLE 0xA
#define USB_ENDPOINT_SET_PROTOCOL 0xB

#define USB_DEVICE_DESCRIPTOR 0x100
#define USB_CONFIGURATION_DESCRIPTOR 0x200
#define USB_HID_DESCRIPTOR 0x2100
#define USB_KEYBOARD_REPORT_DESCRIPTOR 0x2200

#define USB_KEYBOARD_ENDPOINT 3

#define USB_VERSION 0x200  // Version 2.0

#define USB_DESCRIPTOR_TYPE_DEVICE 0x1
#define USB_DESCRIPTOR_TYPE_CONFIGURATION 0x2
#define USB_DESCRIPTOR_TYPE_INTERFACE 0x4
#define USB_DESCRIPTOR_TYPE_HID 0x21
#define USB_DESCRIPTOR_TYPE_ENDPOINT 0x5
#define USB_VERSION_HID 0x101  // Version 1.01
#define USB_HID_CLASSCODE 0x3
#define USB_BOOT_INTERFACE_SUBCLASS 0x1
#define USB_PROTOCOL_KEYBOARD 0x1
#define USB_CLASS_DESCRIPTOR_TYPE_REPORT 0x22

#define USB_CONFIGURATION_BUS_POWERED (1 << 7)
#define USB_CONFIGURATION_SELF_POWERED (1 << 6)

#define USB_COUNTRYCODE_NONE 0
#define USB_CONTROL_ENDPOINT_IN (1 << 7)

// USB SETUP packet structures
typedef struct usb_setup_packet {
  u8 request_type;
  u8 request;
  u16 value;
  u16 index;
  u16 length;
} usb_setup_packet;

#pragma pack(push, 1)
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
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct usb_configuration_descriptor {
  u8 length;
  u8 descriptor_type;
  u16 total_length;
  u8 num_interfaces;
  u8 configuration_value;
  u8 configuration;
  u8 attributes;
  u8 max_power;
} usb_configuration_descriptor;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct usb_interface_descriptor {
  u8 length;
  u8 descriptor_type;
  u8 interface_number;
  u8 alternate_setting;
  u8 num_endpoints;
  u8 interface_class;
  u8 interface_subclass;
  u8 interface_protocol;
  u8 interface;
} usb_interface_descriptor;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct usb_endpoint_descriptor {
  u8 length;
  u8 descriptor_type;
  u8 endpoint_address;
  u8 attributes;
  u16 max_packet_size;
  u8 interval;
} usb_endpoint_descriptor;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct usb_hid_descriptor {
  u8 length;
  u8 descriptor_type;
  u16 hid;
  u8 country_code;
  u8 num_descriptors;
  u8 report_descriptor_type;
  u16 descriptor_length;
} usb_hid_descriptor;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct usb_complete_descriptor {
  usb_configuration_descriptor configuration_descriptor;
  usb_interface_descriptor interface_descriptor;
  usb_hid_descriptor hid_descriptor;
  usb_endpoint_descriptor endpoint_descriptor;
} usb_complete_descriptor;
#pragma pack(pop)
