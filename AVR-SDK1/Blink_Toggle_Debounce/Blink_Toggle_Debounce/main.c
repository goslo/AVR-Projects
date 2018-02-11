/*
 * Blink_Toggle_Debounce.c
 *
 * Created: 2018-02-10 7:26:07 PM
 * Author : jorge
 */ 

#include <avr/io.h>


int main(void)
{
    DDRD =0xff;		//set direction for PORTD to all outputs
	DDRC = 0xff;	//set direction for PORTC to all inputs
	PORTD = 0x01;	//set all LED's off except bit 0 which is on
	PORTC = 0xff;	//activate internal pull ups on inputs
	
	int Pressed = 0;
	int Pressed_Confidence_Level = 0;	//Measure button press confidence
	int Released_Confidence_Level = 0;	//Measure button release confidence
	
    while (1) 
    {
		if (bit_is_clear(PINC, 0))  //check if button 1 (PORTC bit 0) pushed
		{
		Pressed_Confidence_Level ++; // Increase pressed confidence
		Released_Confidence_Level = 0; // Reset released button confidence since there is a button press
		if (Pressed_Confidence_Level >500) //Indicator of a good button press
			{
				if (Pressed == 0)
				{
					PORTD ^= 1 << PIND0;
					PORTD ^= 1 << PIND1;
					Pressed = 1;
				}
			Pressed_Confidence_Level = 0;	//Zero it so a new pressed condition can be evaluated
			}
		}
		else
		{
			Released_Confidence_Level ++; // This works just like the pressed
			if (Released_Confidence_Level >500) //Indicator of a button released
				{
				Pressed = 0;	//Reset Pressed status
				}			
		}		 	
    }
}

