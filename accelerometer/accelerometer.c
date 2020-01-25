/*	Accelerometer is connected with PORTA 0,1,2	*/ 
#define F_CPU 12000000UL
	#include <avr/io.h>
	#include <avr/interrupt.h>
	#include<util/delay.h>
	#include"lcd_16.h"
	#include"lcd_16.c"

	#define X_FORWARD 450
	#define Y_FORWARD 380
	#define Z_FORWARD 430

	#define X_BACKWARD 320
	#define Y_BACKWARD 380
	#define Z_BACKWARD 440
#define X_RIGHT 380
#define Y_RIGHT 330
#define Z_RIGHT 440

#define X_LEFT 380
#define Y_LEFT 450
#define Z_LEFT 430

#define X_STOP 380
#define Y_STOP 382
#define Z_STOP 460
	char buffer[5];

int ReadADC(uint8_t ch)
{
   ADC=0;		
   //Select ADC Channel ch must be 0-7
   ADMUX = ADMUX & 0b11100000; //ADMUX7,6 is to select VREF and ADCMUX 5 is ADLAR
   ch=ch&0b00000111;
   ADMUX|=ch;		       // selecting the ADC channel	
//Start Single conversion
   ADCSRA |= (1<<ADSC);
   //Wait for conversion to complete
   while(!(ADCSRA&(1<<ADIF)));	// ADIF 1 when conversion completes
//Clear ADIF by writing one to it
ADCSRA|=(1<<ADIF); // thisis how ADIF is cleared
   return(ADC);
}
	void initADC()
		{
		ADMUX=(1<<REFS0);  // For Aref=AVcc;
		ADCSRA=(1<<ADEN)|(1<<ADIE)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS1); //Prescalar div factor =128
		}
	void wait(float x)
		{
		int i;
		for(i=0;i<(int)(61*x);i++)
		_delay_loop_2(0);
		}
int main(void)
{
DDRA=0x00;
DDRB=0xFF;
lcd_init(LCD_DISP_ON);
lcd_clrscr();
initADC();
int x=0,y=0,z=0, range=30;
while(1)
{
x=ReadADC(1);
y=ReadADC(2);
z=ReadADC(3);
lcd_gotoxy(0,0);
sprintf(buffer,"x=%4d, y=%4d,\nz=%4d    ",x,y,z);
lcd_puts(buffer);
if((x>(X_STOP-range))&&(x<(X_STOP+range))&&(y>(Y_STOP-range))&&(y<(Y_STOP+range))&&(z>(Z_STOP-range))&&(z<(Z_STOP+range)))
{
PORTB=0b00000000;// stop
lcd_gotoxy(8,1);
lcd_puts("STOP");
}
if((x>(X_FORWARD-range))&&(x<(X_FORWARD+range))&&(y>(Y_FORWARD-range))&&(y<(Y_FORWARD+range))&&(z>(Z_FORWARD-range))&&(z<(Z_FORWARD+range)))
{
PORTB=0b00100100; //forward
lcd_gotoxy(8,1);
lcd_puts("FRWD");
}
	if((x>(X_BACKWARD-range))&&(x<(X_BACKWARD+range))&&(y>(Y_BACKWARD-range))&&(y<(Y_BACKWARD+range))&&(z>(Z_BACKWARD-range))&&(z<(Z_BACKWARD+range)))
	{
	PORTB=0b00011000; // back
	lcd_gotoxy(8,1);
	lcd_puts("BACK");
	}
if((x>(X_LEFT-range))&&(x<(X_LEFT+range))&&(y>(Y_LEFT-range))&&(y<(Y_LEFT+range))&&(z>(Z_LEFT-range))&&(z<(Z_LEFT+range)))
{
PORTB=0b00000100; // left
lcd_gotoxy(8,1);
lcd_puts("LEFT");
}
	if((x>(X_RIGHT-range))&&(x<(X_RIGHT+range))&&(y>(Y_RIGHT-range))&&(y<(Y_RIGHT+range))&&(z>(Z_RIGHT-range))&&(z<(Z_RIGHT+range)))
	{
	PORTB=0b00100000; // right
	lcd_gotoxy(8,1);
	lcd_puts("RIGHT");
	}
wait(.30);
lcd_clrscr();
}
return 0; 
}


