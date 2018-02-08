/******************************************************************************
 Title:    Turn on LED when switch is pressed
 Author:   Peter Fleury <pfleury@gmx.ch> http://jump.to/fleury
 Date:     December 2002
 Software: AVR-GCC 3.3 
 Hardware: AT90S8515 at 4 Mhz, STK200 compatible starter kit
           
 Description:
 This example demonstrates basic port input/output technic.
 If one of the switches on port C is pressed, the corresponding LED on port D is 
 turned on.
  
*******************************************************************************/
#include <inttypes.h>
#include <avr/io.h>

int main(void)
{
    uint8_t   led; 
    uint8_t   keys;
    

    DDRD  = 0xff;                  // use all pins on PortD for output 
    DDRC  = 0xff;                  // use all pins on port C for input
    
    PORTC = 0xff;                  // activate internal pull-up
    PORTD = 0x00;                  // set output low -> turn all LEDs off
    
    for (;;) {                     // loop forever   
        keys = ~PINC;              // read input port with switches (active-low)
			        
        if ( keys & 1 )				//back to original code
            led = 1;
        else if ( keys & 2 )       // priority encoder: if multiple switches are pressed,
            led = 2;               // only the lowest switch is recognized
        else if ( keys & 4 )
            led = 4;
       else if ( keys & 8 )
            led = 8;
//       else if ( keys & 0x10 )	//rem out code for use with 4 buttons
//           led = 0x10;
//       else if ( keys & 0x20 )
//           led = 0x20;
//       else if ( keys & 0x40 )     
//           led = 0x40;             
//       else if ( keys & 0x80 )      
//           led = 0x80;
        else
            led = 0;
            
        if ( keys ) 
            PORTD = led;           // Set corresponding LED if switch pressed
    }
}
