
/*
 *      Author: Eng.TERA
 */


#include "SPI_DRIVER.h"


//-------------------------------------------------
// GENERIC VARIABLES
//-------------------------------------------------

SPI_Config_t* Global_SPI_Config[2] ={NULL,NULL};

//-------------------------------------------------
// GENERIC FUNCTIONS
//-------------------------------------------------

#define	SPI1_INDEX	0
#define	SPI2_INDEX	1

#define   SPI_SR_RXNE            ((uint8_t)0x01)         //Bit 0 RXNE: Receive buffer not empty
#define   SPI_SR_TXE             ((uint8_t)0x02)         //Bit 1 TXE: Transmit buffer empty


//#define SPI_SR_TXE               1<<1
//#define SPI_SR_RXNE              1<<0
//-------------------------------------------------
// APIs
//-------------------------------------------------
/**************************************************************
 * @Fn			-MCAL_SPI_INIT
 * @Breif		-Initializes the SPI according to specified parameters
 * @Param [in]		-SPIx where x can be (1,2,3 depending on device used)
 * @Param [in]		-Config pointer to SPI_Config_t structure that contains the configuration information for the specified SPI
 * @Retval 		-None
 * Note			-Support for SPI Full duplex Master/Slave only & NSS HW only for slave
 */
void MCAL_SPI_INIT (SPI_REGISTERS_t* SPIx, SPI_Config_t* SPI_Config)
{
	//Safety for regs
	uint16_t tmpreg_CR1=0;
	uint16_t tmpreg_CR2=0;

	if (SPIx == SPI1)
	{
		Global_SPI_Config[SPI1_INDEX] = SPI_Config;
		SPI1_CLOCK_EN();
	}
	else if(SPIx == SPI2)
	{
		Global_SPI_Config[SPI2_INDEX] = SPI_Config;
		SPI2_CLOCK_EN();
	}
	//EN SPI CR1:Bit 6 SPE
	tmpreg_CR1= (0x1U<<6);

	//Master or slave
	tmpreg_CR1 |= SPI_Config->DEVICE_MODE;

	//Communication mode
	tmpreg_CR1 |= SPI_Config->COMM_MODE;

	//Data size
	tmpreg_CR1 |= SPI_Config->DATA_SZ;

	//SPI CLK_POLARITY
	tmpreg_CR1 |= SPI_Config->CLK_POLARITY;

	//SPI CLK_PHASE
	tmpreg_CR1 |= SPI_Config->CLK_PHASE;

	//Frame format
	tmpreg_CR1 |= SPI_Config->FRAME_FORMAT;


	//NSS

	if (SPI_Config->NSS == SPI_NSS_HW_MASTER_SSO_ENABLE)
	{
		tmpreg_CR2 |= SPI_Config->NSS;
	}
	else if ((SPI_Config->NSS == SPI_NSS_HW_MASTER_SSO_DISABLE) || (SPI_Config->NSS == SPI_NSS_HW_SLAVE))
	{
		tmpreg_CR2 &= SPI_Config->NSS;
	}

	else
	{
		tmpreg_CR1 |= SPI_Config->NSS;
	}

	// SPI BaudRate prescalar
	tmpreg_CR1 |= SPI_Config->SPI_BAUDRATE_PRESCALAR;


	// SPI_IRQ_ ENABLE/DISABLE
	if (SPI_Config->IRQ_ENABLE !=  SPI_IRQ_ENABLE_NONE)
	{
		tmpreg_CR2 |= SPI_Config->IRQ_ENABLE;
		if (SPIx == SPI1)
		{
			NVIC_IRQ35_SPI1_ENABLE;
		}
		else if(SPIx == SPI2)
		{
			NVIC_IRQ36_SPI2_ENABLE;
		}

	}

	SPIx->SPI_CR1 = tmpreg_CR1;
	SPIx->SPI_CR2 = tmpreg_CR2;


	//SPIx->I2SCFGR &= ~(1<<11);
	//SPIx->CRCPR = 0x0;

}

/**************************************************************
 * @Fn			-MCAL_SPI_DeINIT
 * @Breif		-Deinitializes the SPI (
 * @Param [in]		-SPIx where x can be (1,2,3 depending on device used)
 * @Retval 		-None
 * Note			-Reset model by RCC
 */

void MCAL_SPI_DeINIT (SPI_REGISTERS_t* SPIx)
{
	if (SPIx == SPI1)
	{
		NVIC_IRQ35_SPI1_DISABLE;
		SPI1_CLOCK_Reset();
	}
	else if(SPIx == SPI2)
	{
		NVIC_IRQ36_SPI2_DISABLE;
		SPI2_CLOCK_Reset();
	}

}

/**************************************************************
 * @Fn			-MCAL_SPI_GPIO_SET_PINS
 * @Breif		-Initializes GPIO pins
 * @Param [in]		-SPIx where x can be (1,2,3 depending on device used)
 * @Retval 		-None
 * Note			-Check pin alternative table
 */
void MCAL_SPI_GPIO_SET_PINS(SPI_REGISTERS_t* SPIx)
{
	Pin_Config_t pin_cfg;

	if (SPIx == SPI1)
	{
		//PA4:SPI1_NSS
		//PA5:SPI1_SCK
		//PA6:SPI_MISO
		//PA7:SPI_MOSI

		if (Global_SPI_Config[SPI1_INDEX]->DEVICE_MODE == SPI_DEVICE_MODE_MASTER)
		{
			//PA4:SPI1_NSS
			switch (Global_SPI_Config[SPI1_INDEX]->NSS)
			{
			case SPI_NSS_HW_MASTER_SSO_DISABLE:
				//Hardware master /slave Input floating
				pin_cfg.Pin_Num =4;
				pin_cfg.mode= Input_AF;
				MCAL_GPIO_Init(GPIOA , &pin_cfg);
				break;

			case SPI_NSS_HW_MASTER_SSO_ENABLE:
				//Hardware master/ NSS output enabled Alternate function push-pull
				pin_cfg.Pin_Num =4;
				pin_cfg.mode= Output_ALF_Push_pull;
				pin_cfg.Speed_Output=speed_10;
				MCAL_GPIO_Init(GPIOA , &pin_cfg);
				break;
			default:
				break;
			}

			//PA5:SPI1_SCK
			//Master Alternate function push-pull
			pin_cfg.Pin_Num =5;
			pin_cfg.mode= Output_ALF_Push_pull;
			pin_cfg.Speed_Output=speed_10;
			MCAL_GPIO_Init(GPIOA , &pin_cfg);

			//PA6:SPI_MISO
			//Supported only (Full Duplex) master: Input floating
			pin_cfg.Pin_Num =6;
			pin_cfg.mode= Input_AF;
			MCAL_GPIO_Init(GPIOA , &pin_cfg);
			//PA7:SPI_MOSI
			//Supported only (Full Duplex) master: Alternate function push-pull
			pin_cfg.Pin_Num =7;
			pin_cfg.mode= Output_ALF_Push_pull;
			pin_cfg.Speed_Output=speed_10;
			MCAL_GPIO_Init(GPIOA , &pin_cfg);		}


		else if (Global_SPI_Config[SPI1_INDEX]->DEVICE_MODE == SPI_DEVICE_MODE_SLAVE)
		{
			//PA4:SPI1_NSS
			if (Global_SPI_Config[SPI1_INDEX]->NSS == SPI_NSS_HW_SLAVE )
			{	//Hardware master /slave Input floating
				pin_cfg.Pin_Num =4;
				pin_cfg.mode= Input_AF;
				MCAL_GPIO_Init(GPIOA , &pin_cfg);
			}
			//PA5:SPI1_SCK
			//Slave Input floating
			pin_cfg.Pin_Num =5;
			pin_cfg.mode= Input_AF;
			MCAL_GPIO_Init(GPIOA , &pin_cfg);

			//PA6:SPI_MISO
			//Supported only (Full Duplex) slave:  Alternate function push-pull
			pin_cfg.Pin_Num =6;
			pin_cfg.mode= Output_ALF_Push_pull;
			pin_cfg.Speed_Output=speed_10;
			MCAL_GPIO_Init(GPIOA , &pin_cfg);

			//PA7:SPI_MOSI
			//Supported only (Full Duplex) slave: Input floating
			pin_cfg.Pin_Num =7;
			pin_cfg.mode= Input_AF;
			MCAL_GPIO_Init(GPIOA , &pin_cfg);
		}


	}
	else if(SPIx == SPI2)
	{
		//PB12:SPI1_NSS
		//PB13:SPI1_SCK
		//PB14:SPI_MISO
		//PB15:SPI_MOSI


		if (Global_SPI_Config[SPI2_INDEX]->DEVICE_MODE == SPI_DEVICE_MODE_MASTER)
		{
			//PB12:SPI1_NSS
			switch (Global_SPI_Config[SPI2_INDEX]->NSS)
			{
			case SPI_NSS_HW_MASTER_SSO_DISABLE:
				//Hardware master /slave Input floating
				pin_cfg.Pin_Num =12;
				pin_cfg.mode= Input_AF;
				MCAL_GPIO_Init(GPIOB , &pin_cfg);
				break;

			case SPI_NSS_HW_MASTER_SSO_ENABLE:
				//Hardware master/ NSS output enabled Alternate function push-pull
				pin_cfg.Pin_Num =12;
				pin_cfg.mode= Output_ALF_Push_pull;
				pin_cfg.Speed_Output=speed_10;
				MCAL_GPIO_Init(GPIOB , &pin_cfg);
				break;
			}

			//PB13:SPI1_SCK
			//Master Alternate function push-pull
			pin_cfg.Pin_Num =13;
			pin_cfg.mode= Output_ALF_Push_pull;
			pin_cfg.Speed_Output=speed_10;
			MCAL_GPIO_Init(GPIOB , &pin_cfg);


			//PB14:SPI_MISO
			//Supported only (Full Duplex) master: Input floating
			pin_cfg.Pin_Num =14;
			pin_cfg.mode= Input_AF;
			MCAL_GPIO_Init(GPIOB , &pin_cfg);

			//PB15:SPI_MOSI
			//Supported only (Full Duplex) master: Alternate function push-pull
			pin_cfg.Pin_Num =15;
			pin_cfg.mode= Output_ALF_Push_pull;
			pin_cfg.Speed_Output=speed_10;
			MCAL_GPIO_Init(GPIOB , &pin_cfg);
		}


		else if (Global_SPI_Config[SPI2_INDEX]->DEVICE_MODE == SPI_DEVICE_MODE_SLAVE)
		{
			//PB12:SPI1_NSS
			if (Global_SPI_Config[SPI2_INDEX]->NSS == SPI_NSS_HW_SLAVE )
			{	//Hardware master /slave Input floating
				pin_cfg.Pin_Num =12;
				pin_cfg.mode= Input_AF;
				MCAL_GPIO_Init(GPIOB , &pin_cfg);
			}
			//PB13:SPI1_SCK
			//Slave Input floating
			pin_cfg.Pin_Num =13;
			pin_cfg.mode= Input_AF;
			MCAL_GPIO_Init(GPIOB , &pin_cfg);

			//PB14:SPI_MISO
			//Supported only (Full Duplex) slave:  Alternate function push-pull
			pin_cfg.Pin_Num =14;
			pin_cfg.mode= Output_ALF_Push_pull;
			pin_cfg.Speed_Output=speed_10;
			MCAL_GPIO_Init(GPIOB , &pin_cfg);

			//PB15:SPI_MOSI
			//Supported only (Full Duplex) slave: Input floating
			pin_cfg.Pin_Num =15;
			pin_cfg.mode= Input_AF;
			MCAL_GPIO_Init(GPIOA , &pin_cfg);
		}

	}
}


/**************************************************************
 * @Fn				-MCAL_SPI_SEND_DATA
 * @Breif			-Send Buffer on SPI
 * @Param [in]		-SPUx where x can be (1,2,3 depending on device used)
 * @Param [in]		-pTX_Buffer buffer
 * @Param [in]		-ENUM to check if polling mechanism is enabled
 * @Retval 			-None
 * Note				-Should initialize SPI first
 *
 */

void MCAL_SPI_SEND_DATA (SPI_REGISTERS_t* SPIx, uint16_t* pTX_Buffer, Polling_Mechanism PollingEn)
{
	//TODO check if transmit only or recieve only
	if ( PollingEn == Polling_enable)
		while( !((SPIx->SPI_SR) &  SPI_SR_TXE) );

	SPIx->SPI_DR = *pTX_Buffer;

}


/**************************************************************
 * @Fn			-MCAL_SPI_RECEIVE_DATA
 * @Breif		-Receive Buffer on SPI
 * @Param [in]		-SPIx where x can be (1,2,3 depending on device used)
 * @Param [in]		-pTX_Buffer buffer
 * @Param [in]		-ENUM to check if polling mechanism is enabled
 * @Retval 		-None
 * Note			-Should initialize SPI first
 */
void MCAL_SPI_RECEIVE_DATA (SPI_REGISTERS_t* SPIx, uint16_t* pTX_Buffer,  Polling_Mechanism PollingEn)
{
	if ( PollingEn == Polling_enable)
		while( !((SPIx->SPI_SR) & SPI_SR_RXNE));

	*pTX_Buffer = SPIx->SPI_DR;
}

void MCAL_SPI_TX_RX (SPI_REGISTERS_t* SPIx,uint16_t* pTX_Buffer,  Polling_Mechanism PollingEn)
{

	if ( PollingEn == Polling_enable)
		while( !((SPIx->SPI_SR ) &  SPI_SR_TXE) );
	SPIx->SPI_DR = *pTX_Buffer;

	if ( PollingEn == Polling_enable)
		while( !((SPIx->SPI_SR) & SPI_SR_RXNE) );
	*pTX_Buffer = SPIx->SPI_DR;






}


//-------------------------------------------------
// IRQ
//-------------------------------------------------

void SPI1_IRQHandler(void)
{
	S_IRQ_SRC irq_src;

	irq_src.TXE =  (SPI1->SPI_SR & (1<<1) >> 1 );
	irq_src.RXNE =  (SPI1->SPI_SR & (1<<0) >> 0 );
	irq_src.ERRI =  (SPI1->SPI_SR & (1<<4) >> 4 );

	Global_SPI_Config[SPI1_INDEX]->P_SPI_IRQ_CALLBACK(irq_src);
}

void SPI2_IRQHandler(void)
{
	S_IRQ_SRC irq_src;

	irq_src.TXE = (SPI2->SPI_SR & (1<<1) >> 1 );
	irq_src.RXNE = (SPI2->SPI_SR & (1<<0) >> 0 );
	irq_src.ERRI = (SPI2->SPI_SR & (1<<4) >> 4 );

	Global_SPI_Config[SPI2_INDEX]->P_SPI_IRQ_CALLBACK(irq_src);
}
