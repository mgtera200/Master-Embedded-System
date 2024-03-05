/*
 * CA.c

 *
 *  Created on: Sep 4, 2023
 *      Author: MOHTERA
 */
#include "CA.h"
void speed_set(int s);
int CA_speed = 0;
int CA_distance = 0;
int CA_threshold = 50;
void (*CA_state)();
void distance_set(int d){
	CA_distance = d;

}
void CA_waiting(){
	CA_STATE_ID = CA_WAITING;
	(CA_distance <= CA_threshold)? (CA_state = CA_waiting) : (CA_state = CA_driving);
	printf("CA was in waiting state: current distance = %d current speed = %d \n",CA_distance,CA_speed);
	(CA_distance <= CA_threshold)? (printf(" CA >-----SPEED=0---> DC \n")) : (printf(" CA >-----SPEED=30---> DC \n"));
	(CA_distance <= CA_threshold)? (speed_set(0)) : (speed_set(30));

}
void CA_driving(){
	CA_STATE_ID = CA_DRIVING;
	(CA_distance <= CA_threshold)? (CA_state = CA_waiting) : (CA_state = CA_driving);
	printf("CA was driving state: current distance = %d current speed = %d \n",CA_distance,CA_speed);
	(CA_distance <= CA_threshold)? (printf(" CA >-----SPEED=0---> DC \n")) : (printf(" CA >-----SPEED=30---> DC \n"));
	(CA_distance <= CA_threshold)? (speed_set(0)) : (speed_set(30));


}

