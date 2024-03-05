/*
 * SPI_DRIVER.h
 *
 *  Created on: Dec 9, 2023
 *      Author: Eng.TERA
 */

#ifndef INC_I2C_DRIVER_H_
#define INC_I2C_DRIVER_H_


//-----------------------------------------
//-------<< INCLUDES >>--------------------
//-----------------------------------------
#include "STM32F103x8.h"



//-----------------------------------------
//-------<< Generic Macros >>--------------
//-----------------------------------------

#define I2C_EVENT_MASTER_BYTE_TRANSMITTING			((uint32_t)0x00070080)

//-----------------------------------------
//-------<< Generic Typedef >>--------------
//-----------------------------------------


typedef enum{

	With_Stop,
	without_Stop

}Stop_Condition;

typedef enum{

	Start,
	repeated_start

}Repeated_Start;

typedef enum{

	Enable,
	Disable

}FunctionalState;

typedef enum{

	RESET,
	SET

}FlagStatus;


typedef enum{

	I2C_FLAG_BUSY,
	EV5, //EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address
	EV6, //EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2
	EV7, //EV7: RxNE=1 cleared by reading DR register
	EV8, //EV8: TxE=1, shift register not empty, .data register empty, cleared by writing DR register
	EV8_1,//EV8_1: TxE=1, shift register empty, data register empty, write Data1 in DR.
	MASTER_BYTE_TRANSMITTING = ((uint32_t)0x00070080)


}Status;


typedef enum{

	I2C_Direction_Transmitter,
	I2C_Direction_Receiver

}I2C_Direction;




/*
 * =====================================================================================================================
 * 													User type definitions (structures)
 * ======================================================================================================================
 */

struct S_I2C_Slave_Device_Address{

	uint16_t Enable_Dual_ADD; //1-Enable 0-Disable
	uint16_t Primary_slave_address;
	uint16_t Secondary_slave_address;
	uint32_t I2C_Addressing_Slave_mode;//@I2C_Addressing_Slave
};

typedef enum{

	I2C_EV_STOP,
	I2C_ERROR_AF,
	I2C_EV_ADDR_Matched,
	I2C_EV_DATA_REQ, //The App layer should SEND the data (I2C_SlaveSendData ) in this state
	I2C_EV_DATA_RCV //The App layer should READ the data (I2C_SlaveReceiveData ) in this state



}Slave_State;


typedef struct {

	uint32_t 								I2C_ClockSpeed;		// < Specifies The clock frequency >
																// < This parameter must be set to @I2C_SCLK_

	uint32_t								StretchMode; 		//@ref I2C_StretchMode

	uint32_t								I2C_Mode;			// < Specifies The I2C mode >
																// < This parameter must be set to @I2C_Mode

	struct S_I2C_Slave_Device_Address		I2C_Slave_Address;

	uint32_t								I2C_ACK_Control; 		// < Enable or disable acknowledge >
																	// < This parameter must be set to @I2C_Ack_
	uint32_t								General_Call_Address_Detection;	//@I2C_ENGC

	void (* P_Slave_Event_CallBack)(Slave_State state);

}I2C_InitTypeDef;

/*
 * =====================================================================================================================
 * 													Macros Configuration References
 * ======================================================================================================================
 */


// @I2C_SCLK_

// Standard Speed ( up to 100 KHZ )
// Fast Speed ( up to 400 KHZ )
// To configure the clock before enabling the peripheral
// -- I2C_CR2.FREQ[5:0]: Peripheral clock frequency
//• Configure the clock control registers
//  T(high) = CCR * T(pclk1)
//  SM or FM
//• Configure the rise time register -->I2C_TRISE

#define I2C_SCLK_SM_50K				(50000U)
#define I2C_SCLK_SM_100K			(100000U)
#define I2C_SCLK_FM_200K			(200000U) // Fast mode not supported yet
#define I2C_SCLK_FM_400K			(400000U) // Fast mode not supported yet


//@I2C_StretchMode
//Bit 7 NOSTRETCH: Clock stretching disable (Slave mode)
//0: Clock stretching enabled
//1: Clock stretching disabled

#define I2C_StretchMode_Enable		0x0ul
#define I2C_StretchMode_Disable		I2C_CR1_NOSTRETCH


//@I2C_Mode
//I2C_CR1
//Bit 1 SMBUS: SMBus mode
//0: I2C mode
//1: SMBus mode

#define I2C_Mode_I2C				0x00ul
#define I2C_Mode_SMBus				I2C_CR1_SMBUS


//@I2C_Addressing_Slave
//I2C_OAR1.ADDMODE
//Bit 15 ADDMODE Addressing mode (slave mode)
//0: 7-bit slave address (10-bit address not acknowledged)
//1: 10-bit slave address (7-bit address not acknowledged)

#define I2C_Addressing_Slave_mode_7Bit		0x0ul
#define I2C_Addressing_Slave_mode_10Bit		(uint16_t)(1<<15)

//@I2C_Ack_
//I2C_CR1
//Bit 10 ACK: Acknowledge enable
//This bit is set and cleared by software and cleared by hardware when PE=0.
//0: No acknowledge returned
//1: Acknowledge returned after a byte is received (matched address or data)

#define I2C_Ack_Enable 					I2C_CR1_ACK_Msk
#define I2C_Ack_Disable					0x00ul


//@I2C_ENGC
//Bit 6 ENGC: General call enable
//0: General call disabled. Address 00h is NACKed.
//1: General call enabled. Address 00h is ACKed.

#define I2C_ENGC_Enable 		I2C_CR1_ENGC
#define I2C_ENGC_Disable 		0x00ul


/*
 * =====================================================================================================================
 * 													APIs Supported by "MCAL I2C DRIVER"
 * ======================================================================================================================
 */
void MCAL_I2C_Init(I2C_REGISTERS_t * I2Cx, I2C_InitTypeDef * I2C_InitStruct);
void MCAL_I2C_DInit(I2C_REGISTERS_t * I2Cx);
void MCAL_I2C_GPIO_Set_Pins(I2C_REGISTERS_t * I2Cx);

//Master Polling Mechanism
void MCAL_I2C_Master_TX(I2C_REGISTERS_t *I2Cx,uint16_t devAddr,uint8_t * dataOut,uint32_t dataLen , Stop_Condition Stop, Repeated_Start start);
void MCAL_I2C_Master_RX(I2C_REGISTERS_t *I2Cx,uint16_t devAddr,uint8_t * dataOut,uint32_t dataLen , Stop_Condition Stop, Repeated_Start start);

//Slave Interrupt Mechanism

void MCAL_I2C_SlaveSendData(I2C_REGISTERS_t *I2Cx,uint8_t data);
uint8_t MCAL_I2C_SlaveReceiveData(I2C_REGISTERS_t *I2Cx);





//Generic APIs
void I2C_GenerateSTART(I2C_REGISTERS_t *I2Cx,FunctionalState NewState , Repeated_Start start);
FlagStatus I2C_GetFlagStatus(I2C_REGISTERS_t *I2Cx,Status flag);
void I2C_SendAddress(I2C_REGISTERS_t *I2Cx,uint16_t Address , I2C_Direction Direction);
void I2C_GenerateSTOP(I2C_REGISTERS_t *I2Cx,FunctionalState NewState);
void I2C_AcknowledgeConfig(I2C_REGISTERS_t *I2Cx,FunctionalState NewState);








#endif /* INC_I2C_DRIVER_H_ */
