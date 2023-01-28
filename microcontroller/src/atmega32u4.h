/**
 * @brief ATMEGA32U4 constants and assembly
 */

#define STS(x) (*((uint8_t *)(uint16_t)(x)))

#define CLI asm("CLI")

#define SEI asm("SEI")

#define NOP asm("NOP")

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

#define CLKPR 0x61

#define TCCR0B 0x45
#define CS00 0

#define TIMSK0 0x6E
#define OCIE0A 1

#define CLKPR 0x61
#define CLKPCE 7
#define CLKPS0 0

#define SPCR 0x4C
#define SPIE 7
#define SPE 6
#define MSTR 4

#define SPSR 0x4D
#define SPIF 7
#define SPI2X 0

#define SPDR 0x4E

#define SREG 0x5F
#define I 7

#define TCCR0A 0x44
#define COM0A1 7
#define COM0A0 6
#define WGM01 1
#define WGM00 0

#define TCCR0B 0x45
#define WGM02 3
#define CS02 2
#define CS01 1
#define CS00 0

#define OCR0A 0x47

#define TCCR1A 0x80
#define COM1A1 7
#define COM1A0 6
#define WGM11 1
#define WGM10 0

#define TCCR1B 0x81
#define CS12 2
#define CS11 1
#define CS10 0

#define OCR1AH 0x89
#define OCR1AL 0x88

#define TCNT1H 0x85
#define TCNT1L 0x84
