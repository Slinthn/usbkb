#define PINB STS_BYTE(0x23)
#define DDRB STS_BYTE(0x24)
#define PORTB STS_BYTE(0x25)

#define PINC STS_BYTE(0x26)
#define DDRC STS_BYTE(0x27)
#define PORTC STS_BYTE(0x28)


#define PIND STS_BYTE(0x29)
#define DDRD STS_BYTE(0x2A)
#define PORTD STS_BYTE(0x2B)

#define PINE STS_BYTE(0x2C)
#define DDRE STS_BYTE(0x2D)
#define PORTE STS_BYTE(0x2E)

#define PINF STS_BYTE(0x2F)
#define DDRF STS_BYTE(0x30)
#define PORTF STS_BYTE(0x31)

#define EICRA STS_BYTE(0x69)

#define PCICR STS_BYTE(0x68)

#define PCMSK0 STS_BYTE(0x6B)

#define EIMSK STS_BYTE(0x3D)

// DEFINEs for USB registers
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
#define RWAL 5
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
