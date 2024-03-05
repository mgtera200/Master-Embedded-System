/*
 * WatchDog.h
 *
 *  Created on: Dec 30, 2023
 *      Author: Dell
 */


#ifndef WATCHDOG_DRIVER_WATCHDOG_H_
#define WATCHDOG_DRIVER_WATCHDOG_H_

#include <avr/io.h>

typedef enum {

	WatchDog_Time_Half_second = 0b101,
	WatchDog_Time_One_second = 0b110


}WatchDog_Prescale_t;

void WatchDog_Enable(WatchDog_Prescale_t);
void WatchDog_Disable();


#endif /* WATCHDOG_DRIVER_WATCHDOG_H_ */
