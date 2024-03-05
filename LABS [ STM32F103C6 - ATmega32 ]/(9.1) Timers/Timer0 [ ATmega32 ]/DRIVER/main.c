//ENG.TERA


#include <avr/io.h>
#include <util/delay.h>
#include "WatchDog.h"
#include "timer.h"

#define F_CPU 16000000UL

void Timer_CompareMatch_CallBack(void)
{
	PORTA = ~PORTA;
}
int main(void)
{
	DDRA = 0xFF;
	sei();
	Timer0_Config_t timer_config;

	timer_config.Mode = Timer0_Mode_CTC;
	timer_config.Clock = Timer0_Prescaling_CLK8;
	timer_config.Output_Compare_Interrupt = Timer0_Interrupt_OCIE_Enable;
	timer_config.CompareMatch_CallBack_Ptr = Timer_CompareMatch_CallBack;

	Timer0_Set_CompareValue(0xAA);
	Timer0_Init(&timer_config);

	for(;;)
	{

	}

return 0;
}
