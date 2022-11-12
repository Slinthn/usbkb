/*
 * Description: Debug functions
 */


/*
 * Description: Enable all leds
 */
debug_enable_led:
  SER R16
  
  OUT DDRB, R16
  OUT PORTB, R16
  OUT DDRC, R16
  OUT PORTC, R16
  OUT DDRD, R16
  OUT PORTD, R16
  OUT DDRE, R16
  OUT PORTE, R16
  OUT DDRF, R16
  OUT PORTF, R16

  RET


/*
 * Description: Disable all leds
 */
debug_disable_led:
  CLR R16
  
  OUT DDRB, R16
  OUT PORTB, R16
  OUT DDRC, R16
  OUT PORTC, R16
  OUT DDRD, R16
  OUT PORTD, R16
  OUT DDRE, R16
  OUT PORTE, R16
  OUT DDRF, R16
  OUT PORTF, R16

  RET

