/*
 * main.c
 *
 * Created: 11/30/2023 7:30:00 AM
 *  Author: Dell
 */ 

#include "ATMEGA32.h"
#include "UART.h"
#include "lcd.h"
#include "ADC.h"
#include <math.h>
#include <string.h>
#include <util/delay.h>
#include <avr/interrupt.h>

unsigned short adc_data;
unsigned short percentage;
float input;
float Temp;

int main(void)
{
	LCD_Init();
	ADC_Config_s adc_config;
	adc_config.Ref = ADC_AVCC;
	adc_config.Channel = ADC_Channel_0;
	adc_config.scale = ADC_Prescaler_128;
	adc_config.Trigger_Enable_Disable = ADC_Trigger_Enable;
	adc_config.trigger_Source_Selection = ADC_Mode_FreeRunning;
	adc_config.Interrupt_Enable_Disable = ADC_Interrupt_Enable;
	
	ADC_Init(&adc_config);
	ADC_FreeRunning_Start();
	
	
	
	for(;;)
	{
		percentage = ((float)adc_data/1023)*100;
		//input = ((float)(adc_data*5)/1023);
		//Temp = (float)adc_data*150/(float);
		LCD_Display_Number(percentage);
		LCD_Send_Character('%');
		LCD_Clear_Screen();
		
	}
}

ISR(ADC_vect){
	
adc_data = 0;
adc_data |= ADCL;
adc_data |= ((unsigned short)ADCH << 8);
ADCSRA |= ( 1<<4);


}


