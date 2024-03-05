/*
 * main.c
 *
 * Created: 10/26/2023 2:56:07 AM
 *  Author: Dell
 */ 
#include <util/delay.h>
#include "address.h"
#include "DoBits.h"



void init_pins()
{
DDRC = 0b11111100;
DDRD = 0b11111000;
PORTD = 0;
}



/*void delay()
{
	int i;
	for(i=0; i<6000; i++);
}*/
int main(void)
{
	init_pins();
	
	//int i,j;
	
    while(1)
    {			
			while(!(((PIND & (1<<0))>>0) && !((PIND & (1<<5))>>5)));
			SETBIT(PORTD,5);
			
			while(((PIND & (1<<0))>>0));
			while(!(((PIND & (1<<0))>>0) && ((PIND & (1<<5))>>5)));
			SETBIT(PORTD,6);
			
			while(((PIND & (1<<0))>>0));
			while(!(((PIND & (1<<0))>>0) && ((PIND & (1<<6))>>6)));
			SETBIT(PORTD,7);
			
			while(((PIND & (1<<0))>>0));
			while(!(((PIND & (1<<0))>>0) && ((PIND & (1<<7))>>7)));
			CLRBIT(PORTD,7);
			
			while(((PIND & (1<<0))>>0));
			while(!(((PIND & (1<<0))>>0) && ((PIND & (1<<6))>>6)));
			CLRBIT(PORTD,6);
			
			while(((PIND & (1<<0))>>0));
			while(!(((PIND & (1<<0))>>0) && ((PIND & (1<<5))>>5)));
			CLRBIT(PORTD,5);
			
			while(((PIND & (1<<0))>>0));
	}
	return 0;
}