/*
 * Blink_Led_Fast.c
 *
 * Created: 2018-02-07 8:28:57 PM
 * Author : jorge
 */ 

#define F_CPU 4000000UL /* 4 MHz Internal Oscillator */
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
    DDRD = 0xff;					//set direction for output
	
    while (1) 
    {
		PORTD ^= 1 << PIND0;		//XOR(^) to toggle PORT D bit0 0
		_delay_ms(10);				//delay 10 ms
    }
}

