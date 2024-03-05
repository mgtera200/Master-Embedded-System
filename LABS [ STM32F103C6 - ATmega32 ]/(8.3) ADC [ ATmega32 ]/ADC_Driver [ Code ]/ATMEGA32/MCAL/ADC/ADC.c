/*
 * ADC.c
 *
 * Created: 1/3/2024 5:58:12 PM
 *  Author: Dell
 */ 

#include "ADC.h"

void ADC_Init(ADC_Config_s *config){
	
	
	ADCSRA |= ( 1<<7 ); //ADC enable
	ADCSRA |= ( config->scale ); //ADC Prescaler
	ADMUX  |= ( config->Ref << 6);
	ADMUX  |= ( config->Channel);
	
	if(config->Trigger_Enable_Disable == ADC_Trigger_Enable)
	{
		ADCSRA |= ( 1<<5 ); //ADC trigger enable
		SFIOR  |= (config->trigger_Source_Selection << 5);
	}
	if(config->Interrupt_Enable_Disable == ADC_Interrupt_Enable)
	{
		ADCSRA |= (1<<3);
		SREG   |= (1<<7);
	}

}

void ADC_FreeRunning_Start(){
	
	ADCSRA |= ( 1<<6 ); //ADC start conversion

}

