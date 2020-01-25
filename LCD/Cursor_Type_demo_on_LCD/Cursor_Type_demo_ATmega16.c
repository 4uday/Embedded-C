// Project name		: Cursor_Type_demo_on_LCD_for_ATmega16_IBOT_mini_V3
// Designed By 		: ROBOMART.com
// Designed for		: Robosapiens Technologies Pvt. Ltd.
//                	  http://www.robosapiensindia.com
/* Program for "Cursor_Type_demo_on_LCD" 
______________________________________________________________________________________________________
Connection settings of Kit

16x2 LCD connection
Pin 1 -----> GND
Pin 2 -----> VCC(+5v)
VEE   -----> Connected with Variable resistor
RS --------> PC0
RW --------> PC1
E  --------> PC2
D0,D1,D2 & D3 do not Used
D4 --------> PC4 
D5 --------> PC5
D6 --------> PC6
D7 --------> PC7
Pin 15-----> Vcc(+5v)
Pin 16-----> GND

BOOTLooder Condition Check--->PA0(If 0 bootler section else program execution section of Flash memory)
Crystal Ossilator(12MHz)----->XTAL1,XTAL2
VB=Battery Supply
VCC=regulated 5V+
Gnd=Ground(0V)

*/

#define F_CPU 1000000UL  // defines the clock speed
#include <avr/io.h>      // includes input/output header file     
#include <util/delay.h>  // includes delay header file   
#include"lcd_16.h"       // include lcd_16.h 
#include"lcd_16.c"       // include lcd_16.c

void wait(float x)       // wait function
{
for(int i=0;i<(int)(1302*x);i++)
_delay_loop_1(0);
}

int main (void)          // main function
{
lcd_init(LCD_DISP_ON_CURSOR_BLINK);   // initialize LCD

	while(1)                  // infinite loop
	{
	lcd_clrscr();             // clear screen
	lcd_puts("ROBOSAPIENS");  // print the text
	for(int i=0;i<11;i++)     // make text static for some time
	{ 
	wait(2);
	}

		for(int i=0;i<24;i++) // for loop
		{
		lcd_command(LCD_MOVE_DISP_LEFT); // Shift display left 16 times (use LCD_MOVE_DISP_RIGHT for shift Right)
		wait(2);
		}                     // loop closed
	} 						  // while closed
}							  // main closed




