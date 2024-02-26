/*
 * timer.c
 *
 *  Created on: Dec 30, 2023
 *      Author: Dell
 */


#include "timer.h"

#define NULL (void*)0

Timer0_Config_s* Global_Timer_Config_s;
unsigned char TOV_Number;

Timer_Status_t Timer0_Init(Timer0_Config_s *config){

	Timer_Status_t error = Timer_No_Error;
	Global_Timer_Config_s = config;

	if(NULL == config)
	{
		error = Timer_Error;
	}
	else
	{
		TCCR0 |= config->Mode;
		TCCR0 |= config->Clock;
		TIMSK |= config->Output_Compare_Interrupt;
		TIMSK |= config->Timer_OverFlow_Interrupt;

	}



	return error;

}
Timer_Status_t Timer0_Stop(){

	Timer_Status_t error;
	error = Timer_No_Error;


	TCCR0 &= (0b000 << 0); // NO CLK


	return error;

}

Timer_Status_t Timer0_Get_CompareValue(unsigned char *Ticks){

	Timer_Status_t error;
	error = Timer_No_Error;


	*Ticks = OCR0;


	return error;

}
Timer_Status_t Timer0_Set_CompareValue(unsigned char Value){

	Timer_Status_t error;
	error = Timer_No_Error;


	OCR0 = Value;


	return error;

}

Timer_Status_t Timer0_Get_CounterValue(unsigned char *Ticks){

	Timer_Status_t error;
	error = Timer_No_Error;


	*Ticks = TCNT0;


	return error;



}
Timer_Status_t Timer0_Set_CounterValue(unsigned char Value){

	Timer_Status_t error;
	error = Timer_No_Error;


	TCNT0 = Value;


	return error;



}

Timer_Status_t Timer0_Get_OverFlowValue(unsigned char *Ticks){

	Timer_Status_t error;
	error = Timer_No_Error;


	*Ticks = TOV_Number;


	return error;


}
Timer_Status_t Timer0_Set_OverFlowValue(unsigned char Value){

	Timer_Status_t error;
	error = Timer_No_Error;


	TOV_Number = Value;


	return error;


}


ISR(TIMER0_COMP_vect)
{
	Global_Timer_Config_s->CompareMatch_CallBack_Ptr ();
}

ISR(TIMER0_OVF_vect)
{
	TOV_Number++;
	Global_Timer_Config_s->OverFlow_CallBack_Ptr ();
}
