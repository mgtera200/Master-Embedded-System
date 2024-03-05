/*
 * GPIO_DRIVER.c
 *
 *  ENG-TERA
 */
#include "GPIO_DRIVER.h"


int get_CRLH_position(uint32_t pin_num){

	switch(pin_num)
	{
	case 0:
		return 0;
	case 1:
		return 4;
	case 2:
		return 8;
	case 3:
		return 12;
	case 4:
		return 16;
	case 5:
		return 20;
	case 6:
		return 24;
	case 7:
		return 28;
	case 8:
		return 0;
	case 9:
		return 4;
	case 10:
		return 8;
	case 11:
		return 12;
	case 12:
		return 16;
	case 13:
		return 20;
	case 14:
		return 24;
	case 15:
		return 28;
	}
	return 0;

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

	volatile uint32_t *configRegister = NULL;
	uint32_t pinConfig = 0;

	configRegister = (Pin_config_s->Pin_Num < 8)? &GPIOx->GPIOx_CRL : &GPIOx->GPIOx_CRH;
	(*configRegister) &= ~(0x000F << get_CRLH_position(Pin_config_s->Pin_Num));

	/* IF OUTPUT */

	if( (Pin_config_s->mode == Output_ALF_Push_pull) || (Pin_config_s->mode == Output_ALF_Open_drain) || (Pin_config_s->mode == Output_Open_drain) || (Pin_config_s->mode == Output_Push_pull) )
	{
		pinConfig = ( ( ( (Pin_config_s->mode - 4 )<< 2 ) | (Pin_config_s->Speed_Output) ) & 0x0F );
	}

	else // IF INPUT
	{
		if( (Pin_config_s->mode == Input_Analog) || (Pin_config_s ->mode == Input_floating) )
		{
			pinConfig =( ( (Pin_config_s->mode << 2) | 0x00 ) & 0x0F );
		}
		else if(Pin_config_s->mode == Input_AF)
		{
			pinConfig =( ( (Input_floating << 2 ) | 0x00 ) & 0x0F );
		}
		else // IF INPUT PULLUP\PULLDOWN
		{
			pinConfig = ( ( (Input_PullUp << 2 ) | 0x00 ) & 0x0F );
			if(Pin_config_s->mode == Input_PullUp) // IF PULL UP
			{
				GPIOx->GPIOx_ODR |= (1<<Pin_config_s->Pin_Num) ;
			}
			else // IF PULL DOWN
			{
				GPIOx->GPIOx_ODR &= ~(1<<Pin_config_s->Pin_Num) ;

			}
		}
	}
	(*configRegister) |=( (pinConfig) << get_CRLH_position(Pin_config_s->Pin_Num) );
}


/**================================================================
 * @Fn			-MCAL_GPIO_DeInit
 * @brief		-Used to initialize specific pin in the GPIO module to its reset state
 * @param [in]	-GPIOx: Where x could be from A >> E depending on the Package
 * @param [in]	-Pin_num: The pin number which we want to reset
 * @retval		-None
 * Note			-None
 */
void MCAL_GPIO_DeInit(GPIO_REGISTERS_t *GPIOx,uint8_t Pin_num){

//	GPIOx->GPIOx_CRH = 0x44444444;
//	GPIOx->GPIOx_CRL = 0x44444444;
//	GPIOx->GPIOx_ODR = 0;

	volatile uint32_t *configRegister = NULL;

		configRegister = (Pin_num < 8)? &GPIOx->GPIOx_CRL : &GPIOx->GPIOx_CRH;
		(*configRegister) &= ~(0x000F << get_CRLH_position(Pin_num));
		(*configRegister) |= (0x0004 << get_CRLH_position(Pin_num));

		GPIOx->GPIOx_ODR &= ~(1<<Pin_num) ;



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
void MCAL_GPIO_WritePin(GPIO_REGISTERS_t *GPIOx,uint32_t Pin_Num,uint32_t Value){

GPIOx->GPIOx_ODR &= ~(1<<Pin_Num);
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

unsigned char MCAL_GPIO_ReadPin(GPIO_REGISTERS_t *GPIOx,uint32_t Pin_Num){

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
void MCAL_GPIO_WritePort(GPIO_REGISTERS_t *GPIOx, uint32_t Value){

	GPIOx->GPIOx_ODR = (uint32_t)Value;
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


