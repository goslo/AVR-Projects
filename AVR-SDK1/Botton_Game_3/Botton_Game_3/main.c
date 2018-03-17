/*
 * Button_Game_3.c
 *
 * Created: 2018-02-07 7:19:16 PM
 * Author : jorge
 * The button game, using the button library
 * with buttons 1+2 erasing the LED's on the ports
 * Define numberOfButtons to be used FIRST
 * Fill out the variables in the main loop.
 * -buttonNumber=Switch number
 * -pinOButton=Port pin eg. PINC
 * -portBit=bit of port button is on
 * -confidenceLevel=value to gage good button press
 */ 

#define numberOfButtons 4	//using 4 button
#include <avr/io.h>
#include "button.h"
#define F_CPU 4000000UL		/* 4 MHz Internal Oscillator */
#include <util/delay.h>

void ProcessPressedButton(int ButtonID);		//prototype for function

int LEDNum[4];				//LED count

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
		if (ButtonPressed(1,PINC,1,100))			//check if button on PORTC Bit 1 is pressed
			{
				ProcessPressedButton(1);			//go process button press
			}
		if (ButtonPressed(2,PINC,2,100))			//check if button on PORTC Bit 2 is pressed
			{
				ProcessPressedButton(2);			//go process button press
			}
		if (ButtonPressed(3,PINC,3,100))			//check if button on PORTC Bit 3 is pressed
			{
				ProcessPressedButton(3);			//go process button press
			}			
	}
}
void ProcessPressedButton(int ButtonID)		//function for button press
{	
	if (ButtonID == 0) PORTD |= 1 << LEDNum[ButtonID];	//increment LED's
	if (ButtonID == 3) PORTB |= 1 << LEDNum[ButtonID];	//increment LED's
	if (ButtonID == 1)									//was it an erase button 1?
		{
			PORTD = 0x00; 
			LEDNum[0] = 0;			//yes, so turn off all LED's, reset LED count
		}
	if (ButtonID == 2)									//was it an erase button 2?
		{
			PORTB = 0X00; 
			LEDNum[3] = 0;			//yes, so turn off all LED's, reset LED count
		}
	LEDNum[ButtonID] ++;
	if (LEDNum[ButtonID] >6)
	{
		for (int i=0;i < 10;i++)			//start of flash all LED's function
		{
			if (ButtonID == 0) PORTD = 0x00;
			if (ButtonID == 3) PORTB = 0x00;
			_delay_ms(10);
			if (ButtonID == 0) PORTD = 0xff;
			if (ButtonID == 3) PORTB = 0xff;
			_delay_ms(10);
		}
		LEDNum[0] = 0;						//set LED count back to zero button 1
		LEDNum[3] = 0;						//set LED count back to zero button 3
		PORTD = 0x00;						//turn off all LED's PORTD
		PORTB = 0x00;						//turn off all LED's PORTB
	}
	
}

