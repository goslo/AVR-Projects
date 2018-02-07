/*
 * Blink_all_Leds.c
 *
 * Created: 2018-01-14 2:45:25 PM
 * Author : jorge
 */ 

#define F_CPU 4000000    // AVR clock frequency in Hz, used by util/delay.h
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
 DDRD = 0xff;           // Configure PORTD as output


 while(1)

 {

	 PORTD = 0xff;        // Turn ON all the Leds connected to PORTD

	 _delay_ms(100);      // Wait for some time

	 PORTD = 0x00;        // Turn OFF all the Leds connected to PORTD

	 _delay_ms(100);      // Wait for some time

 }

 return 0;
    while (1) 
    {
    }
}

