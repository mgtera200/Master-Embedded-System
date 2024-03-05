/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Basem Said
 * @brief          : Main program body
 ******************************************************************************
 */

#include <stdint.h>

// register address
typedef volatile unsigned int  vuint32_t ;

#define RCC_BASE   0x40021000
#define PortA_BASE 0x40010800

#define RCC_APB2ENR   *(volatile uint32_t *) (RCC_BASE   + 0x18)
#define GPIO_CRH      *(volatile uint32_t *) (PortA_BASE + 0x04)
#define GPIO_ODR      *(volatile uint32_t *) (PortA_BASE + 0x0C)

typedef union
{
	vuint32_t allfields;
	struct
	{
		vuint32_t reserved:13;
		vuint32_t pin13:1;
	}pin;
}R_ODR_t;

volatile R_ODR_t*  R_ODR =  (volatile R_ODR_t*) (PortA_BASE + 0x0C);

int main(void)
{

	RCC_APB2ENR |=1<<2;     // Enable RCC clock
	GPIO_CRH &=0xff0fffff;  // make bits from 20 to 24 zero
	GPIO_CRH |=0x00200000;  // write 2 on bits from 20 to 24

	while(1)
	{
		// GPIO_ODR |= 1<<13;  //set bit 13
		R_ODR->pin.pin13=1;
		for(int i=0;i<5000; i++); //delay
		// GPIO_ODR &= ~(1<<13);  //clear bit 13
		R_ODR->pin.pin13=0;
		for(int i=0;i<5000; i++);  //delay
	}

	return 0;
}
