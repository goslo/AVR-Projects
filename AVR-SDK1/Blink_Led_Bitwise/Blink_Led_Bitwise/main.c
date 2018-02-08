/*
 * Blink_Led_Bitwise.c
 *
 * Created: 2018-02-07 7:19:16 PM
 * Author : jorge
 */ 

#define F_CPU 4000000UL /* 4 MHz Internal Oscillator */
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
	DDRD = 0xFF;
	
	while(1) {
		PORTD ^= (1 << 7);	//toggle bit 7
		_delay_ms(250);
	}
}





