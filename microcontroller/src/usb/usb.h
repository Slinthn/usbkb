/**
 * @brief USB constants and packets
 * 
 */

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

#define USB_HID_MAX_KEYS 6

#define USB_TYPE_CLASS (0b1 << 5)
#define USB_RECIPIENT_INTERFACE (0b1 << 0)

#define USB_TRANSFER_DEVICE_TO_HOST (1 << 7)

// USB SETUP packet structures
typedef struct usb_setup_packet {
  uint8_t request_type;
  uint8_t request;
  uint16_t value;
  uint16_t index;
  uint16_t length;
} usb_setup_packet;

typedef struct usb_device_descriptor {
  uint8_t length;
  uint8_t descriptor_type;
  uint16_t usb;
  uint8_t device_class;
  uint8_t device_subclass;
  uint8_t device_protocol;
  uint8_t max_packet_size;
  uint16_t id_vendor;
  uint16_t id_product;
  uint16_t device;
  uint8_t manufacturer;
  uint8_t product;
  uint8_t serial_number;
  uint8_t num_configurations;
} usb_device_descriptor;

typedef struct usb_configuration_descriptor {
  uint8_t length;
  uint8_t descriptor_type;
  uint16_t total_length;
  uint8_t num_interfaces;
  uint8_t configuration_value;
  uint8_t configuration;
  uint8_t attributes;
  uint8_t max_power;
} usb_configuration_descriptor;

typedef struct usb_interface_descriptor {
  uint8_t length;
  uint8_t descriptor_type;
  uint8_t interface_number;
  uint8_t alternate_setting;
  uint8_t num_endpoints;
  uint8_t interface_class;
  uint8_t interface_subclass;
  uint8_t interface_protocol;
  uint8_t interface;
} usb_interface_descriptor;

typedef struct usb_endpoint_descriptor {
  uint8_t length;
  uint8_t descriptor_type;
  uint8_t endpoint_address;
  uint8_t attributes;
  uint16_t max_packet_size;
  uint8_t interval;
} usb_endpoint_descriptor;

typedef struct usb_hid_descriptor {
  uint8_t length;
  uint8_t descriptor_type;
  uint16_t hid;
  uint8_t country_code;
  uint8_t num_descriptors;
  uint8_t report_descriptor_type;
  uint16_t descriptor_length;
} usb_hid_descriptor;

typedef struct usb_complete_descriptor {
  usb_configuration_descriptor configuration_descriptor;
  usb_interface_descriptor interface_descriptor;
  usb_hid_descriptor hid_descriptor;
  usb_endpoint_descriptor endpoint_descriptor;
} usb_complete_descriptor;
