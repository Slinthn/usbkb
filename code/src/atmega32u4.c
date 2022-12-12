/*
 * ATMEGA32U4 constants and defines
 */

#define STS(x) (*((u8 *)(u16)(x)))  // Used as STS instruction

#define PINB 0x23
#define DDRB 0x24
#define PORTB 0x25

#define PINC 0x26
#define DDRC 0x27
#define PORTC 0x28


#define PIND 0x29
#define DDRD 0x2A
#define PORTD 0x2B

#define PINE 0x2C
#define DDRE 0x2D
#define PORTE 0x2E

#define PINF 0x2F
#define DDRF 0x30
#define PORTF 0x31

#define EICRA 0x69

#define PCICR 0x68

#define PCMSK0 0x6B

#define EIMSK 0x3D

// DEFINEs for USB registers
#define USBCON 0xD8
#define FRZCLK 5
#define OTGPADE 4

#define PLLCSR 0x49
#define USBE 7
#define PINDIV 4
#define PLLE 1
#define PLOCK 0

#define UDCON 0xE0
#define LSM 2
#define DETACH 0

#define UHWCON 0xD7
#define UVREGE 0

#define UDIEN 0xE2
#define EORSTE 3
#define SOFE 2

#define UEINTX 0xE8
#define RWAL 5
#define RXSTPI 3
#define RXOUTI 2
#define TXINI 0

#define USB_UNINITIALISED 0
#define USB_ACIVE 1

#define UECONX 0xEB
#define STALLRQ 5
#define EPEN 0

#define UENUM 0xE9
#define EPNUM 0

#define UECFG0X 0xEC
#define EPTYPE 6
#define EPDIR 0

#define UECFG1X 0xED
#define EPSIZE 4
#define EPBK 2
#define ALLOC 1

#define UESTA0X 0xEE
#define CFGOK 7

#define UERST 0xEA
#define EPRST 0

#define UEIENX 0xF0
#define RXSTPE 3

#define UEDATX 0xF1

#define UDINT 0xE1
#define EORSTI 3
#define SOFI 2

#define UDADDR 0xE3
#define ADDEN 7
