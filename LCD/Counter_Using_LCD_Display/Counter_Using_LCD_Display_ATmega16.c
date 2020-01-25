// Project name		: Counter_Using_LCD_Display_for_ATmega16_IBOT_mini_V3
// Designed By 		: ROBOMART.com
// Designed for		: Robosapiens Technologies Pvt. Ltd.
//                	  http://www.robosapiensindia.com
/* Program for "Counter_Using_LCD_Display" 
______________________________________________________________________________________________________
Connection settings of the Kit

16x2 LCD connection
Pin 1 -----> GND
Pin 2 -----> VCC(+5v)
VEE   -----> Connected with Variable resistor
RS --------> PC0
RW --------> PC1
E  --------> PC2
D0,D1,D2 & D3 Not Used
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

#define F_CPU 12000000UL 	// defines the clock speed
#include <avr/io.h> 		// includes input/output header file     
#include <util/delay.h> 	// includes delay header file   
#include"lcd_16.h" 			// include lcd_16.h 
#include"lcd_16.c" 			// include lcd_16.c


void wait(float x)  		// wait Function
{
for(int i=0;i<(int)(1302*x);i++)
_delay_loop_1(0);
}


int main (void)  			// main function
{
int i=0;
char s[5];
lcd_init(LCD_DISP_ON); 		// initialize LCD
while(1)
	{
	itoa(i++, s, 10); 			// convert integer to string and store it in s
	lcd_clrscr();
	lcd_puts(s); 				// print converted string
	if(i==51) 					//if i=51 reset to 0
	i=0;
	wait(5);
	}

}  
