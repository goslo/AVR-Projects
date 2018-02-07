/*
 * Knight_Rider.c
 *frecuency number needed by delay function
 * Created: 2016-05-01 6:53:09 AM
 * Author : jorge
 */ 


#define F_CPU 4000000    // AVR clock frequency in Hz, used by util/delay.h
#include <avr/io.h>
#include <util/delay.h>

// Number of frames in the animation
#define FRAMES 13

// The animation sequence array.
// All the values are in binary for easy
// reading (1 = LED on / 0 = LED off)
// The rightmost bit is PB0 and the leftmost
// bit after '0b' is PB4.
// -> 0b[4][3][2][1][0]
char animation[FRAMES] =
{
	0b00000001,
	0b00000010,
	0b00000100,
	0b00001000,
	0b00010000,
	0b00100000,
	0b01000000,
	0b10000000,
	0b01000000,
	0b00100000,
	0b00010000,
	0b00001000,
	0b00000010

};


int main(void)
{
	DDRD = 0xFF; // PD0-PD7 output
	PORTD = 0x00; // Set all pins low
	
	int i;
	
	while(1)
	{
		// Loop through all the frames in the animation
		for(i=0 ; i<FRAMES ; i++)
		{
			// Write the value from the array to the port
			PORTD = animation[i];
			
			// Wait 30 ms before going to the next frame
			_delay_ms(30);
		}
	}
	
	return 0;
}



