/*
 * DC.c
 *
 *  Created on: Sep 4, 2023
 *      Author: MOHTERA
 */
#include "stdio.h"
#include "stdlib.h"
#include "DC.h"
extern int CA_speed;
void (*DC_state)();
void DC_init(){
	printf("DC init DONE! \n");
}
void speed_set(int s){
	CA_speed = s;
	DC_state= DC_busy;
}
void DC_idle(){
DC_state_id = DC_IDLE;
DC_state = DC_idle;
printf("DC_idle state : speed=%d \n \n \n ",CA_speed);


}
void DC_busy(){
	DC_state_id = DC_BUSY;
	DC_state = DC_idle;
	printf("DC busy state : speed=%d \n \n \n ",CA_speed);


}
