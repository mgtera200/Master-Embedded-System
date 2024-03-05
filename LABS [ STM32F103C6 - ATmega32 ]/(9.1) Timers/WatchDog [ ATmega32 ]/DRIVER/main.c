/*
 * main.c
 *
 *  Created on: Dec 30, 2023
 *      Author: Dell
 */

#include <avr/io.h>
#include <util/delay.h>
#include "WatchDog.h"
#include "timer.h"

#define F_CPU 16000000UL

//void Timer_OverFlow_CallBack(void)
//{
//
//}
int main(void)
{
	DDRC |= (1<<0);
	PORTC &= ~(1<<0);
	for(;;)
	{
		WatchDog_Enable(WatchDog_Time_One_second);
		_delay_ms(700);
		PORTC ^= (1<<0);
		WatchDog_Disable();

	}

return 0;
}
