/*
 * SPI_DRIVER.c
 *
 *  Created on: Dec 9, 2023
 *      Author: Eng.TERA
 */


//-----------------------------------------
//-------<< INCLUDES >>--------------------
//-----------------------------------------
#include "SPI_DRIVER.h"
#include "GPIO_DRIVER.h"


//-----------------------------------------
//-------<< Generic Variables >>------------
//-----------------------------------------

static uint8_t TX_Interrupt_SPI_FLAG=0;
static uint8_t RX_Interrupt_SPI_FLAG=0;
SPI_Config_t * Global_SPI_Config_s;

/**================================================================
 * @Fn	 		-MCAL_SPI_Init
 * @brief 		-This Function used to initialize SPIs to specific configuration depending on the parameters
 * @param [in] 	-SPIx: Where x could be 1 or 2 or 3 depending on the Package
 * @param [in]	-SPI_Config_s: Is a pointer to the structure that contains the information of the SPI we want to configure
 * @retval		-none
 * Note			-In Our package LQFP48 we have only SPI1 and SPI2
 */
void MCAL_SPI_Init(SPI_REGISTERS_t * SPIx,SPI_Config_t * SPI_Config_s)
{
	uint16_t CR1_SAFETY=0;
	uint16_t temp_reg_CR2=0;
	Global_SPI_Config_s = SPI_Config_s;

	// 1- Master OR Slave Configure
	CR1_SAFETY |= SPI_Config_s->MASTER_OR_SLAVE;

	// 2- SPI MODES
	CR1_SAFETY |= SPI_Config_s->SPI_MODES;

	// 3- Clock Polarity
	CR1_SAFETY |=  SPI_Config_s->clock_polarity;

	// 4- Clock Phase
	CR1_SAFETY |=  SPI_Config_s->clock_phase;

	// 5- Data frame
	CR1_SAFETY |=  SPI_Config_s->data_frame;

	// 6- BAUD RATE Control
	CR1_SAFETY |= SPI_Config_s->Baud_rate_control;

	// 7- NSS Management
	//config NSS
	if(SPI_Config_s->NSS_Management ==SPI_NSS_HARDWARE_MASTER_SS_OUTPUT_ENABLE)
	{
		temp_reg_CR2|= SPI_Config_s->NSS_Management;
	}
	else if(SPI_Config_s->NSS_Management ==SPI_NSS_HARDWARE_MASTER_SS_OUTPUT_DISABLE)
	{
		temp_reg_CR2 &=  SPI_Config_s->NSS_Management;
	}
	else
	{
		CR1_SAFETY |= SPI_Config_s->NSS_Management;
	}
	//=======================================================

	// 8- Interrupts
	if(SPI_Config_s->Tx_buffer_empty_interrupt == Interrupt_Enable)
	{
		SPIx->SPI_CR2 |= (1<<7);
		TX_Interrupt_SPI_FLAG =1;
	}
	if(SPI_Config_s->RX_buffer_not_empty_interrupt == Interrupt_Enable)
	{
		SPIx->SPI_CR2 |= (1<<6);
		RX_Interrupt_SPI_FLAG =1;
	}

	//NVIC
	if( (TX_Interrupt_SPI_FLAG) || (RX_Interrupt_SPI_FLAG) ){
		if(SPIx == SPI1)
		{
			NVIC->NVIC_ISER1 |= (1<<(35-32));
		}
		else if(SPIx == SPI2)
		{
			NVIC->NVIC_ISER1 |= (1<<(36-32));
		}
	}

	//9- Enable SPI
	CR1_SAFETY |= (1<<6);

	// 10- PUSH INTO CR1 and CR2 REAL REGISTER
	SPIx->SPI_CR1 = CR1_SAFETY;
	SPIx->SPI_CR2 = temp_reg_CR2;

}
/**================================================================
 * @Fn	 		-MCAL_SPI_Send_Character
 * @brief 		-This Function used to send character ( or 16 bit variable ) depending on the SPI initialization
 * @param [in] 	-SPIx: Where x could be 1 or 2 or 3 depending on the Package
 * @param [in]	-buffer: Is a pointer to the buffer that contains the bits we want to send
 * @retval		-none
 * Note			-In Our package LQFP48 we have only SPI1 and SPI2
 */
void MCAL_SPI_Send_Character(SPI_REGISTERS_t * SPIx,uint16_t * buffer)
{
	if(!(TX_Interrupt_SPI_FLAG)) // If no interrupts ( Polling )
	{
		while(!(SPIx->SPI_SR & (1<<1)));
	}
	SPIx->SPI_DR = (*buffer & 0xFF);

}
/**================================================================
 * @Fn	 		-MCAL_SPI_Recieve_Character
 * @brief 		-This Function used to send character ( or 16 bit variable ) depending on the SPI initialization
 * @param [in] 	-SPIx: Where x could be 1 or 2 or 3 depending on the Package
 * @param [in]	-buffer: Is a pointer to the buffer that contains the bits we want to recieve
 * @retval		-none
 * Note			-In Our package LQFP48 we have only SPI1 and SPI2
 */
void MCAL_SPI_Recieve_Character(SPI_REGISTERS_t * SPIx,uint16_t * buffer)
{
	if(!(RX_Interrupt_SPI_FLAG)) // If no interrupts ( Polling )
	{
		while(!(SPIx->SPI_SR & (1<<0)));
	}
	*buffer  = ( SPIx->SPI_DR & 0xFF );

}

/**================================================================
 * @Fn	 		-MCAL_SPI_Recieve_Character
 * @brief 		-This Function used to send character ( or 16 bit variable ) depending on the SPI initialization
 * @param [in] 	-SPIx: Where x could be 1 or 2 or 3 depending on the Package
 * @param [in]	-buffer: Is a pointer to the buffer that contains the bits we want to recieve
 * @retval		-none
 * Note			-In Our package LQFP48 we have only SPI1 and SPI2
 */


void MCAL_SPI_TX_RX(SPI_REGISTERS_t* SPIx, uint16_t* buffer ){

	if(!(RX_Interrupt_SPI_FLAG)) // If no interrupts ( Polling )
	{
		while(!(SPIx->SPI_SR & (1<<0)));
	}

	*buffer = ( SPIx->SPI_DR & 0xFF );


	if(!(TX_Interrupt_SPI_FLAG)) // If no interrupts ( Polling )
	{
		while(!(SPIx->SPI_SR & (1<<1)));
	}
	SPIx->SPI_DR = (*buffer & 0xFF);
}


/**================================================================
 * @Fn	 		-MCAL_SPI_GPIO_PINS_CONFIG
 * @brief 		-This Function used to initialize specific Pins to its alternative SPI function
 * @param [in] 	-SPIx: Where x could be 1 or 2 or 3 depending on the Package
 * @retval		-none
 * Note			-In Our package LQFP48 we have only SPI1 and SPI2
 */
void MCAL_SPI_GPIO_PINS_CONFIG(SPI_REGISTERS_t * SPIx){
	// FOR SPI1
	//	SPI1_NSS PA4
	//	SPI1_SCK PA5
	//	SPI1_MISO PA6
	//	SPI1_MOSI PA7

	// TODO SPI2

	Pin_Config_t pin_cfg;

	//   PA4:NSS
	//   PA5:SCK
	//   PA6:MISO
	//	 PA7:MOSI
	if(Global_SPI_Config_s->MASTER_OR_SLAVE == Master)
	{
		switch(Global_SPI_Config_s->NSS_Management)
		{
//		case SPI_NSS_HARDWARE_MASTER_SS_OUTPUT_DISABLE:
//			pin_cfg.Pin_Num =4;
//			pin_cfg.mode= Input_AF;
//			MCAL_GPIO_Init(GPIOA , &pin_cfg);
//
//			break;


		case SPI_NSS_HARDWARE_MASTER_SS_OUTPUT_ENABLE:
			pin_cfg.Pin_Num =4;
			pin_cfg.mode= Output_ALF_Push_pull;
			pin_cfg.Speed_Output=speed_10;
			MCAL_GPIO_Init(GPIOA , &pin_cfg);
			break;
		}

		//PA5: SCLK
		pin_cfg.Pin_Num =5;
		pin_cfg.mode= Output_ALF_Push_pull;
		pin_cfg.Speed_Output=speed_10;
		MCAL_GPIO_Init(GPIOA , &pin_cfg);

		//PA6: MISO
		//full duplex
		pin_cfg.Pin_Num =6;
		pin_cfg.mode= Input_AF;
		MCAL_GPIO_Init(GPIOA , &pin_cfg);

		//PA7: MOSI
		//full duplex
		pin_cfg.Pin_Num =7;
		pin_cfg.mode= Output_ALF_Push_pull;
		pin_cfg.Speed_Output=speed_10;
		MCAL_GPIO_Init(GPIOA , &pin_cfg);
	}

	//Slave
	else if(Global_SPI_Config_s->MASTER_OR_SLAVE == Slave){

		if(Global_SPI_Config_s->NSS_Management == SPI_NSS_HARDWARE_SLAVE){
			//PA4: NSS
			pin_cfg.Pin_Num =4;
			pin_cfg.mode= Input_AF;
			MCAL_GPIO_Init(GPIOA , &pin_cfg);
		}



		//PA5: SCLK
		pin_cfg.Pin_Num =5;
		pin_cfg.mode= Input_AF;
		MCAL_GPIO_Init(GPIOA , &pin_cfg);


		//PA6: MISO
		//full duplex
		pin_cfg.Pin_Num =6;
		pin_cfg.mode= Output_ALF_Push_pull;
		pin_cfg.Speed_Output=speed_10;
		MCAL_GPIO_Init(GPIOA , &pin_cfg);

		//PA7: MOSI
		//full duplex
		pin_cfg.Pin_Num =7;
		pin_cfg.mode= Input_AF;
		MCAL_GPIO_Init(GPIOA , &pin_cfg);

	}
}





//-----------------------------------------------
//------------------<< ISR >>--------------------
//-----------------------------------------------


void SPI1_IRQHandler(void)
{
	Interrupt_flags_bits_t IRQ;
	IRQ.Receive_buffer_not_empty_flag = ( ( SPI1->SPI_SR & (1<<0) ) >> 0 );
	IRQ.Transmit_buffer_empty_flag = ( ( SPI1->SPI_SR & (1<<1) ) >> 1 );

	Global_SPI_Config_s->CallBack_PTR (&IRQ);



}

void SPI2_IRQHandler(void)
{
	Interrupt_flags_bits_t IRQ;
	IRQ.Receive_buffer_not_empty_flag = ( ( SPI2->SPI_SR & (1<<0) ) >> 0 );
	IRQ.Transmit_buffer_empty_flag = ( ( SPI2->SPI_SR & (1<<1) ) >> 1 );

	Global_SPI_Config_s->CallBack_PTR (&IRQ);

}
