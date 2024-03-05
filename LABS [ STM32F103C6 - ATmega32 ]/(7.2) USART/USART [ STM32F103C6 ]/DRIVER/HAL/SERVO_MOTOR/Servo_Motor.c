/*
 * Sorce_Motor.c
 *
 *  Eng.TERA
 */

#include "Servo_Motor.h"





//B8 SERVO1
void Servo1_Entry_Gate_Init(void)
{
	/*SERVO MOTOR 1*/
	Pin_Config_t PinCinfg;
	PinCinfg.Pin_Num=8;
	PinCinfg.mode= Output_Push_pull;
	PinCinfg.Speed_Output =speed_10;
	MCAL_GPIO_Init(GPIOB, &PinCinfg);
}

//Direction Up or Down
void Servo1_Entry_Gate(uint8_t Direction)
{
	if(Direction == UP)
	{
		//servo1 Enter gate up +90
		MCAL_GPIO_WritePin(GPIOB, 8, 1);
		dus(500);
		MCAL_GPIO_WritePin(GPIOB, 8, 0);
	}
	if(Direction==Down)
	{
		//servo1 Enter gate down -90
		MCAL_GPIO_WritePin(GPIOB, 8, 1);
		dus(1488);
		MCAL_GPIO_WritePin(GPIOB, 8, 0);
	}


}

//B9 SERVO2
void Servo2_Exit_Gate_Init(void)
{
	/*SERVO MOTOR 2*/
	Pin_Config_t PinCinfg;
	PinCinfg.Pin_Num=9;
	PinCinfg.mode = Output_Push_pull;
	PinCinfg.Speed_Output =speed_10;
	MCAL_GPIO_Init(GPIOB, &PinCinfg);
}

//Direction Up or Down
void Servo2_Exit_Gate(uint8_t Direction)
{
	if(Direction == UP)
	{
		//servo2 Exit gate up +90
		MCAL_GPIO_WritePin(GPIOB, 9, 1);
		dus(500);
		MCAL_GPIO_WritePin(GPIOB, 9, 0);
	}

	if(Direction == Down)
	{
		//servo2 Exit gate down -90
		MCAL_GPIO_WritePin(GPIOB, 9, 1);
		dus(1488);
		MCAL_GPIO_WritePin(GPIOB, 9, 0);
	}

}
