/*
 * ADC.h
 *
 * Created: 1/3/2024 5:57:32 PM
 *  Author: Dell
 */ 


#ifndef ADC_H_
#define ADC_H_
#include "ATMEGA32.h"

typedef enum {
	ADC_AREF,
	ADC_AVCC,
	ADC_Internal
}ADC_VoltageRef_Selection_t;

typedef enum {
	ADC_Channel_0,
	ADC_Channel_1,
	ADC_Channel_2,
	ADC_Channel_3,
	ADC_Channel_4,
	ADC_Channel_5,
	ADC_Channel_6,
	ADC_Channel_7
}ADC_Channel_Selection_t;

typedef enum {
	ADC_Prescaler_2,
	ADC_Prescaler_4 =2,
	ADC_Prescaler_8,
	ADC_Prescaler_16,
	ADC_Prescaler_32,
	ADC_Prescaler_64,	
	ADC_Prescaler_128
}ADC_Prescaler_Selection_t;

typedef enum {
	ADC_Mode_FreeRunning,
	ADC_Mode_AnalogComparator,
	ADC_Mode_External_Interrupt0
}ADC_AutoTrigger_Source_Selection_t;

typedef enum {
	ADC_Trigger_Enable,
	ADC_Trigger_Disable
}ADC_AutoTrigger_Enable_Disable_t;

typedef enum {
	ADC_Interrupt_Enable,
	ADC_Interrupt_Disable
}ADC_Conversion_Interrupt_Enable_Disable_t;


typedef struct{
	
	ADC_VoltageRef_Selection_t Ref;
	ADC_Channel_Selection_t Channel;
	ADC_Prescaler_Selection_t scale;
	ADC_AutoTrigger_Enable_Disable_t Trigger_Enable_Disable;
	ADC_AutoTrigger_Source_Selection_t trigger_Source_Selection;
	ADC_Conversion_Interrupt_Enable_Disable_t Interrupt_Enable_Disable;
	
}ADC_Config_s;

void ADC_Init(ADC_Config_s *config);
void ADC_FreeRunning_Start();


#endif /* ADC_H_ */