/*
 * Description: ATMEGA32U4 USB protocol
 */


/*
 * Description: Initialise USB protocol
 */
usb_init:  ; Attempt 3
  LDS R16, USBCON
  SBR R16, (1 << OTGPADE)
  STS USBCON, R16

  NOP
  NOP

  LDS R16, USBCON
  CBR R16, (1 << OTGPADE)
  STS USBCON, R16

  /* Power on USB pads regulator */
  LDS R16, UHWCON
  SBR R16, (1 << UVREGE)
  STS UHWCON, R16

  LDI R16, (1 << PDIV2)
  STS PLLFRQ, R16

  /* Enable PLL */
  LDS R16, PLLCSR
  SBR R16, (1 << PLLE)
  STS PLLCSR, R16

  /* Wait for PLOCK */
usb_init.plocka:
  LDS R16, PLLCSR
  SBRS R16, PLOCK
  RJMP usb_init.plocka

  /* Enable USB */
  LDI R16, (1 << VBUSTE)
  STS USBCON, R16

















  SEI

  /* Power on USB pads regulator */
  LDI R16, (1 << UVREGE)
  STS UHWCON, R16

  /* Configure PLL interface */
  LDI R16, 0  ;(1 << PINDIV)
  STS PLLCSR, PINDIV
  
  LDI R16, (1 << PINMUX) | (0b0100 << PDIV0)
  STS PLLFRQ, R16

  /* Enable PLL */
  LDS R16, PLLCSR
  SBR R16, (1 << PLLE)
  STS PLLCSR, R16

  /* Wait for PLOCK */
usb_init.plock:
  LDS R16, PLLCSR
  SBRS R16, PLOCK
  RJMP usb_init.plock

  /* Enable USB */
  LDI R16, (1 << VBUSTE)
  STS USBCON, R16

  /* Configure USB interface */
  ; TODO idk /* Note: Since we are working in full-speed mode, no changes must be made */
  LDS R16, UDCON
  SBR R16, (1 << LSM)
  STS UDCON, R16

  /* Set up endpoint 0 (control) */
  LDI R16, 0
  STS UENUM, R16  /* Select endpoint 0 */

  LDI R16, (1 << EPEN)
  STS UECONX, R16  /* Enable endpoint */

  CLR R16
  STS UECFG0X, R16  /* Set as control endpoint */

  LDI R16, (0b001 << EPSIZE) | (1 << ALLOC)
  STS UECFG1X, R16  /* Set size of endpoint and allocate */

  CLR R16
  STS UEINTX, R16  /* Clear interrupts */
  
  /* Wait for connection */
usb_init.connect:
  LDS R16, USBSTA
  SBRS R16, VBUS
  RJMP usb_init.connect

  /* USB connected, so attach USB */
  LDS R16, UDCON
  CBR R16, (1 << DETACH)
  STS UDCON, R16





;usb_init:
  RCALL debug_disable_led  /* TODO temporary */

  /* Enable USB pad regulator */
  LDI R16, (0x01 << UVREGE)
  STS UHWCON, R16

  /* Freeze USB */
  LDS R16, USBCON

  SBR R16, (1 << USBE) | (1 << FRZCLK)
  STS USBCON, R16

  /* Enable PLL */
  LDI R16, (0x01 << PLLE)
  STS PLLCSR, R16

  /* Wait for PLL to enable */
usb_init.loop11:
  LDS R16, PLLCSR
  SBRS R16, PLOCK
  RJMP usb_init.loop11  /* Loop if not enabled */

  /* Enable USB and VBUS pad */
  LDS R16, USBCON

  SBR R16, (1 << USBE) | (1 << OTGPADE)
  STS USBCON, R16

  ;/* Enable clock inputs */
  ;CBR R16, FRZCLK
  ;STS USBCON, R16

  /* Attach USB */
  LDS R16, UDCON

  CBR R16, (1 << DETACH)
  STS UDCON, R16

  RCALL debug_enable_led
  RET

  /* Enable low-speed mode */
  LDS R16, UDCON

  SBR R16, LSM
  STS UDCON, R16

  /* Enable VBUS interrupts */
  LDS R16, USBCON

  SBR R16, VBUSTE
  STS USBCON, R16

  /* Check for VBUS interrupt */
usb_init.loop01:  /* Loop to wait for interrupt */
  LDS R16, USBINT

  SBRS R16, VBUSTI
  RJMP usb_init.loop01

  /* VBUS interrupt detected; Clear VBUSTI and check if USB connected */
  CBR R16, USBINT
  STS USBINT, R16

  LDS R16, USBSTA
  SBRS R16, VBUS
  RJMP usb_init.return  /* If USB is not connected, return */


  /* USB setup complete */


  RCALL debug_enable_led
usb_init.return:
  RJMP usb_init
