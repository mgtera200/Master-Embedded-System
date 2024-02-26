/*
 * PS.c\
 *
 *  Created on: Sep 12, 2023
 *      Author: MOHTERA
 *
 */
#include "driver.h"
extern void send_pressure(int alg_pressure);
int PS_pressure =0;
void read_pressure(){
PS_pressure = getPressureVal();
send_pressure(PS_pressure);
}

