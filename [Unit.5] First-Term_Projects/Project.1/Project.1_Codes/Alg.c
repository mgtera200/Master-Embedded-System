/*
 * Alg.c
 *
 *  Created on: Sep 12, 2023
 *      Author: MOHTERA
 */
#include "stdio.h"
int pressure=0;
int threshold = 20;
extern void alarm_set(int i);
void send_pressure(int alg_pressure){
pressure = alg_pressure;
}
void checking(){
	(pressure >= threshold)? (alarm_set(0)) : (alarm_set(1));

}
