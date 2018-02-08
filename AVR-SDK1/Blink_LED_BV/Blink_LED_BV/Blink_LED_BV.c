#define F_CPU 4000000UL /* 4 MHz Internal Oscillator */
#include <avr/io.h>
#include <util/delay.h>

/* function for long delay */
void delay_ms(uint16_t ms) {
  while ( ms )
  {
    _delay_ms(1);
    ms--;
  }
}

int main (void)
{
  /* POPRTD is digital output */
      DDRD  = 0xff;                  // use all pins on PortD for output
	  PORTD = 0x00;                  // set output low -> turn all LEDs off
//	DDRD = _BV (0);					//This was in original code using 1 LED

  /* loop forever */
  while (1)
  {
    /* clear PD0 on PORTD (digital high) and delay for 1 Second */
    PORTD &= ~_BV(0);
    delay_ms(1000);

    /* set PD0 on PORTD (digital low) and delay for 1 Second */
    PORTD |= _BV(0);
    delay_ms(1000);
  }
}