/*
 * main.c
 *
 *  Created on: Sep 4, 2023
 *      Author: MOHTERA
 */


#include "CA.h"
#include "DC.h"
#include "US.h"
void setup()
{
	US_init();
	DC_init();
	US_state = US_busy;
	DC_state = DC_busy;
	CA_state = CA_waiting;
}
int main() {

	setup();
	while (1)
	{
		US_state();
		CA_state();
		DC_state();

	}
}
