// Project name		: UART_string_transmit_Testing_for_ATmega16_IBOT_mini_V3
// Designed By 		: ROBOMART.com
// Designed for		: Robosapiens Technologies Pvt. Ltd.
//                	  http://www.robosapiensindia.com
/* Program for "Testing the Recieving & Transmitting of the MCU" 
______________________________________________________________________________________________________
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


#define F_CPU 12000000UL 					// define clock speed of the MCU
#include <avr/io.h> 						// include avr header file
#include <util/delay.h> 					// include delay header file
#include"lcd_16.h"   						// include lcd header file
#include"lcd_16.c" 
 
void USARTInit(unsigned int ubrr_value) 	// USART initialization 
{
/*
Baud rate = 9600
Data bits =8
Parity = None
Stop bits = 1
Flow Control = None
Transmission Mode = Asynchronous
USART Reciever = ON
USART Transmitter = ON
U2X = 0
UBRR value = 77

ATMega16 Calibrated Internal RC Oscilator Frequency = 12 MHz

*/

UBRRL = ubrr_value;    
UBRRH = 0;
UCSRC|=(1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);
UCSRB=(1<<RXEN)|(1<<TXEN);     				// Enable Receiver & Transmitter
}

unsigned char USARTReadChar()  				// USART recieving function
{
 while(!(UCSRA & (1<<RXC)));      			// Wait till the receiving  is not completed.
 return UDR;            					// Return the received data
}

void USARTTransmitChar(unsigned char data) 	// USART transmitting function
{
 while(!(UCSRA & (1<<UDRE)));   			// Wait till the data  register is not Empty.
 UDR=data;          						// put the data to be transfer
}

void USART_StringTransmit(unsigned char s[])  // function for string transmit
{
 int i=0;
 while(s[i]!='\0')
 {
 USARTTransmitChar(s[i]);
 i++;
 }

}

void main() 								// main function
{
DDRB=0b00010000;  							// declare PD4 as a output Pin connected to Buzzer
unsigned char data;
USARTInit(77);   							// Baudrate
lcd_init(LCD_DISP_ON); 						// LCD initalize
lcd_gotoxy(0,0);  							// select the position 
lcd_puts("System is Ready"); 				// print the text
lcd_gotoxy(0,1);  							// select the position
lcd_puts("  Send  Data   "); 				// Print the text
_delay_ms(100);

while(1)  									// infinite loop
  	 {   
	 data=USARTReadChar();   				// waiting to receive new data
     PORTB=0b00010000;       				// Buzzer ON 
	 lcd_clrscr();
     lcd_gotoxy(0,0);
     lcd_puts("Recived :      ");
     lcd_gotoxy(10,0);
	 lcd_putc(data);
     if((data=='A')||(data=='a'))
	 {
	  USART_StringTransmit(" \n\rA for Apple"); // string transmit
	  lcd_gotoxy(0,1);
      lcd_puts(" A for Apple   ");
	 }
     
	 else if((data=='B')||(data=='b'))
	 {
	  USART_StringTransmit(" \n\rB for Ball  ");
	  lcd_gotoxy(0,1);
      lcd_puts(" B for Ball    ");
	 }

     else if((data=='T')||(data=='t'))
	 {
	 USART_StringTransmit("\n\rTwinkle Twinkle little Star  ");
	 lcd_gotoxy(0,1);
     lcd_puts("Twinkle  Star     ");
	 }

	 else
	 {
     USART_StringTransmit(" \n\rSorry!!  Invalid Data ");
	 lcd_gotoxy(0,1);
     lcd_puts("Invalid Data !!   ");
     }
	 _delay_ms(100);

	 PORTB=0b00000000;      			   // Buzzer OFF
    
	 }									   // while closed 
	
	
} 									   	   // main closed

