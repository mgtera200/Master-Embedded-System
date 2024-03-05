/*
 * UART_DRIVER.c
 *
 *  Created on: Dec 6, 2023
 *      Author: Eng.TERA
 */




//-----------------------------------------
//-------<< INCLUDES >>--------------------
//-----------------------------------------
#include "USART_DRIVER.h"


//-----------------------------------------
//-------<< Generic Variables >>------------
//-----------------------------------------

uint8_t TX_flag1 =0;
uint8_t RX_flag2 =0;
uint8_t TC_flag3 =0;
USART_Config_t * Global_USART_Config_s[2] = {NULL,NULL};

//-----------------------------------------
//-------<< Generic Macros >>------------
//-----------------------------------------
#define USARTDIV(_clock_,_baudrate_)      				(_clock_/(16*_baudrate_))
#define USARTDIV_MUL100(_clock_,_baudrate_)				((_clock_*25)/(_baudrate_*4))
#define Mantissa(_clock_,_baudrate_)					USARTDIV(_clock_,_baudrate_)
#define Mantissa_MUL100(_clock_,_baudrate_)				(USARTDIV(_clock_,_baudrate_)*100)
#define DIV_Fraction(_clock_,_baudrate_)				(( ( USARTDIV_MUL100(_clock_,_baudrate_) - Mantissa_MUL100(_clock_,_baudrate_) ) * 16 )/100 )
#define USART_BRR_Register(_clock_,_baudrate_)			(( Mantissa(_clock_,_baudrate_) << 4 ) | ( DIV_Fraction(_clock_,_baudrate_) & 0x0F ))

/**================================================================
 * @Fn	 		-MCAL_USART_Init
 * @brief 		-This Function used to initialize USARTs to specific configuration depending on the parameters
 * @param [in] 	-USARTx: Where x could be 1 or 2 or 3 depending on the Package
 * @param [in]	-USART_Config_s: Is a pointer to the structure that contains the information of the SPI we want to configure
 * @retval		-none
 * Note			-In Our package LQFP48 we have only USART1 and USART2
 */
void    MCAL_USART_Init(USART_REGISTERS_t * USARTx,USART_Config_t * USART_Config_s){

	if(USARTx == USART1)
	{
		Global_USART_Config_s[0] = USART_Config_s;
		USART1_CLOCK_EN();

	}
	if(USARTx == USART2)
	{
		Global_USART_Config_s[1] = USART_Config_s;
		USART2_CLOCK_EN();

	}

	if(USART_Config_s->Sync_EN == USART_Enable)
	{
		// 1- Bit 11 CLKEN: Clock enable

		USARTx->USART_CR2 |= (1<<11);

	}
	else if(USART_Config_s->Async_EN == USART_Enable)
	{

		// 1- USART ENABLE
		USARTx->USART_CR1 |= (1<<13);

		// 2- TX and RX ENABLE

		USARTx->USART_CR1 |= ( (1<<2) | (1<<3) );

		// 3- Program the M bit in USART_CR1 to define the word length.

		USARTx->USART_CR1 |= USART_Config_s->Async_Config_s.Word_Length;

		// 4- Program the number of stop bits in USART_CR2.

		USARTx->USART_CR2 |= USART_Config_s->Async_Config_s.Stop_Bits;

		// 5 - Select the desired baud rate using the USART_BRR register.

		if(USARTx == USART1)
		{

			USARTx->USART_BRR |= USART_BRR_Register(RCC_Get_PCLK2(),USART_Config_s->Async_Config_s.Baud_Rate);
		}
		if(USARTx == USART2)
		{
			USARTx->USART_BRR |= USART_BRR_Register(RCC_Get_PCLK1(),USART_Config_s->Async_Config_s.Baud_Rate);

		}
		// 6 - Set Parity Configurations

		if(USART_Config_s->Async_Config_s.Parity.Parity_Enable == USART_Enable)
		{

			USARTx->USART_CR1 |= (1<<10);
			USARTx->USART_CR1 |= USART_Config_s->Async_Config_s.Parity.Parity_Even_Odd;
		}
	}

	if( (USART_Config_s->interrupts_CNFG.TX_Interrupt_Enable_Or_Disable) == USART_Enable )
	{
		USARTx->USART_CR1 |= (1<<7);
		TX_flag1 =1;
	}
	if( (USART_Config_s->interrupts_CNFG.RX_Interrupt_Enable_Or_Disable) == USART_Enable )
	{
		USARTx->USART_CR1 |= (1<<5);
		RX_flag2=1;
	}
	if( (USART_Config_s->interrupts_CNFG.TC_Interrupt_Enable_Or_Disable) == USART_Enable )
	{
		USARTx->USART_CR1 |= (1<<6);
		TC_flag3=1;
	}

	if( (TX_flag1 || RX_flag2 || TC_flag3) )
	{

		if(USARTx == USART1)
		{
			NVIC->NVIC_ISER1 |= (1<< 5 );
		}
		else if(USARTx == USART2)
		{
			NVIC->NVIC_ISER1 |= (1<<6);
		}
		else if(USARTx == USART3)
		{
			NVIC->NVIC_ISER1 |= (1<<7);
		}
	}
}

/**================================================================
 * @Fn	 		-MCAL_USART_SendChar
 * @brief 		-This Function used to send a char (or 9 bits) depending on the USART configurations
 * @param [in] 	-USARTx: Where x could be 1 or 2 or 3 depending on the Package
 * @param [in]	-Buffer: Is a pointer to the buffer that we want to send
 * @retval		-none
 * Note			-In Our package LQFP48 we have only USART1 and USART2
 */
void    MCAL_USART_SendChar(USART_REGISTERS_t * USARTx,uint16_t * Buffer){

	if(!(  (TX_flag1)||(RX_flag2)||(TC_flag3) ))
	{
		while(!( USARTx->USART_SR & (1<<7) ) );

	}
	if(USARTx == USART1)
	{
		if(Global_USART_Config_s[0]->Async_Config_s.Word_Length == Nine_bits)
		{
			USARTx->USART_DR = (*Buffer  & 0x01FF );
		}
		else if(Global_USART_Config_s[0]->Async_Config_s.Word_Length == Eight_bits)
		{
			USARTx->USART_DR = (*Buffer  & 0xFF );
		}
	}
	else if(USARTx == USART2)
	{
		if(Global_USART_Config_s[1]->Async_Config_s.Word_Length == Nine_bits)
		{
			USARTx->USART_DR = (*Buffer  & 0x01FF );
		}
		else if(Global_USART_Config_s[1]->Async_Config_s.Word_Length == Eight_bits)
		{
			USARTx->USART_DR = (*Buffer  & 0xFF );
		}
	}




}
/**================================================================
 * @Fn	 		-MCAL_USART_RecieveChar
 * @brief 		-This Function used to receive a char (or 9 bits) depending on the USART configurations
 * @param [in] 	-USARTx: Where x could be 1 or 2 or 3 depending on the Package
 * @param [in]	-Buffer: Is a pointer to the buffer where we want to save the received value
 * @retval		-none
 * Note			-In Our package LQFP48 we have only USART1 and USART2
 */
void MCAL_USART_ReceiveChar(USART_REGISTERS_t * USARTx,uint16_t * Buffer){

	if( !(  (TX_flag1)||(RX_flag2)||(TC_flag3) )  )
	{
		while(!( USARTx->USART_SR & (1<<5) ) );

	}
	if(USARTx == USART1)
	{
		if(Global_USART_Config_s[0]->Async_Config_s.Word_Length == Nine_bits)
		{
			if(Global_USART_Config_s[0]->Async_Config_s.Parity.Parity_Enable)
			{
				*Buffer = USARTx->USART_DR   & 0xFF ;
			}
			else
			{
				*Buffer = USARTx->USART_DR & 0x01FF;
			}
		}
		else if(Global_USART_Config_s[0]->Async_Config_s.Word_Length == Eight_bits)
		{
			if(Global_USART_Config_s[0]->Async_Config_s.Parity.Parity_Enable)
			{
				*Buffer = USARTx->USART_DR   & 0x7F ;
			}
			else
			{
				*Buffer = USARTx->USART_DR & 0x0FF;
			}
		}
	}
	else if(USARTx == USART2)
	{
		if(Global_USART_Config_s[1]->Async_Config_s.Word_Length == Nine_bits)
		{
			if(Global_USART_Config_s[1]->Async_Config_s.Parity.Parity_Enable)
			{
				*Buffer = USARTx->USART_DR   & 0xFF ;
			}
			else
			{
				*Buffer = USARTx->USART_DR & 0x01FF;
			}
		}
		else if(Global_USART_Config_s[1]->Async_Config_s.Word_Length == Eight_bits)
		{
			if(Global_USART_Config_s[1]->Async_Config_s.Parity.Parity_Enable)
			{
				*Buffer = USARTx->USART_DR   & 0x7F ;
			}
			else
			{
				*Buffer = USARTx->USART_DR & 0x0FF;
			}
		}
	}

}

/**================================================================
 * @Fn	 		-MCAL_USART_GPIO_Pins_Config
 * @brief 		-This Function is to configure the USART pins to its alternative function
 * @param [in] 	-USARTx: Where x could be 1 or 2 or 3 depending on the Package
 * @retval		-none
 * Note			-In Our package LQFP48 we have only USART1 AND USART2
 */
void 	MCAL_USART_GPIO_Pins_Config(USART_REGISTERS_t * USARTx){

	// USARTx_RX Full duplex Input floating / Input pull-up
	// USARTx_TX(1) Full duplex Alternate function push-pull
	if(USARTx == USART1)
	{
		// USART1_TX PA9
		//USART1_RX PA10
		Pin_Config_t GPIO_Pin_CNFG_s;
		GPIO_Pin_CNFG_s.Pin_Num = 9;
		GPIO_Pin_CNFG_s.mode = Output_ALF_Push_pull;
		GPIO_Pin_CNFG_s.Speed_Output = speed_10;
		MCAL_GPIO_Init(GPIOA, &GPIO_Pin_CNFG_s);

		GPIO_Pin_CNFG_s.Pin_Num = 10;
		GPIO_Pin_CNFG_s.mode = Input_AF;
		MCAL_GPIO_Init(GPIOA, &GPIO_Pin_CNFG_s);

	}
	else if(USARTx == USART2)
	{
		// USART2_RX PA3
		//USART2_TX PA2
		Pin_Config_t GPIO_Pin_CNFG_s;
		GPIO_Pin_CNFG_s.Pin_Num = 2;
		GPIO_Pin_CNFG_s.mode = Output_ALF_Push_pull;
		GPIO_Pin_CNFG_s.Speed_Output = speed_10;
		MCAL_GPIO_Init(GPIOA, &GPIO_Pin_CNFG_s);

		GPIO_Pin_CNFG_s.Pin_Num = 3;
		GPIO_Pin_CNFG_s.mode = Input_AF;
		MCAL_GPIO_Init(GPIOA, &GPIO_Pin_CNFG_s);

	}

	else if(USARTx == USART3)
	{
		//USART3_RX PB11
		//USART3_TX PB10

		Pin_Config_t GPIO_Pin_CNFG_s;
		GPIO_Pin_CNFG_s.Pin_Num = 10;
		GPIO_Pin_CNFG_s.mode = Output_ALF_Push_pull;
		GPIO_Pin_CNFG_s.Speed_Output = speed_10;
		MCAL_GPIO_Init(GPIOB, &GPIO_Pin_CNFG_s);

		GPIO_Pin_CNFG_s.Pin_Num = 11;
		GPIO_Pin_CNFG_s.mode = Input_AF;
		MCAL_GPIO_Init(GPIOB, &GPIO_Pin_CNFG_s);

	}
}

//-----------------------------------------------
//------------------<< ISR >>--------------------
//-----------------------------------------------
void USART1_IRQHandler(void)
{
	interrupts_Bits IRQ = { ( (USART1->USART_SR) & (0b1<<5) ) >> 5 , ( (USART1->USART_SR) & (0b1<<6) ) >> 6 , ( (USART1->USART_SR) & (0b1<<7) ) >> 7};
	Global_USART_Config_s[0]->CallBack_FN (&IRQ);
}
void USART2_IRQHandler(void)
{
	interrupts_Bits IRQ = { ( (USART2->USART_SR) & (0b1<<5) ) >> 5 , ( (USART2->USART_SR) & (0b1<<6) ) >> 6 , ( (USART2->USART_SR) & (0b1<<7) ) >> 7};
	Global_USART_Config_s[1]->CallBack_FN (&IRQ);
}

