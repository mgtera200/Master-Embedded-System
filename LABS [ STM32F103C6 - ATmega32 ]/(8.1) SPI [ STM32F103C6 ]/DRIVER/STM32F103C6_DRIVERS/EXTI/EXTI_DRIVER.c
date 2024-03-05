/*
 * GPIO_DRIVER.c
 *
 *  ENG-TERA
 */
#include "GPIO_DRIVER.h"
#include "EXTI_DRIVER.h"



//-----------------------------
// Private function
//-----------------------------
uint32_t check_port_return_binary(GPIO_REGISTERS_t* port){ // This function used to return the 4 bits required to set the AFIO register..
														  // based on which port we will use in order to map the GPIO pin to EXTI peripheral

	int binary;

	if(port == GPIOA){
		binary = 0;
	}
	else if(port == GPIOB)
	{
		binary = 1;
	}
	else if(port == GPIOC)
	{
		binary = 2;
	}

	return binary;


}

//-----------------------------
//Generic GLOBAL variable
//-----------------------------


void (*GP_IRQ_CallBack[15])(void); // This array contains pointers to call back functions to different external interrupt pins
								  // Every external interrupt pin should have call back function


/**================================================================
 * @Fn	 		-MCAL_EXTI_init
 * @brief 		-This Function used to initialize specific Pin as External interrupt with different modes according to the parameters in EXTI_config_s
 * @param [in]	-Pin_config_s: Is a pointer to the structure that contains the information of the pin we want to configure
 * @retval		-none
 * Note			-In Our package LQFP48 we have only GPIOA and GPIOB
 */

void MCAL_EXTI_init(EXTI_Config_t* EXTI_Config_s){

	MCAL_EXTI_Update(EXTI_Config_s);
}


/**================================================================
 * @Fn	 		-MCAL_EXTI_Deinit
 * @brief 		-This Function used to deinitialize specific Pin that was configured as External interrupt pin
 * @param [in]	-Pin_config_s: Is a pointer to the structure that contains the information of the pin we want to configure
 * @retval		-none
 * Note			-In Our package LQFP48 we have only GPIOA and GPIOB
 */
void MCAL_EXTI_DeInit(EXTI_Config_t* EXTI_Config_s){

	// 1- Reset the External interrupt pin to reset state in the GPIO register
	MCAL_GPIO_DeInit(EXTI_Config_s->EXTI_GPIO_Mapping.Port,EXTI_Config_s->EXTI_GPIO_Mapping.Pin_num);

	// 2- Disconnect the pin from the EXTI peripheral using AFIO registers
	uint8_t index;
	index = ( EXTI_Config_s->EXTI_GPIO_Mapping.Pin_num ) / 4;

	uint8_t shift;
	shift = ( ( EXTI_Config_s->EXTI_GPIO_Mapping.Pin_num ) % 4 ) * 4;

	AFIO->AFIO_EXTICR[index] &= ~(0x0F << shift);

	// 3- Reset EXTI Falling\Rising registers
	EXTI->EXTI_FTSR &= ~(1 << EXTI_Config_s->EXTI_GPIO_Mapping.Pin_num);
	EXTI->EXTI_RTSR &= ~(1 << EXTI_Config_s->EXTI_GPIO_Mapping.Pin_num);

	// 4- Enable interrupt line mask in EXTI peripheral
	EXTI->EXTI_IMR &= ~(1 << EXTI_Config_s->EXTI_GPIO_Mapping.Pin_num);

	// 5- Enable interrupt mask in NVIC peripheral
	if(EXTI_Config_s->EXTI_GPIO_Mapping.IRQ_num <= 31)
	{
		NVIC->NVIC_ISER0 &= ~(1 << EXTI_Config_s->EXTI_GPIO_Mapping.IRQ_num);
	}
	else if( (EXTI_Config_s->EXTI_GPIO_Mapping.IRQ_num > 31) && (EXTI_Config_s->EXTI_GPIO_Mapping.IRQ_num <= 63) )
	{
		NVIC->NVIC_ISER1 &= ~(1 << ( EXTI_Config_s->EXTI_GPIO_Mapping.IRQ_num - 32) );

	}
}


/**================================================================
 * @Fn	 		-MCAL_EXTI_Updat
 * @brief 		-This Function used to Update specific Pin " In run time " as External interrupt with different modes according to the parameters in EXTI_config_s
 * @param [in]	-Pin_config_s: Is a pointer to the structure that contains the information of the pin we want to configure
 * @retval		-none
 * Note			-In Our package LQFP48 we have only GPIOA and GPIOB
 */




void MCAL_EXTI_Update(EXTI_Config_t* EXTI_Config_s){

	// 1- first we need to configure the desired pin as an input floating
	Pin_Config_t Pin_config_s;
	Pin_config_s.Pin_Num = EXTI_Config_s->EXTI_GPIO_Mapping.Pin_num;
	Pin_config_s.mode = Input_floating;
	MCAL_GPIO_Init(EXTI_Config_s->EXTI_GPIO_Mapping.Port, &Pin_config_s);

	// 2- Connect the pin to EXTI peripheral using AFIO registers

	uint8_t index;
	index = ( EXTI_Config_s->EXTI_GPIO_Mapping.Pin_num ) / 4 ;

	uint8_t shift;
	shift = ( ( EXTI_Config_s->EXTI_GPIO_Mapping.Pin_num ) % 4 ) * 4  ;

	uint32_t binary;
	binary = check_port_return_binary(EXTI_Config_s->EXTI_GPIO_Mapping.Port);

	AFIO->AFIO_EXTICR[index] &= ~(0x0F << shift);
	AFIO->AFIO_EXTICR[index] |= (binary << shift);


	// 3- Set EXTI Falling\rising registers to match the user requirements

	if( (EXTI_Config_s->Rising_or_Falling) == FALLING)
	{
		EXTI->EXTI_FTSR &= ~(1 << EXTI_Config_s->EXTI_GPIO_Mapping.Pin_num);
		EXTI->EXTI_FTSR |=  (1 << EXTI_Config_s->EXTI_GPIO_Mapping.Pin_num);
		EXTI->EXTI_RTSR &= ~(1 << EXTI_Config_s->EXTI_GPIO_Mapping.Pin_num); // so that if we update from rising to falling

	}
	if( (EXTI_Config_s->Rising_or_Falling) == RISING)
	{
		EXTI->EXTI_RTSR &= ~(1 << EXTI_Config_s->EXTI_GPIO_Mapping.Pin_num);
		EXTI->EXTI_RTSR |= (1 << EXTI_Config_s->EXTI_GPIO_Mapping.Pin_num);
		EXTI->EXTI_FTSR &= ~(1 << EXTI_Config_s->EXTI_GPIO_Mapping.Pin_num); // so that if we update from falling to rising

	}
	else if( (EXTI_Config_s->Rising_or_Falling) == BOTH)
	{
		EXTI->EXTI_FTSR &= ~(1 << EXTI_Config_s->EXTI_GPIO_Mapping.Pin_num);
		EXTI->EXTI_FTSR |=  (1 << EXTI_Config_s->EXTI_GPIO_Mapping.Pin_num);
		EXTI->EXTI_RTSR &= ~(1 << EXTI_Config_s->EXTI_GPIO_Mapping.Pin_num);
		EXTI->EXTI_RTSR |=  (1 << EXTI_Config_s->EXTI_GPIO_Mapping.Pin_num);
	}

	// 4- Disable interrupt line mask in EXTI peripheral

	EXTI->EXTI_IMR &= ~(1 << EXTI_Config_s->EXTI_GPIO_Mapping.Pin_num);
	EXTI->EXTI_IMR |= (1 << EXTI_Config_s->EXTI_GPIO_Mapping.Pin_num);

	// 5- Disable interrupt mask in NVIC peripheral

	if(EXTI_Config_s->EXTI_GPIO_Mapping.IRQ_num <= 31)
	{
		NVIC->NVIC_ISER0 &= ~(1 << EXTI_Config_s->EXTI_GPIO_Mapping.IRQ_num);
		NVIC->NVIC_ISER0 |= (1 << EXTI_Config_s->EXTI_GPIO_Mapping.IRQ_num);
	}
	else if( (EXTI_Config_s->EXTI_GPIO_Mapping.IRQ_num > 31) && (EXTI_Config_s->EXTI_GPIO_Mapping.IRQ_num <= 63) )
	{
		NVIC->NVIC_ISER1 &= ~(1 << ( EXTI_Config_s->EXTI_GPIO_Mapping.IRQ_num - 32) );
		NVIC->NVIC_ISER1 |= (1 << ( EXTI_Config_s->EXTI_GPIO_Mapping.IRQ_num - 32) );
	}


	// 6- store the call back function in our array

	GP_IRQ_CallBack[EXTI_Config_s->EXTI_GPIO_Mapping.Pin_num] = EXTI_Config_s->Function_call;

}




//-----------------------------
// ISR functions
//-----------------------------


void EXTI0_IRQHandler(void)
{
	EXTI->EXTI_PR |= (1<<0); //WRITE 1 TO CLEAR
	GP_IRQ_CallBack[0]();
}

void EXTI1_IRQHandler(void)
{
	EXTI->EXTI_PR |= (1<<1); //WRITE 1 TO CLEAR
	GP_IRQ_CallBack[1]();
}


void EXTI2_IRQHandler(void)
{
	EXTI->EXTI_PR |= (1<<2); //WRITE 1 TO CLEAR
	GP_IRQ_CallBack[2]();
}


void EXTI3_IRQHandler(void)
{
	EXTI->EXTI_PR |= (1<<3); //WRITE 1 TO CLEAR
	GP_IRQ_CallBack[3]();
}

void EXTI4_IRQHandler(void)
{
	EXTI->EXTI_PR |= (1<<4); //WRITE 1 TO CLEAR
	GP_IRQ_CallBack[4]();
}

void EXTI9_5_IRQHandler(void)
{
	if( EXTI->EXTI_PR & (1<<5))
	{
		EXTI->EXTI_PR |= (1<<5); //WRITE 1 TO CLEAR
		GP_IRQ_CallBack[5]();
	}
	if( EXTI->EXTI_PR & (1<<6))
	{
		EXTI->EXTI_PR |= (1<<6); //WRITE 1 TO CLEAR
		GP_IRQ_CallBack[6]();
	}
	if( EXTI->EXTI_PR & (1<<7))
	{
		EXTI->EXTI_PR |= (1<<7); //WRITE 1 TO CLEAR
		GP_IRQ_CallBack[7]();
	}
	if( EXTI->EXTI_PR & (1<<8))
	{
		EXTI->EXTI_PR |= (1<<8); //WRITE 1 TO CLEAR
		GP_IRQ_CallBack[8]();
	}
	if( EXTI->EXTI_PR & (1<<9))
	{
		EXTI->EXTI_PR |= (1<<9); //WRITE 1 TO CLEAR
		GP_IRQ_CallBack[9]();
	}
}

void EXTI15_10_IRQHandler(void)
{
	if( EXTI->EXTI_PR & (1<<10))
	{
		EXTI->EXTI_PR |= (1<<10); //WRITE 1 TO CLEAR
		GP_IRQ_CallBack[10]();
	}
	else if( EXTI->EXTI_PR & (1<<11))
	{
		EXTI->EXTI_PR |= (1<<11); //WRITE 1 TO CLEAR
		GP_IRQ_CallBack[11]();
	}
	else if( EXTI->EXTI_PR & (1<<12))
	{
		EXTI->EXTI_PR |= (1<<12); //WRITE 1 TO CLEAR
		GP_IRQ_CallBack[12]();
	}
	else if( EXTI->EXTI_PR & (1<<13))
	{
		EXTI->EXTI_PR |= (1<<13); //WRITE 1 TO CLEAR
		GP_IRQ_CallBack[13]();
	}
	else if( EXTI->EXTI_PR & (1<<14))
	{
		EXTI->EXTI_PR |= (1<<14); //WRITE 1 TO CLEAR
		GP_IRQ_CallBack[14]();
	}
	else if( EXTI->EXTI_PR & (1<<15))
	{
		EXTI->EXTI_PR |= (1<<15); //WRITE 1 TO CLEAR
		GP_IRQ_CallBack[15]();
	}


}





