#ifndef _main_h_
#define _main_h_
#include <avr/io.h>
#include "mydefs.h"

#define	F_CPU           8e6             // 8MHz
#include <util/delay.h>

/***************************************************************************/
/*                       define the wanted LCD type:                       */
/***************************************************************************/
//#define LCD_1X8
//#define LCD_1X16
//#define LCD_1X20
//#define LCD_1X40
//#define LCD_2X8       // some 1x16 are wired as 2x8
//#define LCD_2X12
#define LCD_2X16
//#define LCD_2X20
//#define LCD_2X24
//#define LCD_2X40
//#define LCD_4X16
//#define LCD_4X20

/***************************************************************************/
/*                       define the LCD connections:                       */
/***************************************************************************/
#define	LCD_D4		SBIT( PORTD, 4 )
#define	LCD_DDR_D4	SBIT( DDRD, 4 )

#define	LCD_D5		SBIT( PORTD, 5 )
#define	LCD_DDR_D5	SBIT( DDRD, 5 )

#define	LCD_D6		SBIT( PORTD, 6 )
#define	LCD_DDR_D6	SBIT( DDRD, 6 )

#define	LCD_D7		SBIT( PORTD, 7 )
#define	LCD_DDR_D7	SBIT( DDRD, 7 )

#define	LCD_RS		SBIT( PORTD, 2 )
#define	LCD_DDR_RS	SBIT( DDRD, 2 )

#define	LCD_E0		SBIT( PORTD, 3 )
#define	LCD_DDR_E0	SBIT( DDRD, 3 )


#endif
