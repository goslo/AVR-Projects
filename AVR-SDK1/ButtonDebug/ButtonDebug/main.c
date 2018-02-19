/*
 * ButtonDebug
 *
 * Created: 2018-02-12 7:28:25 AM
 * Author : jorge
 */ 

#define F_CPU 4000000UL /* 4 MHz Internal Oscillator */
#include <avr/io.h>
#include <util/delay.h>

 void ProcessPressedButton();			//function for pressed button
 void ProcessReleasedButton();		//function for released button
 
int Pressed = 0;
int i;
unsigned char keys;
int LEDNumber = 0;
int Pressed_Confidence_Level = 0;	//Measure button press confidence
int Released_Confidence_Level = 0;	//Measure button release confidence
 
int main(void)
{
    //Initialization area. Setting up ports and data direction
	DDRC &= ~(1<<0);	//set Bit 0 for input
	PORTC |= (1<<0);	//activate Bit 0 internal pull up resistor
	DDRD = 0xff;	//set for all outputs
	PORTD = 0x00;	//set output low -> turn all LEDs off
	
		
    while (1) 
    {
		if ( ~PINC & (1<<0))			//read PINC Bit 0 to see if Switch 1 is pressed 
		{
			ProcessPressedButton();		//Process button click
		}
		else
		{
			ProcessReleasedButton();	//Process button release
			
		}
     }
}

void ProcessPressedButton()
{
	Pressed_Confidence_Level ++;
	if (Pressed_Confidence_Level > 500);
	Released_Confidence_Level = 0;			// Reset released button confidence since there is a button press
	{
		if (Pressed == 0)
		{
		Pressed = 1;
		PORTD |= 1 << LEDNumber;			//turn on Bits for LED's in ascending order
		LEDNumber ++;
		if (LEDNumber > 7)					//have all LED's been switched on?
			{	
			for (i=0;i < 10;i++)			//loop to flash all LED's 10 times
				{
				PORTD = 0x00;				//start of flash all LED's routine
				_delay_ms(10);
				PORTD = 0xff;
				_delay_ms(10);		
				}
				LEDNumber = 0;				//reset LED counter
				PORTD = 0x00;				//turn off all LED's
			}
		}
	}
		Pressed_Confidence_Level = 0;	
}

void ProcessReleasedButton()
{
	Released_Confidence_Level ++;
	if (Released_Confidence_Level > 500)
	{
		Pressed = 0;
		Released_Confidence_Level = 0;
	}
}