/*
 * main.c
 *
 *  Created on: Sep 12, 2023
 *      Author: MOHTERA
 */

#include <stdint.h>
#include <stdio.h>
#include "driver.h"
#include "PS.h"
#include "alarm.h"
#include "Alg.h"
unsigned int timer2 = 20000;
void main (){
	GPIO_INITIALIZATION();
	PS_state = read_pressure;
	Alg_state = checking;
	Alarm_state = checking_signal;

	while (1)
	{
		PS_state();
		Alg_state();
		Alarm_state();
		Delay(timer2);
	}

}
