/*
 * Description: Main file of KBUSB with entrypoint
 */


.INCLUDE "atmega32u4.inc"
.INCLUDE "usb.s"
.INCLUDE "debug.s"


/*
 * Description: Entrypoint p of the program
 */
.GLOBAL main
main:

  SER R16
  STS 0x27, R16
  STS 0x28, R16

  RCALL usb_init

main.loop:
  RJMP main.loop
