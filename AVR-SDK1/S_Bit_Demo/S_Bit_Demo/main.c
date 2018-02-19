/*
 * S_Bit_Demo.c
 *
 * Created: 2018-02-18 3:52:10 PM
 * Author : jorge
 */ 
#include <avr/io.h>
#include "sbit.h"


#define KEY0            SBIT( PINC, 0 )
#define KEY0_PULLUP     SBIT( PORTC, 0 )

#define LED0            SBIT( PORTD, 0 )
//#define LED0_DDR        SBIT( DDRD, 1 )


int main( void )
{
		DDRD  = 0xff;                  // use all pins on PortD for output
		DDRC  = 0xff;                  // use all pins on port C for input
	    
		PORTC = 0xff;                  // activate internal pull-up
		PORTD = 0x00;                  // set output low -> turn all LEDs off

		//LED0_DDR = 1;         // output
		//KEY0_PULLUP = 1;      // pull up on

	for(;;){

			if( KEY0 == 0 )     // if key pressed (low)
			LED0 = 1;         // LED on (high)
			else
			LED0 = 0;         // LED off (low)
			}
}

