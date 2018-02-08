/*
 * Blink_Led.c
 *
 * Created: 2018-01-12 2:33:20 PM
 * Author : jorge
 */ 

#define F_CPU 4000000    // AVR clock frequency in Hz, used by util/delay.h
#include <avr/io.h>
#include <util/delay.h>

int main() {
	DDRD |= 0xff;        // set LED pin PD1 to output
	PORTD = 0x00;          // set output low -> turn all LEDs off
	while (1) {
		PORTD = PORTD | 0x01;   // drive PD1 high
		_delay_ms(250);    // delay 250 ms
		PORTD  = PORTD & 0xfe;  // drive PD1 low
		_delay_ms(250);    // delay 250 ms
	}
}