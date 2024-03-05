/*
 * US.c
 *
 *  Created on: Sep 4, 2023
 *      Author: MOHTERA
 */
#include "US.h"
#include "stdio.h"
void distance_set(int d);
int distance =0;
void (* US_state)();

void US_init(){
	printf("US INIT DONE!\n");

}
int US_Get_distance_random (int l, int r, int count)
{
	int i;
	for(i = 0; i < count; i++)
	{
		int rand_num = (rand() % (r - l + 1)) + l;
		return rand_num;
	}
	return 0;

}
void US_busy(){
US_STATE_ID = US_BUSY;
distance = US_Get_distance_random(45,55,1);
printf("US >----distance=%d--> CA \n",distance);
distance_set(distance);
US_state = US_busy;

}
