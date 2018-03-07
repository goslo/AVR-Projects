/*
 * Button_Library_2.c
 *
 * Created: 2018-02-07 7:19:16 PM
 * Author : jorge
 * One half of the button game, using the button library
 * Define numberOfButtons to be used FIRST
 * Fill out the variables in the main loop.
 * buttonNumber=Switch number
 * pinOButton=Port pin eg. PINC
 * portBit=bit of port button is on
 * confidenceLevel=value to gauge good button press
 */ 

#define numberOfButtons 1
#include <avr/io.h>
#include "button.h"
#define F_CPU 4000000UL /* 4 MHz Internal Oscillator */
#include <util/delay.h>

int LEDNum = 0;

int main(void)
{
	DDRD = 0xff;		//set PORTD for for all outputs
	PORTD = 0x00;		//set output low -> turn all LEDs off
	DDRC = 0x00;		//set direction to all inputs
	PORTC = 0xff;		//turn on all pull up resistors
	//All the other ways to set PORTC
	//PORTC = (1 << PINC0)|(1 << PINC1); //activate Bit 0 + 1 internal pull up resistor
	//DDRC &= ~(1<<0);	//set Bit 0 for input
	//PORTC |= (1<<0);	//activate Bit 0 internal pull up resistor
	//PORTC |= (1<<1);	//activate Bit 1 internal pull up resistor
	
	while(1)
	{
		//ButtonPressed(int buttonNumber, unsigned char pinOfButton, unsigned char portBit, int confidenceLevel)
		if (ButtonPressed(0,PINC,0,100))
		{
			PORTD |= (1<< LEDNum);
			LEDNum ++;
			if (LEDNum >7)
			{
				for (int i=0;i < 10;i++)
				{
					PORTD = 0x00;;
					_delay_ms(10);
					PORTD = 0xff;
					_delay_ms(10);
				}
				LEDNum = 0;
				PORTD = 0x00;
			}
		}
	}
}
