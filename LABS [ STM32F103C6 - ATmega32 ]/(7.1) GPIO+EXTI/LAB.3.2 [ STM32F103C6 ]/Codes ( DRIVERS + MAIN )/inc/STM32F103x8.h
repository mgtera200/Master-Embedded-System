/*
 * STM32F103xx.h
 *
 *  Created on: Oct 31, 2023
 *      Author: Dell
 */

#ifndef INC_STM32F103X8_H_
#define INC_STM32F103X8_H_
//-----------------------------
//Includes
//-----------------------------
#include <stdlib.h>
#include <stdint.h>

//=======================================================================//

//-----------------------------
//Base addresses for Memories
//-----------------------------

#define FLASH_MEMORY	 0x08000000UL
#define SRAM_MEMORY		 0x20000000UL
#define SYSTEM_MEMORY    0x1FFFF000UL

//=======================================================================//


//-----------------------------
//Base addresses for BUS Peripherals
//-----------------------------
#define GPIOA_BASE		0x40010800UL
#define GPIOB_BASE		0x40010C00UL
#define GPIOC_BASE		0x40011000UL
#define GPIOD_BASE		0x40011400UL
#define GPIOE_BASE		0x40011800UL
#define AFIO_BASE		0x40010000UL
#define RCC_BASE		0x40021000UL



//=======================================================================//


//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral registers: GPIO
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct{

	volatile uint32_t GPIOx_CRL;
	volatile uint32_t GPIOx_CRH;
	volatile uint32_t GPIOx_IDR;
	volatile uint32_t GPIOx_ODR;
	volatile uint32_t GPIOx_BSRR;
	volatile uint32_t GPIOx_BRR;
	volatile uint32_t GPIOx_LCKR;

}GPIO_REGISTERS_t;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral registers: RCC
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct{

	volatile uint32_t RCC_CR;
	volatile uint32_t RCC_CFGR;
	volatile uint32_t RCC_CIR;
	volatile uint32_t RCC_APB2RSTR;
	volatile uint32_t RCC_APB1RSTR;
	volatile uint32_t RCC_AHBENR;
	volatile uint32_t RCC_APB2ENR;
	volatile uint32_t RCC_APB1ENR;
	volatile uint32_t RCC_BDCR;


}RCC_REGISTERS_t;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral registers: AFIO
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct{

	volatile uint32_t AFIO_EVCR;
	volatile uint32_t AFIO_MAPR;
	volatile uint32_t AFIO_EXTICR1;
	volatile uint32_t AFIO_EXTICR2;
	volatile uint32_t AFIO_EXTICR3;
	volatile uint32_t AFIO_EXTICR4;
	volatile uint32_t RESERVED0;
	volatile uint32_t AFIO_MAPR2;

}AFIO_REGISTERS_t;




//=======================================================================//

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants: GPIO
//-*-*-*-*-*-*-*-*-*-*-*

#define GPIOA		((GPIO_REGISTERS_t *)GPIOA_BASE)
#define GPIOB		((GPIO_REGISTERS_t *)GPIOB_BASE)
#define GPIOC		((GPIO_REGISTERS_t *)GPIOC_BASE)
#define GPIOD		((GPIO_REGISTERS_t *)GPIOD_BASE)
#define GPIOE		((GPIO_REGISTERS_t *)GPIOE_BASE)


//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants: AFIO
//-*-*-*-*-*-*-*-*-*-*-*
#define AFIO		((AFIO_REGISTERS_t *)AFIO_BASE)

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants: RCC
//-*-*-*-*-*-*-*-*-*-*-*

#define RCC		((RCC_REGISTERS_t *)RCC_BASE)

//=======================================================================//


//-*-*-*-*-*-*-*-*-*-*-*-
//clock enable Macros:
//-*-*-*-*-*-*-*-*-*-*-*

#define GPIOA_CLOCK_EN()			RCC->RCC_APB2ENR |= (1<<2)
#define GPIOB_CLOCK_EN()			RCC->RCC_APB2ENR |= (1<<3)
#define GPIOC_CLOCK_EN()			RCC->RCC_APB2ENR |= (1<<4)
#define GPIOD_CLOCK_EN()			RCC->RCC_APB2ENR |= (1<<5)
#define GPIOE_CLOCK_EN()			RCC->RCC_APB2ENR |= (1<<6)


//=======================================================================//

//-*-*-*-*-*-*-*-*-*-*-*-
//Generic Macros:
//-*-*-*-*-*-*-*-*-*-*-*


#endif /* INC_STM32F103X8_H_ */
