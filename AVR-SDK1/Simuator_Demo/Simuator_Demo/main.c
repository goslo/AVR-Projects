/*
 * Simuator_Demo.c
 *
 * Created: 2018-02-16 5:00:39 PM
 * Author : jorge
 */ 

#define F_CPU 4000000UL /* 4 MHz Internal Oscillator */
#include <avr/io.h>
#include <util/delay.h>

unsigned char LED_NUM;
int i;

int main(void)
{
	
	DDRD = 0xff;
	PORTD =0x00;
	LED_NUM = 0;

    while (1)
	{
	 PORTD |= 1 << LED_NUM;
	 LED_NUM ++;
	 	if (LED_NUM >7)
			{
				for (i=0;i < 10;i++)
				{
					PORTD = 0x00;
					//_delay_ms(10);
					PORTD = 0xff;
					//_delay_ms(10);
				}
				LED_NUM = 0;
				PORTD = 0x00;
			}
	}
}
