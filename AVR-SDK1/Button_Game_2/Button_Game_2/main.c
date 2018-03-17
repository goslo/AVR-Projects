/*
 * Button_Game_2.c
 *
 * Created: 2018-02-07 7:19:16 PM
 * Author : jorge
 * The button game, using the button library
 * 2 sets of LEDS, PORTB + PORTB
 * This one use a function and a prototype
 * Define numberOfButtons to be used FIRST
 * Fill out the variables in the main loop.
 * -buttonNumber=Switch number
 * -pinOButton=Port pin eg. PINC
 * -portBit=bit of port button is on
 * -confidenceLevel=value to gage good button press
 */ 

#define numberOfButtons 2	//only using 2 button
#include <avr/io.h>
#include "button.h"
#define F_CPU 4000000UL		/* 4 MHz Internal Oscillator */
#include <util/delay.h>

void ProcessPressedButton(int ButtonID);		//prototype for function

int LEDNum[2];				//LED count

int main(void)
{
	DDRB = 0xff;		//set PORTB for all outputs
	PORTB = 0x00;		//set output low -> turn all LEDs off
	DDRD = 0xff;		//set PORTD for for all outputs
	PORTD = 0x00;		//set output low -> turn all LEDs off
	DDRC = 0x00;		//set direction to all inputs
	PORTC = 0xff;		//turn on all pull up resistors
	
	while(1)
	{
		if (ButtonPressed(0,PINC,0,100))			//check if button on PORTC Bit 0 is pressed
			{
				ProcessPressedButton(0);			//go process button press
			}
		if (ButtonPressed(1,PINC,3,100))			//check if button on PORTC Bit 3 is pressed
			{
				ProcessPressedButton(1);			//go process button press
			}		
	}
}
void ProcessPressedButton(int ButtonID)					//function for button press
{	
	if (ButtonID == 0) PORTD |= 1 << LEDNum[ButtonID];	//increment LED's
	if (ButtonID == 1) PORTB |= 1 << LEDNum[ButtonID];	//increment LED's
	LEDNum[ButtonID] ++;								//increment LED count[for both sets of LED's
	if (LEDNum[ButtonID] >6)							//check if at limit
	{
		for (int i=0;i < 10;i++)						//flash all LED's 10 times
		{
			if (ButtonID == 0) PORTD = 0x00;
			if (ButtonID == 1) PORTB = 0x00;
			_delay_ms(10);
			if (ButtonID == 0) PORTD = 0xff;
			if (ButtonID == 1) PORTB = 0xff;
			_delay_ms(10);
		}
		LEDNum[0] = 0;
		LEDNum[1] = 0;
		PORTD = 0x00;
		PORTB = 0x00;
	}	
}
