/*
 * WatchDog.c
 *
 *  Created on: Dec 30, 2023
 *      Author: Dell
 */
#include "WatchDog.h"

void WatchDog_Enable(WatchDog_Prescale_t pre){

	char temp_register;
	temp_register = WDTCR;
	temp_register |= ( ( 1<<3 ) | pre );
	WDTCR = temp_register;

}
void WatchDog_Disable(){

	char temp_register;
	temp_register = WDTCR;
	temp_register |= (0b11 << 3);
	WDTCR = temp_register;
	WDTCR &= ~(1<<3);
	WDTCR = 0;


}
