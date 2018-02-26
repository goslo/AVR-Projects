/*
 * Button_Game.c
 *
 * Created: 2018-02-12 7:28:25 AM
 * Author : jorge
 */ 

#define F_CPU 4000000UL /* 4 MHz Internal Oscillator */
#include <avr/io.h>
#include <util/delay.h>

 void ProcessPressedButton(int ButtonPressed);	//function for pressed button
 void ProcessReleasedButton(int ButtonReleased);  //function for released button
 
 int Pressed_Confidence_Level [2];		//array for debounce 2 switches
 int Released_Confidence_Level [2];		//array for debounce 2 switches
 int Pressed [2];						//array for 2 switch presses
 int LEDNumber [2];						//array to count 2 LED lit levels
 
int main(void)
{
    //Initialization area. Setting up ports and data direction
	DDRB = 0xff;		//set PORTB for all outputs
	PORTB = 0x00;		//set output low -> turn all LEDs off
	DDRD = 0xff;		//set PORTD for for all outputs
	PORTD = 0x00;		//set output low -> turn all LEDs off
    DDRC  = 0xff;       // use all pins on port C for input
	PORTC = 0xff;		//turn on all pull up resistors
	//DDRC &= ~(1<<0);	//set Bit 0 for input
	//PORTC |= (1<<0);	//activate Bit 0 internal pull up resistor

		
    while (1) 
    {
		if ( ~PINC & (1<<0))		//read PINC Bit 0 to see if S0 is pressed 
		{
			ProcessPressedButton(0);	//Process button clicks for side 1	
		}
		else
		{
			ProcessReleasedButton(0);
		}
		if ( ~PINC & (1<<3))			//read PINC Bit 3 to see if S3 is pressed 
		{
			ProcessPressedButton(1);	//Process button clicks for side 2
		}
		else
		{
			ProcessReleasedButton(1);
		} 
     }
}

void ProcessPressedButton(int ButtonPressed)
{
	Pressed_Confidence_Level[ButtonPressed] ++;
	if (Pressed_Confidence_Level[ButtonPressed] > 500)
	{
	if (Pressed[ButtonPressed] == 0)
		{
			Pressed[ButtonPressed] = 1;		
			if (ButtonPressed == 0) PORTD |= 1 << LEDNumber[ButtonPressed];	//increment LED's
			if (ButtonPressed == 1) PORTB |= 1 << LEDNumber[ButtonPressed];	//increment LED's
			LEDNumber[ButtonPressed] ++;
			if (LEDNumber[ButtonPressed] >6)
				{	
				for (int i=0;i < 10;i++)
					{
						if (ButtonPressed == 0) PORTD = 0x00;
						if (ButtonPressed == 1) PORTB = 0x00;
						_delay_ms(10);
						if (ButtonPressed == 0) PORTD = 0xff;
						if (ButtonPressed == 1) PORTB = 0xff;
						_delay_ms(10);		
					}
				LEDNumber[0] = 0;
				LEDNumber[1] = 0;
				PORTD = 0x00;
				PORTB = 0x00;
				}
			}
		Pressed_Confidence_Level[ButtonPressed] = 0;	
	}
}

void ProcessReleasedButton(int ButtonReleased)
{
	Released_Confidence_Level[ButtonReleased] ++;
	if (Released_Confidence_Level[ButtonReleased] > 500)
	{
		Pressed[ButtonReleased] = 0;
		Released_Confidence_Level[0] = 0;
	}
}