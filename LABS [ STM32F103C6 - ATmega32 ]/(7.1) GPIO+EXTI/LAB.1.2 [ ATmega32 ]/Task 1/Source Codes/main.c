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
}
/*void delay()
{
	int i;
	for(i=0; i<35000; i++);
}*/
int main(void)
{
	init_pins();
	
	int i,j;
	
    while(1)
    {
		for(i=0; i<10; i++)
		{
			for(j=0; j<10; j++)
			{
				PORTC = 0b1000 | (i<<4);
				_delay_ms(500);
				PORTC = 0b0100 | (j<<4);
				_delay_ms(1000);

			}
		}
    }
}