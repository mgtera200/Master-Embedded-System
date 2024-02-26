/*
 * timer.h
 *
 *  Created on: Dec 30, 2023
 *      Author: Dell
 */

#ifndef AVR_MCAL_INC_TIMER_H_
#define AVR_MCAL_INC_TIMER_H_

#include <avr/io.h>
#include <avr/interrupt.h>



typedef enum {

	Timer_Error,
	Timer_No_Error

}Timer_Status_t;

typedef enum{

	Timer0_Mode_Normal = 0x0,
	Timer0_Mode_PWM_Phase_Correct = 0b01000000,
	Timer0_Mode_CTC = 0x08,
	Timer0_Mode_Fast_PWM = 0b01001000


}Timer0_Modes_t;

typedef enum {

	Timer0_Prescaling_NoCLK,
	Timer0_Prescaling_CLK0,
	Timer0_Prescaling_CLK8,
	Timer0_Prescaling_CLK64,
	Timer0_Prescaling_CLK256,
	Timer0_Prescaling_CLK1024,
	Timer0_Prescaling_ExternalCLK_Falling,
	Timer0_Prescaling_ExternalCLK_Rising

}Timer0_Clock_t;


typedef enum {

	Timer0_Interrupt_OCIE_Disable ,
	Timer0_Interrupt_OCIE_Enable = 0x02


}OCMIE_t;


typedef enum {

	Timer0_Interrupt_TOVIE_Disable,
	Timer0_Interrupt_TOVIE_Enable = 0x01

}TOVIE_t;


typedef struct {

	Timer0_Modes_t Mode;
	Timer0_Clock_t Clock;
	OCMIE_t Output_Compare_Interrupt;
	TOVIE_t Timer_OverFlow_Interrupt;
	void(*OverFlow_CallBack_Ptr)(void);
	void(*CompareMatch_CallBack_Ptr)(void);


}Timer0_Config_t;



Timer_Status_t Timer0_Init(Timer0_Config_t *config);
Timer_Status_t Timer0_Stop();

Timer_Status_t Timer0_Get_CompareValue(unsigned char *Ticks);
Timer_Status_t Timer0_Set_CompareValue(unsigned char Value);

Timer_Status_t Timer0_Get_CounterValue(unsigned char *Ticks);
Timer_Status_t Timer0_Set_CounterValue(unsigned char Value);

Timer_Status_t Timer0_Get_OverFlowValue(unsigned char *Ticks);
Timer_Status_t Timer0_Set_OverFlowValue(unsigned char Value);



#endif /* AVR_MCAL_INC_TIMER_H_ */
