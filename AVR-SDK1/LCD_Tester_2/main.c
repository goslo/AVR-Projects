/* * LCD_Tester_2.c
 *
 * Created: 2018-01-17 7:58:11 AM
 * Author : jorge
 */ 

/* Simple LCD character display module demonstrator using
 * the 4-bit interface. No handling of the busy flag is 
 * done - all timing contraints are handled by delay loops.
 * This code should be good to run at up to 8 MHz.
 * Above that you might have to tweak the timing of things
 * including, but not restricted to, the existing delays.
 */

#define F_CPU 4000000    // AVR clock frequency in Hz, used by util/delay.h
#include <avr/io.h>
#include <util/delay.h>

/* Here are some defines for the data connections,
 * DB4..7 on the LCD display module. These should be wired
 * up to the four high pins  of any port A..D. You need to alter
 * these to fit your wire up of your display.
 */
#define LCD_DATA_PORT PORTD
#define LCD_DATA_DDR  DDRD

/* Here are some defines for the control connections 
 * (RS, R/W and E on the LCD display module). These can be wired
 * to any pins on any port A..D (all to the same port though).
 * You need to alter these to fit your wire up of your display. 
 */
#define LCD_CTRL_PORT PORTD
#define LCD_CTRL_DDR  DDRD
#define LCD_RS        2
#define LCD_RW        1
#define LCD_E         3

/*
 * YOU SHOULD NOT NEED TO ALTER ANYTHING BEYOND THIS POINT!
 *
 * This holds as long as you have the four data signals
 * connected to the upper 4-bit nibble of the AVR port,
 * and you run at a maximum frequency of 8 MHz.
 */

/* Here are some defines for the LCD instructions we'll use.
 */
#define LCD_FUNCTION_SET      0x38 // 0b00110000
#define LCD_FUNCTION_SET_4BIT 0x28 // 0b00101000
#define LCD_DISPLAY_OFF       0x08 // 0b00001000
#define LCD_DISPLAY_ON        0x0F // 0b00001111
#define LCD_DISPLAY_CLEAR     0x01 // 0b00000001
#define LCD_ENTRY_MODE_SET    0x06 // 0b00000110
#define LCD_CURSOR_HOME       0x02 // 0b00000010


/* LcdSendNibble
 * 
 * Sends a 4-bit nibble to the display.
 *
 * Parameters:
 *	uint8_t nibble	The high nibble of of this byte
 *					is sent to the display.
 * Returns:
 *	nothing
 */
void LcdSendNibble( uint8_t nibble )
{
   _delay_ms(5);

   // Output upper nibble on the data ports upper bits
   LCD_DATA_PORT = (nibble & 0xF0) | (LCD_DATA_PORT & 0x0F);

   // Toggle the E line
   LCD_CTRL_PORT |= (1<<LCD_E);   // Going up..
   LCD_CTRL_PORT &= ~(1<<LCD_E);  // ..and down.
}

/* LcdSendByte
 * 
 * Sends a 8-bit byte to the display.
 *
 * Parameters:
 *	uint8_t theByte	The byte to send to the display
 *
 * Returns:
 *	nothing
 */
void LcdSendByte(uint8_t theByte)
{
   // Send the high nibble
   LcdSendNibble(theByte);

   // Shift theByte to get lower nibble in upper part...
   theByte = theByte << 4;
   // ...and send it
   LcdSendNibble(theByte);
}

/* LcdSendInstruction
 * 
 * Sends an instruction to the display.
 *
 * Parameters:
 *	uint8_t command	This byte is sent to the display as 
 *					an instruction (RS low).
 * Returns:
 *	nothing
 */
void LcdSendInstruction( uint8_t theInstruction )
{
   // RS low for instructions
   LCD_CTRL_PORT &= ~(1<<LCD_RS);

   // Send the instruction
   LcdSendByte(theInstruction);
}

/* LcdSendCharacter
 * 
 * Sends a character to the display.
 *
 * Parameters:
 *	uint8_t nibble	This byte is sent to the display as 
 *					a character (RS high).
 * Returns:
 *	nothing
 */
void LcdSendCharacter(uint8_t theChar)
{
   // RS high for characters to display
   LCD_CTRL_PORT |= (1<<LCD_RS);

   // Send the command
   LcdSendByte(theChar);
}

/* LcdInitialize
 * 
 * Initialize the display.
 *
 * Parameters:
 *	none
 *
 * Returns:
 *	nothing
 */
void LcdInitialize(void)
{
   // initialize LCD control lines
   LCD_CTRL_PORT &= ~(1<<LCD_RS);	// RS low
   LCD_CTRL_PORT &= ~(1<<LCD_RW);	// R/W low
   LCD_CTRL_PORT &= ~(1<<LCD_E);	// E low

   // initialize LCD control lines to output
   LCD_CTRL_DDR |= (1<<LCD_RS);
   LCD_CTRL_DDR |= (1<<LCD_RW);
   LCD_CTRL_DDR |= (1<<LCD_E);

   // initialize LCD data port to input
   LCD_DATA_DDR |= 0xF0;      // Data on high four bits of port for now...

   // First part of init sequence is 3 x Function Set with
   // stipulated waits. Note that the display is in 8-bit mode
   // initially, but although the four low data lines are not connected
   // this does not matter as the instructions low nibble is zero anyway.
   _delay_ms(15);
   LcdSendNibble( LCD_FUNCTION_SET );
   _delay_ms(5);
   LcdSendNibble( LCD_FUNCTION_SET );
   _delay_us(100);
   LcdSendNibble( LCD_FUNCTION_SET );

   // Now, still in 8-bit mode, set the display to 4-bit mode
   LcdSendNibble( LCD_FUNCTION_SET_4BIT );

   // We are now in 4-bit mode.
   // Do the rest of the init sequence.
   LcdSendInstruction( LCD_FUNCTION_SET_4BIT );
   LcdSendInstruction( LCD_DISPLAY_OFF );
   LcdSendInstruction( LCD_DISPLAY_CLEAR );
   LcdSendInstruction( LCD_ENTRY_MODE_SET );
   LcdSendInstruction( LCD_DISPLAY_ON );
}

char message[] = "4-bit avr-gcc";


int main(void)
{
   LcdInitialize();

   volatile int i = 0;
   while (message[i] != 0)
	{
	   LcdSendCharacter(message[i]);
		i++;
   }

   while(1);
   return 0;
}

