// Defines for USB registers (located in SRAM)
#define USBCON STS_BYTE(0xD8)
#define FRZCLK 5
#define OTGPADE 4

#define PLLCSR STS_BYTE(0x49)
#define USBE 7
#define PINDIV 4
#define PLLE 1
#define PLOCK 0

#define UDCON STS_BYTE(0xE0)
#define LSM 2
#define DETACH 0

#define UHWCON STS_BYTE(0xD7)
#define UVREGE 0

#define UDIEN STS_BYTE(0xE2)
#define EORSTE 3
#define SOFE 2

#define UEINTX STS_BYTE(0xE8)
#define RXSTPI 3
#define RXOUTI 2
#define TXINI 0

#define USB_UNINITIALISED 0
#define USB_ACIVE 1

#define UECONX STS_BYTE(0xEB)
#define STALLRQ 5
#define EPEN 0

#define UENUM STS_BYTE(0xE9)
#define EPNUM 0

#define UECFG0X STS_BYTE(0xEC)
#define EPTYPE 6
#define EPDIR 0

#define UECFG1X STS_BYTE(0xED)
#define EPSIZE 4
#define EPBK 2
#define ALLOC 1

#define UESTA0X STS_BYTE(0xEE)
#define CFGOK 7

#define UERST STS_BYTE(0xEA)
#define EPRST 0

#define UEIENX STS_BYTE(0xF0)
#define RXSTPE 3

#define UEDATX STS_BYTE(0xF1)

#define UDINT STS_BYTE(0xE1)
#define EORSTI 3
#define SOFI 2

#define UDADDR STS_BYTE(0xE3)
#define ADDEN 7

// USB SETUP packet types
#define USB_SET_ADDRESS 0x5
#define USB_GET_DESCRIPTOR 0x6
#define USB_SET_CONFIGURATION 0x9
#define USB_GET_CONFIGURATION 0x8
#define USB_GET_STATUS 0

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
