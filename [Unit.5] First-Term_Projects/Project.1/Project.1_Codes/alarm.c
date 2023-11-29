/*
 * alarm.c
 *
 *  Created on: Sep 12, 2023
 *      Author: MOHTERA
 */
#include "driver.h"
int signal =0;
unsigned int timer=9000;
void alarm_set(int i){
	signal = i;
}
void checking_signal (){
	if(signal==0){
			Set_Alarm_actuator(0);
			Delay(timer);
			Set_Alarm_actuator(1);

		}
		else
			Set_Alarm_actuator(1);
}

