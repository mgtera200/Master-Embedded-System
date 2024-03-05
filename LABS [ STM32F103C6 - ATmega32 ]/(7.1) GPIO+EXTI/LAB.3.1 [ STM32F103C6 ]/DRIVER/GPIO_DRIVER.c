/*
 * GPIO_DRIVER.c
 *
 *  ENG-TERA
 */
#include "GPIO_DRIVER.h"


typedef enum {
	CRL,
	CRH
}CR_status;

CR_status Check_CR(Pin_Config_t * Pin)
{
	if(Pin->Pin_Num <= 15 && Pin->Pin_Num > 7)
		return CRH;
	else
		return CRL;

}

/**================================================================
* @Fn	 		-MCAL_GPIO_Init
* @brief 		-This Function used to initialize specific Pin as I\O with different modes according to the parameters in Pin_config_s
* @param [in] 	-GPIOx: Where x could be from A >> E depending on the Package
* @param [in]	-Pin_config_s: Is a pointer to the structure that contains the information of the pin we want to configure
* @retval		-none
* Note			-In Our package LQFP48 we have only GPIOA and GPIOB
*/

void MCAL_GPIO_Init(GPIO_REGISTERS_t *GPIOx, Pin_Config_t * Pin_config_s){


	if(Pin_config_s->input == 1)
	{
		switch(Pin_config_s->mode)
		{
		case Input_floating:
			if(Check_CR(Pin_config_s) == CRH)
			{
				GPIOx->GPIOx_CRH &= (0b0000 << (4*(Pin_config_s->Pin_Num-8)));
				GPIOx->GPIOx_CRH |= (0b0100 << (4*(Pin_config_s->Pin_Num-8)));
			}
			else
			{
				GPIOx->GPIOx_CRL &= (0b0000 << (4*Pin_config_s->Pin_Num));
				GPIOx->GPIOx_CRL |= (0b0100 << (4*Pin_config_s->Pin_Num));
			}

			break;
		case Input_PullUp:
			if(Check_CR(Pin_config_s) == CRH)
			{
				GPIOx->GPIOx_CRH &= (0b0000 << (4*(Pin_config_s->Pin_Num-8)));
				GPIOx->GPIOx_CRH |= (0b1000 << (4*(Pin_config_s->Pin_Num-8)));
			}
			else
			{
				GPIOx->GPIOx_CRL &= (0b0000 << (4*Pin_config_s->Pin_Num));
				GPIOx->GPIOx_CRL |= (0b1000 << (4*Pin_config_s->Pin_Num));
			}
			GPIOx->GPIOx_ODR |= (0x1 << Pin_config_s->Pin_Num);

			break;
		case Input_PullDown:
			if(Check_CR(Pin_config_s) == CRH)
			{
				GPIOx->GPIOx_CRH &= (0b0000 << (4*(Pin_config_s->Pin_Num-8)));
				GPIOx->GPIOx_CRH |= (0b1000 << (4*(Pin_config_s->Pin_Num-8)));
			}
			else
			{
				GPIOx->GPIOx_CRL &= (0b0000 << (4*Pin_config_s->Pin_Num));
				GPIOx->GPIOx_CRL |= (0b1000 << (4*Pin_config_s->Pin_Num));
			}
			GPIOx->GPIOx_ODR |= (0x0 << Pin_config_s->Pin_Num);

			break;
		case Input_Analog:
			if(Check_CR(Pin_config_s) == CRH)
			{
				GPIOx->GPIOx_CRH &= (0b0000 << (4*(Pin_config_s->Pin_Num-8)));
			}
			else
			{
				GPIOx->GPIOx_CRL &= (0b0000 << (4*Pin_config_s->Pin_Num));
			}
			break;
		}

	}
	else if(Pin_config_s->GPIO_output == 1)
	{
		if(Pin_config_s->mode == Output_Open_drain)
		{
			switch(Pin_config_s->Speed_Output)
			{
			case speed_10:
				if(Check_CR(Pin_config_s) == CRH)
				{
					GPIOx->GPIOx_CRH &= (0b0000 << (4*(Pin_config_s->Pin_Num-8)));
					GPIOx->GPIOx_CRH |= (0b0101 << (4*(Pin_config_s->Pin_Num-8)));
				}
				else
				{
					GPIOx->GPIOx_CRL &= (0b0000 << (4*Pin_config_s->Pin_Num));
					GPIOx->GPIOx_CRL |= (0b0101 << (4*Pin_config_s->Pin_Num));
				}
				break;
			case speed_2:
				if(Check_CR(Pin_config_s) == CRH)
				{
					GPIOx->GPIOx_CRH &= (0b0000 << (4*(Pin_config_s->Pin_Num-8)));
					GPIOx->GPIOx_CRH |= (0b0110 << (4*(Pin_config_s->Pin_Num-8)));
				}
				else
				{
					GPIOx->GPIOx_CRL &= (0b0000 << (4*Pin_config_s->Pin_Num));
					GPIOx->GPIOx_CRL |= (0b0110 << (4*Pin_config_s->Pin_Num));
				}
				break;
			case speed_50:
				if(Check_CR(Pin_config_s) == CRH)
				{
					GPIOx->GPIOx_CRH &= (0b0000 << (4*(Pin_config_s->Pin_Num-8)));
					GPIOx->GPIOx_CRH |= (0b0111 << (4*(Pin_config_s->Pin_Num-8)));
				}
				else
				{
					GPIOx->GPIOx_CRL &= (0b0000 << (4*Pin_config_s->Pin_Num));
					GPIOx->GPIOx_CRL |= (0b0111 << (4*Pin_config_s->Pin_Num));
				}
				break;
			}
		}
		else//(Pin_config_s->mode == Output_Push_pull)
		{
			switch(Pin_config_s->Speed_Output)
			{
			case speed_10:
				if(Check_CR(Pin_config_s) == CRH)
				{
					GPIOx->GPIOx_CRH &= (0b0000 << (4*(Pin_config_s->Pin_Num-8)));
					GPIOx->GPIOx_CRH |= (0b0001 << (4*(Pin_config_s->Pin_Num-8)));
				}
				else
				{
					GPIOx->GPIOx_CRL &= (0b0000 << (4*Pin_config_s->Pin_Num));
					GPIOx->GPIOx_CRL |= (0b0001 << (4*Pin_config_s->Pin_Num));
				}
				break;
			case speed_2:
				if(Check_CR(Pin_config_s) == CRH)
				{
					GPIOx->GPIOx_CRH &= (0b0000 << (4*(Pin_config_s->Pin_Num-8)));
					GPIOx->GPIOx_CRH |= (0b0010 << (4*(Pin_config_s->Pin_Num-8)));
				}
				else
				{
					GPIOx->GPIOx_CRL &= (0b0000 << (4*Pin_config_s->Pin_Num));
					GPIOx->GPIOx_CRL |= (0b0010 << (4*Pin_config_s->Pin_Num));
				}
				break;
			case speed_50:
				if(Check_CR(Pin_config_s) == CRH)
				{
					GPIOx->GPIOx_CRH &= (0b0000 << (4*(Pin_config_s->Pin_Num-8)));
					GPIOx->GPIOx_CRH |= (0b0011 << (4*(Pin_config_s->Pin_Num-8)));
				}
				else
				{
					GPIOx->GPIOx_CRL &= (0b0000 << (4*Pin_config_s->Pin_Num));
					GPIOx->GPIOx_CRL |= (0b0011 << (4*Pin_config_s->Pin_Num));
				}
				break;
			}
		}
	}
	else if(Pin_config_s->ALF_output == 1)
	{
		if(Pin_config_s->mode == Output_Open_drain)
		{
			switch(Pin_config_s->Speed_Output)
			{
			case speed_10:
				if(Check_CR(Pin_config_s) == CRH)
				{
					GPIOx->GPIOx_CRH &= (0b0000 << (4*(Pin_config_s->Pin_Num-8)));
					GPIOx->GPIOx_CRH |= (0b1101 << (4*(Pin_config_s->Pin_Num-8)));
				}
				else
				{
					GPIOx->GPIOx_CRL &= (0b0000 << (4*Pin_config_s->Pin_Num));
					GPIOx->GPIOx_CRL |= (0b1101 << (4*Pin_config_s->Pin_Num));
				}
				break;
			case speed_2:
				if(Check_CR(Pin_config_s) == CRH)
				{
					GPIOx->GPIOx_CRH &= (0b0000 << (4*(Pin_config_s->Pin_Num-8)));
					GPIOx->GPIOx_CRH |= (0b1110 << (4*(Pin_config_s->Pin_Num-8)));
				}
				else
				{
					GPIOx->GPIOx_CRL &= (0b0000 << (4*Pin_config_s->Pin_Num));
					GPIOx->GPIOx_CRL |= (0b1110 << (4*Pin_config_s->Pin_Num));
				}
				break;
			case speed_50:
				if(Check_CR(Pin_config_s) == CRH)
				{
					GPIOx->GPIOx_CRH &= (0b0000 << (4*(Pin_config_s->Pin_Num-8)));
					GPIOx->GPIOx_CRH |= (0b1111 << (4*(Pin_config_s->Pin_Num-8)));
				}
				else
				{
					GPIOx->GPIOx_CRL &= (0b0000 << (4*Pin_config_s->Pin_Num));
					GPIOx->GPIOx_CRL |= (0b1111 << (4*Pin_config_s->Pin_Num));
				}
				break;
			}
		}
		else//(Pin_config_s->mode == Output_Push_pull)
		{
			switch(Pin_config_s->Speed_Output)
			{
			case speed_10:
				if(Check_CR(Pin_config_s) == CRH)
				{
					GPIOx->GPIOx_CRH &= (0b0000 << (4*(Pin_config_s->Pin_Num-8)));
					GPIOx->GPIOx_CRH |= (0b1001 << (4*(Pin_config_s->Pin_Num-8)));
				}
				else
				{
					GPIOx->GPIOx_CRL &= (0b0000 << (4*Pin_config_s->Pin_Num));
					GPIOx->GPIOx_CRL |= (0b1001 << (4*Pin_config_s->Pin_Num));
				}
				break;
			case speed_2:
				if(Check_CR(Pin_config_s) == CRH)
				{
					GPIOx->GPIOx_CRH &= (0b0000 << (4*(Pin_config_s->Pin_Num-8)));
					GPIOx->GPIOx_CRH |= (0b1010 << (4*(Pin_config_s->Pin_Num-8)));
				}
				else
				{
					GPIOx->GPIOx_CRL &= (0b0000 << (4*Pin_config_s->Pin_Num));
					GPIOx->GPIOx_CRL |= (0b1010 << (4*Pin_config_s->Pin_Num));
				}
				break;
			case speed_50:
				if(Check_CR(Pin_config_s) == CRH)
				{
					GPIOx->GPIOx_CRH &= (0b0000 << (4*(Pin_config_s->Pin_Num-8)));
					GPIOx->GPIOx_CRH |= (0b1011 << (4*(Pin_config_s->Pin_Num-8)));
				}
				else
				{
					GPIOx->GPIOx_CRL &= (0b0000 << (4*Pin_config_s->Pin_Num));
					GPIOx->GPIOx_CRL |= (0b1011 << (4*Pin_config_s->Pin_Num));
				}
				break;
			}
		}
	}
}
/**================================================================
* @Fn			-MCAL_GPIO_DeInit
* @brief		-Used to initialize the GPIO module to its reset state
* @param [in]	-GPIOx: Where x could be from A >> E depending on the Package
* @retval		-None
* Note			-None
*/
void MCAL_GPIO_DeInit(GPIO_REGISTERS_t *GPIOx){

	GPIOx->GPIOx_CRH = 0x44444444;
	GPIOx->GPIOx_CRL = 0x44444444;
	GPIOx->GPIOx_ODR = 0;
}
/**================================================================
* @Fn			-MCAL_GPIO_WritePin
* @brief		-Used to Write 1 or 0(Value) on an output pin
* @param [in]	-GPIOx: Where x could be from A >> E depending on the Package
* @param [in]	-Value: 1 for output high or 0 for output low
* @param [in]	-Pin_Num: Variable contains the output pin number
* @retval		-None
* Note			-None
*/
void MCAL_GPIO_WritePin(GPIO_REGISTERS_t *GPIOx,uint8_t Pin_Num,uint8_t Value){

	GPIOx->GPIOx_ODR |= (Value<<Pin_Num);
}

/**================================================================
* @Fn			-MCAL_GPIO_ReadPin
* @brief		-Used to read 1 or 0 on an input pin
* @param [in]	-GPIOx: Where x could be from A >> E depending on the Package
* @param [in]	-Pin_Num:Variable contains the output pin number
* @retval		-The value of data which the input pin contain
* Note			-None
*/

unsigned char MCAL_GPIO_ReadPin(GPIO_REGISTERS_t *GPIOx,uint8_t Pin_Num){

	char bit_read = ((GPIOx->GPIOx_IDR & (1 << Pin_Num)) >> Pin_Num);
	return bit_read;
}

/**================================================================
* @Fn			-MCAL_GPIO_WritePort
* @brief		-Used to write an output data to all of the port pins
* @param [in]	-GPIOx: Where x could be from A >> E depending on the Package
* @param [in]	-Value: The value of the data we want to send as an output on the port pins
* @retval		-None
* Note			-None
*/
void MCAL_GPIO_WritePort(GPIO_REGISTERS_t *GPIOx, uint8_t Value){

	GPIOx->GPIOx_ODR = Value;
}

/**================================================================
* @Fn			-MCAL_GPIO_ReadPort
* @brief		-Used to read an input data of all of the port pins
* @param [in]	-GPIOx: Where x could be from A >> E depending on the Package
* @retval		-The value of data which the input port contain
* Note			-None
*/
uint32_t MCAL_GPIO_ReadPort(GPIO_REGISTERS_t *GPIOx){

	uint32_t read_port = GPIOx->GPIOx_IDR;
	return read_port;
}
/**================================================================
* @Fn			-MCAL_GPIO_TogglePin
* @brief		-Used to toggle the data on the output pin
* @param [in]	-GPIOx: Where x could be from A >> E depending on the Package
* @param [in]	-Pin_Num:Variable contains the output pin number
* @retval		-The value of data which the input port contain
* Note			-None
*/
void MCAL_GPIO_TogglePin(GPIO_REGISTERS_t *GPIOx,uint8_t Pin_Num){

	GPIOx->GPIOx_ODR ^= (1<<Pin_Num);

}


