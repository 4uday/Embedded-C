#include <reg51.h>
#include <stdio.h>

sbit motor_pin_1=P2^0; //positive lines
sbit motor_pin_2=P2^1; //negative lines

void main()
{
	unsigned int i;
	motor_pin_1=motor_pin_2=0;
	while(1)
	{
	//clockwise direction
		motor_pin_1=1;
		motor_pin_2=0;
		for(i=0;i<60000;i++); //with the help
		
		//anticlockwise direction
		motor_pin_1=0;
		motor_pin_2=1;
		for(i=0;i<60000;i++);
		
	}
}