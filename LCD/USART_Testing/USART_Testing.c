// Project name		: UART_Testing_for_ATmega16_IBOT_mini_V3
// Designed By 		: ROBOMART.com
// Designed for		: Robosapiens Technologies Pvt. Ltd.
//                	  http://www.robosapiensindia.com
/* Program for "Testing the Recieving & Transmitting of the MCU" 
_______________________________________________________________________________________________________
Connection settings of the Kit

TTL Bridge  is connected with the Serial Port of the MCU

RX ----> TX (PD1)
TX ----> RX (PD0)
GND----> GND pin of th MCU

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


#define F_CPU 12000000UL 						// define clock speed of the MCU
#include <avr/io.h>  							// include avr header file
#include <util/delay.h> 						// include delay header file
#include"lcd_16.h"   							// include LCD header file 
#include"lcd_16.c"  							// include LCD.C file
 
void USARTInit(unsigned int ubrr_value) 		// UART initialization function
{
 UBRRL = ubrr_value;    
 UBRRH = 0;
 UCSRC|=(1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);
 UCSRB=(1<<RXEN)|(1<<TXEN);     				// Enable Receiver & Transmitter
}


unsigned char USARTReadChar()
{
 while(!(UCSRA & (1<<RXC)));      				// Wait till the receiving  is not completed.
 return UDR;            						// Return the received data
}

void USARTTransmitChar(unsigned char data)
{
 while(!(UCSRA & (1<<UDRE)));   				// Wait till the data  register is not Empty.
 UDR=data;         							    // put the data to be transfer
}


void main()  									// main function
{
DDRB=0b00010000;  								// declare PB4 as a output pin connected to the buzzer
 
unsigned char data;

USARTInit(77);  								// Baud rate initialize

lcd_init(LCD_DISP_ON); 							// LCD initialization
lcd_gotoxy(0,0);  								// select the position of the text
lcd_puts("System is Ready"); 					// Print the Text
lcd_gotoxy(0,1); 								// select the position of the text
lcd_puts("  Send  Data   ");					// print the text
_delay_ms(100);


while(1)  										// infinite loop
  	 {   
	 data=USARTReadChar();   					// waiting to receive new data
     PORTB=0b00010000;       					// Buzzer ON 
	 lcd_clrscr();
     lcd_gotoxy(0,0);
     lcd_puts("Recived :      ");
     lcd_gotoxy(10,0);
	 lcd_putc(data);       
     USARTTransmitChar(data);  					// Increament the received data and transmit
	 lcd_gotoxy(0,1);
     lcd_puts("Transmitted:      ");
     lcd_gotoxy(13,1);
	 lcd_putc(data);
     _delay_ms(100);
	 PORTB=0b00000000;      					// Buzzer OFF
     } 											// while closed
	
} 												// main closed

