/*
 * SPI_DRIVER.c
 *
 *  Created on: Dec 9, 2023
 *      Author: Eng.TERA
 */


//-----------------------------------------
//-------<< INCLUDES >>--------------------
//-----------------------------------------
#include "I2C_DRIVER.h"
#include "RCC_DRIVER.h"
#include "GPIO_DRIVER.h"


//-----------------------------------------
//-------<< Generic Variables >>------------
//-----------------------------------------


I2C_InitTypeDef Global_I2C_Config[2] = {0} ;

//--------------------------------------------------------------------------------------------------------------
//-----------------------------------------------<< Generic Macros >>------------------------------------------
//--------------------------------------------------------------------------------------------------------------


#define		I2C1_INDEX		0
#define		I2C2_INDEX		1


//---------------------------------------------------------------------------------------------------------------
//-----------------------------------------------<< Generic Functions >>-----------------------------------------
//---------------------------------------------------------------------------------------------------------------

void I2C_GenerateSTART(I2C_REGISTERS_t *I2Cx,FunctionalState NewState , Repeated_Start start){

	if(start != repeated_start)
	{
		// Check if the bus is idle
		while(I2C_GetFlagStatus(I2Cx,I2C_FLAG_BUSY )); //todo || timeout flag check);
	}
	//	Bit 8 START: Start generation
	//	This bit is set and cleared by software and cleared by hardware when start is sent or PE=0.
	//	In Master Mode:
	//	0: No Start generation
	//	1: Repeated start generation
	//	In Slave mode:
	//	0: No Start generation
	//	1: Start generation when the bus is free

	if(NewState != Disable)
	{
		/* Generate a start condition  */
		I2Cx->I2C_CR1 |= I2C_CR1_START;
	}
	else
	{
		I2Cx->I2C_CR1 &= ~(I2C_CR1_START);
	}
}
//======================================================================================

FlagStatus I2C_GetFlagStatus(I2C_REGISTERS_t *I2Cx,Status flag){

	uint32_t flag1=0;
	uint32_t flag2=0;
	uint32_t lastevent=0;
	FlagStatus bitstatus = RESET;
	switch(flag)
	{
	case I2C_FLAG_BUSY:
		//Bit 1 BUSY: Bus busy
		//0: No communication on the bus
		//1: Communication ongoing on the bus
		//– Set by hardware on detection of SDA or SCL low
		//– cleared by hardware on detection of a Stop condition.
		//It indicates a communication in progress on the bus. This information is still updated when
		//the interface is disabled (PE=0).

		if( (I2Cx->I2C_SR2) & (I2C_SR2_BUSY) )
		{
			bitstatus = SET;
		}

		else
		{
			bitstatus = RESET;
		}
		break;

	case EV5:
		//	Bit 0 SB: Start bit (Master mode)
		//	0: No Start condition
		//	1: Start condition generated.
		//	– Set when a Start condition generated.
		//	– Cleared by software by reading the SR1 register followed by writing the DR register, or by
		//	 hardware when PE=0

		if( (I2Cx->I2C_SR1) & (I2C_SR1_SB) )
			bitstatus = SET;
		else
			bitstatus = RESET;

		break;


	case EV6:
		//		Bit 1 ADDR: Address sent (master mode)/matched (slave mode)
		//		Address sent (Master)
		//		0: No end of address transmission
		//		1: End of address transmission
		//		– For 10-bit addressing, the bit is set after the ACK of the 2nd byte.
		//		– For 7-bit addressing, the bit is set after the ACK of the byte.
		//		Note: ADDR is not set after a NACK reception

		if( (I2Cx->I2C_SR1) & (I2C_SR1_ADDR) )
			bitstatus = SET;
		else
			bitstatus = RESET;

		break;


	case EV8_1:
	case EV8:
		//		Bit 7 TxE: Data register empty (transmitters)
		//		0: Data register not empty
		//		1: Data register empty
		//		– Set when DR is empty in transmission. TxE is not set during address phase.
		//		– Cleared by software writing to the DR register or by hardware after a start or a stop condition
		//		or when PE=0.
		//		TxE is not set if either a NACK is received, or if next byte to be transmitted is PEC (PEC=1)
		//		Note: TxE is not cleared by writing the first data being transmitted, or by writing data when
		//		BTF is set, as in both cases the data register is still empty.
		if( (I2Cx->I2C_SR1) & (I2C_SR1_TXE) )
		{
			bitstatus = SET;
		}

		else
		{
			bitstatus = RESET;
		}
		break;


	case EV7:
		//		Bit 6 RxNE: Data register not empty (receivers)
		//		0: Data register empty
		//		1: Data register not empty
		//		– Set when data register is not empty in receiver mode. RxNE is not set during address phase.
		//		– Cleared by software reading or writing the DR register or by hardware when PE=0.
		//		RxNE is not set in case of ARLO event.
		//		Note: RxNE is not cleared by reading data when BTF is set, as the data register is still full.
		if( (I2Cx->I2C_SR1) & (I2C_SR1_RXNE) )
		{
			bitstatus = SET;
		}

		else
		{
			bitstatus = RESET;
		}
		break;

	case MASTER_BYTE_TRANSMITTING:
	{
		/*  Read the I2Cx Status registers */
		flag1 = I2Cx->I2C_SR1;
		flag2 = I2Cx->I2C_SR2;
		flag2 = (flag2 << 16);
		/* Get the last event value from I2Cx status register */
		lastevent = (flag1 | flag2 ) & ((uint32_t)0x00FFFFFF);
		/* Check whether the last event contains the flag */
		if( (lastevent & flag) == flag )
		{
			bitstatus = SET;
		}
		else
		{
			bitstatus = RESET;

		}
		break;
	}

	}


	return bitstatus;



}

//======================================================================================

void I2C_SendAddress(I2C_REGISTERS_t *I2Cx,uint16_t Address , I2C_Direction Direction)
{

	Address = (Address << 1);
	if(Direction != I2C_Direction_Transmitter)
	{
		/* Set the address bit0 for read */
		Address |= ( 1 << 0);
	}
	else
	{
		/* Set the address bit0 for write */
		Address &= ~( 1 << 0);
	}

	/* Send The Address */
	I2Cx->I2C_DR = Address;

}

//================================================================================


void I2C_AcknowledgeConfig(I2C_REGISTERS_t *I2Cx,FunctionalState NewState){

	uint16_t tempreg;
	tempreg = I2Cx->I2C_CR1;

	if(NewState == Enable)
	{
		tempreg |= I2C_CR1_ACK;
		I2Cx->I2C_CR1 = tempreg;

	}
	else
	{
		tempreg &= ~(I2C_CR1_ACK);
		I2Cx->I2C_CR1 = tempreg;
	}

}
//=================================================================================

void I2C_GenerateSTOP(I2C_REGISTERS_t *I2Cx,FunctionalState NewState){

	if(NewState != Disable)
	{
		/* Generate a Stop condition */
		I2Cx->I2C_CR1 |= I2C_CR1_STOP;
	}
	else
	{
		/* Disable the stop condition generation */
		I2Cx->I2C_CR1 &= ~(I2C_CR1_STOP);

	}


}

//================================================================================







/*
 * =====================================================================================================================
 * 													APIs Supported by "MCAL I2C DRIVER"
 * ======================================================================================================================
 */


/* ================================================================
 * @Fn 				- MCAL_I2C_Init
 * @brief 			- Initializes I2Cx according to the specified parameters in I2C_Config
 * @param [in] 		- I2Cx : where x can be (1..2 depending on device used) to select I2C peripheral
 * @param [in] 		- I2C_InitStruct : a pointer to I2C_InitTypeDef structure that contains the configuration information for the specified I2C Module
 * @retval 			- None
 * Note 			- Supported for I2C SM mode only
 * 					- Support only 7-bit address mode
 */
void MCAL_I2C_Init(I2C_REGISTERS_t * I2Cx, I2C_InitTypeDef * I2C_InitStruct){
	uint16_t tempreg=0;
	uint16_t freqrange=0;
	uint32_t pclk1 = 8000000;
	uint16_t result = 0;
	if(I2Cx == I2C1)
	{
		Global_I2C_Config[I2C1_INDEX] = *I2C_InitStruct;
		I2C1_CLOCK_EN();
	}
	else
	{
		Global_I2C_Config[I2C2_INDEX] = *I2C_InitStruct;
		I2C2_CLOCK_EN();
	}

	if(I2C_InitStruct->I2C_Mode == I2C_Mode_I2C)
	{
		/*------------------ INIT Timing ---------------------*/
		// -- I2C_CR2.FREQ[5:0]: Peripheral clock frequency
		/* Get the I2Cx CR2 value */
		tempreg = I2Cx->I2C_CR2;
		/* Clear frequency FREQ[5:0] bits */
		tempreg &= ~(I2C_CR2_FREQ);
		/* Get pclk1 frequency value */
		pclk1 = RCC_Get_PCLK1();
		/* Set frequency bits depending on pclk1 value */
		freqrange = (uint16_t)(pclk1 / 1000000);
		tempreg |= freqrange;
		/* Write to I2Cx CR2 */
		I2Cx->I2C_CR2 = tempreg;
		//• Configure the clock control registers(I2C_CCR)
		// Disable I2C Peripheral while configuring time
		I2Cx->I2C_CR1 &= ~(I2C_CR1_PE);
		tempreg = 0;
		/* Configure speed in standard mode */
		if( (I2C_InitStruct->I2C_ClockSpeed == I2C_SCLK_SM_50K) || (I2C_InitStruct->I2C_ClockSpeed == I2C_SCLK_SM_100K) )
		{
			/* Standard mode speed calculate */
			// Tclk/2 = CRR * Tpclk1
			// CRR = Tclk / (2 * Tpclk1 )
			// CRR = Fpclk1 / ( 2 * I2C_ClockFrequency )
			result = (uint16_t)(pclk1 / (I2C_InitStruct->I2C_ClockSpeed << 1) );
			tempreg |= result;
			I2Cx->I2C_CCR = tempreg;

			/*------------------ I2C_TRISE Configuration ---------------------*/
			I2Cx->I2C_TRISE = freqrange + 1;


		}
		else
		{
			// Fast mode not supported
		}

		/*------------------ I2Cx CR1 Configuration ---------------------*/
		// Get THe I2Cx CR1 value
		tempreg = I2Cx->I2C_CR1;
		tempreg |= (uint16_t)( I2C_InitStruct->I2C_ACK_Control |   I2C_InitStruct->General_Call_Address_Detection | I2C_InitStruct->I2C_Mode | I2C_InitStruct->StretchMode );
		// Write to I2Cx CR1
		I2Cx->I2C_CR1 = tempreg;

		/*------------------ I2Cx OAR1 & I2Cx OAR2 Configuration ---------------------*/
		tempreg =0;
		if(I2C_InitStruct->I2C_Slave_Address.Enable_Dual_ADD == 1 )
		{
			tempreg = I2C_OAR2_ENDUAL ;
			tempreg |= I2C_InitStruct->I2C_Slave_Address.Secondary_slave_address << I2C_OAR2_ADD2_Pos;
			I2Cx->I2C_OAR2 = tempreg;
		}
		tempreg = 0;
		tempreg |= I2C_InitStruct->I2C_Slave_Address.Primary_slave_address << 1 ;
		tempreg |= I2C_InitStruct->I2C_Slave_Address.I2C_Addressing_Slave_mode;
		I2Cx->I2C_OAR1 = tempreg;

	}
	else
	{
		// SMBus not supported
	}


	// Interrupt Mode (Slave mode ) // Check callback pointer != NULL
	if(I2C_InitStruct->P_Slave_Event_CallBack != NULL)
	{
		//Enable IRQ
		I2Cx->I2C_CR2 |= (I2C_CR2_ITERREN);
		I2Cx->I2C_CR2 |= (I2C_CR2_ITEVTEN);
		I2Cx->I2C_CR2 |= (I2C_CR2_ITBUFEN);

		if(I2Cx == I2C1)
		{
			NVIC_IRQ31_I2C1_EV_Enable;
			NVIC_IRQ32_I2C1_ER_Enable;


		}
		else if (I2Cx == I2C2)
		{
			NVIC_IRQ31_I2C2_EV_Enable;
			NVIC_IRQ32_I2C2_ER_Enable;
		}
		I2Cx->I2C_SR1 =0;
		I2Cx->I2C_SR2 =0;
	}

	I2Cx->I2C_CR1 |= I2C_CR1_PE;

}

/* ================================================================
 * @Fn 				- MCAL_I2C_DInit
 * @brief 			- Resets Selected I2C Module and disable NVIC IRQs
 * @param [in] 		- I2Cx : where x can be (1..2 depending on device used) to select I2C peripheral
 * @retval 			- None
 * Note 			- Reset The Module By RCC & Disable NVIC
 */

void MCAL_I2C_DInit(I2C_REGISTERS_t * I2Cx){

	if(I2Cx == I2C1)
	{
		NVIC_IRQ31_I2C1_EV_Disable;
		NVIC_IRQ32_I2C1_ER_Disable;
		I2C1_CLOCK_Reset();

	}
	else if(I2Cx == I2C2)
	{
		NVIC_IRQ31_I2C2_EV_Disable;
		NVIC_IRQ32_I2C2_ER_Disable;
		I2C2_CLOCK_Reset();


	}


}




/* ================================================================
 * @Fn 				- MCAL_I2C_GPIO_Set_Pins
 * @brief 			- Initializes GPIO Pins to be connected with the selected I2C
 * @param [in] 		- I2Cx : where x can be (1..2 depending on device used) to select I2C peripheral
 * @retval 			- None
 * Note 			- Must open clock for AFIO & GPIO After GPIO Initialization
 * 					- Supported for I2C SM MODE only
 */


void MCAL_I2C_GPIO_Set_Pins(I2C_REGISTERS_t * I2Cx){

	Pin_Config_t PinCfg;

	if(I2Cx == I2C1)
	{
		//PB6 : I2C1_SCL
		//PB7 : I2C1_SDA

		PinCfg.Pin_Num = 6;
		PinCfg.mode = Output_ALF_Open_drain;
		PinCfg.Speed_Output = speed_10;
		MCAL_GPIO_Init(GPIOB, &PinCfg);

		PinCfg.Pin_Num = 7;
		PinCfg.mode = Output_ALF_Open_drain;
		PinCfg.Speed_Output = speed_10;
		MCAL_GPIO_Init(GPIOB, &PinCfg);

	}
	else if(I2Cx == I2C2)
	{

		//PB10 : I2C1_SCL
		//PB11 : I2C1_SDA
		PinCfg.Pin_Num = 10;
		PinCfg.mode = Output_ALF_Open_drain;
		PinCfg.Speed_Output = speed_10;
		MCAL_GPIO_Init(GPIOB, &PinCfg);

		PinCfg.Pin_Num = 11;
		PinCfg.mode = Output_ALF_Open_drain;
		PinCfg.Speed_Output = speed_10;
		MCAL_GPIO_Init(GPIOB, &PinCfg);


	}


}




/* ================================================================
 * @Fn 				- MCAL_I2C_Master_TX
 * @brief 			- Master Send data with I2C
 * @param [in] 		- I2Cx : where x can be (1..2 depending on device used) to select I2C peripheral
 * @param [in] 		- devAddr : slave address
 * @param [in] 		- dataOut : a pointer to the data which will be send
 * @param [in] 		- dataLen : number of data bytes to be Transmitted
 * @param [in] 		- Stop : select send stop bit or not
 * @param [in] 		- Start : select send start or repeated start
 * @retval 			- None
 * Note 			- None
 */


void MCAL_I2C_Master_TX(I2C_REGISTERS_t *I2Cx,uint16_t devAddr,uint8_t * dataOut,uint32_t dataLen , Stop_Condition Stop, Repeated_Start start){

	int i=0;

	// TODO ->..
	// support timeout ( configure timer to work for specific duration then raise interrupt )
	// this interrupt set a flag to 1 --> timer_interrupt(){flag=1}
	//so any while condition should check this flag in addition to any polling condition ( check flag || any polling condition )

	// 1. Set the start bit in the I2C_CR1 register to generate a start condition
	I2C_GenerateSTART(I2Cx, Enable, start);

	// 2. Wait for EV5
	//EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address
	while(!(I2C_GetFlagStatus(I2Cx, EV5)));


	// 3. Send Address
	I2C_SendAddress(I2Cx, devAddr, I2C_Direction_Transmitter);

	// 4. Wait for EV6
	//	EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2
	while(!(I2C_GetFlagStatus(I2Cx, EV6)));


	// 5. Check for TRA,BUSY,MSL,TXE flags

	while(!(I2C_GetFlagStatus(I2Cx, MASTER_BYTE_TRANSMITTING)));

	// 6. Send data
	for(i =0; i<dataLen; i++)
	{
		/* Write in the DR register the data to be sent */
		I2Cx->I2C_DR = dataOut[i];
		// 7. Wait for EV8
		//	  EV8: TxE=1, shift register not empty, .data register empty, cleared by writing DR register
		while(!(I2C_GetFlagStatus(I2Cx, EV8)));
	}


	if(Stop == With_Stop)
	{
		//8. Send stop condition
		I2C_GenerateSTOP(I2Cx, Enable);
	}
}

/* ================================================================
 * @Fn 				- MCAL_I2C_Master_RX
 * @brief 			- Master Receive data with I2C
 * @param [in] 		- I2Cx : where x can be (1..2 depending on device used) to select I2C peripheral
 * @param [in] 		- devAddr : slave address
 * @param [in] 		- dataOut : a pointer to the data which will be send
 * @param [in] 		- dataOut : number of data bytes to be Received
 * @param [in] 		- Stop : select send stop bit or not
 * @param [in] 		- Start : select send start or repeated start
 * @retval 			- None
 * Note 			- None
 */
void MCAL_I2C_Master_RX(I2C_REGISTERS_t *I2Cx,uint16_t devAddr,uint8_t * dataOut,uint32_t dataLen , Stop_Condition Stop, Repeated_Start start){


	uint8_t i =0;
	uint8_t index = I2Cx==I2C1?  I2C1_INDEX: I2C2_INDEX;

	// 1. Set the start bit in the I2C_CR1 register to generate a start condition
	I2C_GenerateSTART(I2Cx, Enable, start);

	// 2. Wait for EV5
	//EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address
	while(!(I2C_GetFlagStatus(I2Cx, EV5)));


	// 3. Send Address
	I2C_SendAddress(I2Cx, devAddr, I2C_Direction_Receiver);

	// 4. Wait for EV6
	//	EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2
	while(!(I2C_GetFlagStatus(I2Cx, EV6)));

	I2C_AcknowledgeConfig(I2Cx, Enable);


	if(dataLen)
	{
		//read data until Len becomes zero
		for( i = dataLen; i>1; i--)
		{
			//wait until RxNE becomes 1
			while(!(I2C_GetFlagStatus(I2Cx, EV7)));
			//Read the data from data register into the buffer
			*dataOut = I2Cx->I2C_DR;
			//Increment the buffer address
			dataOut++;
		}

		I2C_AcknowledgeConfig(I2Cx, Disable);

	}


	if(Stop == With_Stop)
	{
		//8. Send stop condition
		I2C_GenerateSTOP(I2Cx, Enable);
	}

	//Re-enable Acknowledge
	if(Global_I2C_Config[index].I2C_ACK_Control == I2C_Ack_Enable)
	{
		I2C_AcknowledgeConfig(I2Cx, Enable);

	}



}


/* ================================================================
 * @Fn 				- MCAL_I2C_SlaveSendData
 * @brief 			- Slave send data to master using interrupt mechanism
 * @param [in] 		- I2Cx : where x can be (1..2 depending on device used) to select I2C peripheral
 * @param [in] 		- data : slave data to be sent to master
 * @retval 			- None
 * Note 			- Support interrupt mechanism only
 */

void MCAL_I2C_SlaveSendData(I2C_REGISTERS_t *I2Cx,uint8_t data){

	I2Cx->I2C_DR = data;

}


/* ================================================================
 * @Fn 				- MCAL_I2C_SlaveReceiveData
 * @brief 			- Slave Receive data from master using interrupt mechanism
 * @param [in] 		- I2Cx : where x can be (1..2 depending on device used) to select I2C peripheral
 * @retval 			- Received data
 * Note 			- Support interrupt mechanism only
 *
 */
uint8_t MCAL_I2C_SlaveReceiveData(I2C_REGISTERS_t *I2Cx){

	return (uint8_t)I2Cx->I2C_DR;


}



/*
 * =====================================================================================================================
 * 																ISR
 * ======================================================================================================================
 */

//Not supported
void I2C1_ER_IRQHandler(void)
{


}

void I2C1_EV_IRQHandler(void)
{

}

void I2C2_ER_IRQHandler(void)
{


}

void I2C2_EV_IRQHandler(void)
{

}


