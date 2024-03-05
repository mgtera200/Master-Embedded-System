/*
 * GPIO_DRIVER.h
 *
 * ENG-TERA
 */

#ifndef INC_GPIO_DRIVER_H_
#define INC_GPIO_DRIVER_H_
//-----------------------------
//Includes
//-----------------------------
#include "STM32F103x8.h"



//-----------------------------
//User type definitions (structures)
//-----------------------------
typedef struct{
	uint32_t Pin_Num;      		//Should be from 0 >> 15
	uint32_t mode;				//@ref Pin_Mode
	uint32_t Speed_Output;		//@ref Output_speed

}Pin_Config_t;


//-----------------------------
//Macros Configuration References
//-----------------------------


//@ref Pin_Mode
#define Input_Analog					0x0000UL
#define Input_floating					0x0001UL
#define Input_PullUp					0x0002UL
#define Input_PullDown					0x0003UL
#define Output_Push_pull				0x0004UL
#define Output_Open_drain				0x0005UL
#define Output_ALF_Push_pull			0x0006UL
#define Output_ALF_Open_drain			0x0007UL
#define Input_AF						0x0008UL




//@ref Output_speed
#define speed_10						0x0001UL
#define speed_2							0x0002UL
#define speed_50						0x0003UL




/*
 * ===============================================
 * APIs Supported by "MCAL GPIO DRIVER"
 * ===============================================
 */

void			MCAL_GPIO_Init(GPIO_REGISTERS_t *GPIOx, Pin_Config_t * Pin_config_s);
void			MCAL_GPIO_DeInit(GPIO_REGISTERS_t *GPIOx,uint8_t Pin_num);
void			MCAL_GPIO_WritePin(GPIO_REGISTERS_t *GPIOx,uint32_t Pin_Num,uint32_t Value);
unsigned char	MCAL_GPIO_ReadPin(GPIO_REGISTERS_t *GPIOx,uint32_t Pin_Num);
void			MCAL_GPIO_WritePort(GPIO_REGISTERS_t *GPIOx, uint32_t Value);
uint32_t		MCAL_GPIO_ReadPort(GPIO_REGISTERS_t *GPIOx);
void			MCAL_GPIO_TogglePin(GPIO_REGISTERS_t *GPIOx,uint8_t Pin_Num);




#endif /* INC_GPIO_DRIVER_H_ */
