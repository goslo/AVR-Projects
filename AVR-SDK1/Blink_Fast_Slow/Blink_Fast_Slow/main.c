/*
 * Blink_Fast_Slow.c
 *
 * Created: 2018-02-10 6:07:00 AM
 * Author : jorge
 */ 

#define F_CPU 4000000UL /* 4 MHz Internal Oscillator */
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
    DDRD = 0xff;		//use all pins on PORTD for outputs
	DDRC = 0xff;		//use all pins on PORTC for inputs
	PORTD = 0x00;		//set output low --> all LED's off
	PORTC = 0xff;		//activate internal pull ups on inputs
	
    while (1) 
    {
		PORTD ^= 1 <<PIND0;		//flip PORTD bit 0 
		if (bit_is_clear(PINC, 0))	//check if button 1 (PORTC bit 0) pushed
		{
			_delay_ms(10);	//button pushed fast blink
		}
		else
		{
			_delay_ms(100); //button not pushed slow blink
		}
	}
}
