/*
 * Button_Library.c
 *
 * Created: 2018-02-07 7:19:16 PM
 * Author : jorge
 * Define numberOfButtons to be used first
 * Fill out the variables in the main loop.
 * buttonNumber=Switch number
 * pinOButton=Port pin eg. PINC
 * portBit=bit of port button is on
 * confidenceLevel=value to gage good button press
 */ 

#define numberOfButtons 4
#include <avr/io.h>
#include "button.h"

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
		
		if (ButtonPressed(0,PINC,0,100)) PORTD ^= (1<<PIND0);	//toggle bit 0 with XOR, flips from 1 to 0
		
		if (ButtonPressed(1,PINC,1,100)) PORTD ^= (1<<PIND1);	//toggle bit 1 with XOR, flips from 1 to 0
		
		if (ButtonPressed(2,PINC,2,100)) PORTD ^= (1<<PIND2);	//toggle bit 2 with XOR, flips from 1 to 0
		
		if (ButtonPressed(3,PINC,3,100)) PORTD ^= (1<<PIND3);	//toggle bit 3 with XOR, flips from 1 to 0
	}
}