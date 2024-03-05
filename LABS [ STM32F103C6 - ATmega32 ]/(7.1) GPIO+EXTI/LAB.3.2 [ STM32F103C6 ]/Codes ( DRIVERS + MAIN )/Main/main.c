

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif
/* Eng.TERA */
//YARABBBB

#include "STM32F103x8.h"
#include "GPIO_DRIVER.h"
#include "lcd.h"
#include "keypad.h"

#define ZERO 0x01
#define ONE 0x79
#define TWO 0x24
#define THREE 0x30
#define FOUR 0x4C
#define FIVE 0x12
#define SIX 0x02
#define SEVEN 0x19
#define EIGHT 0x00
#define NINE 0x10

extern Pin_Config_t Pin_config;


void clock_init() {
	//Enable clock GPIOA
	GPIOA_CLOCK_EN();
	//Enable clock GPIOB
	GPIOB_CLOCK_EN();
}
void GPIO_7SEG_init() {


	Pin_config.Pin_Num = 9;
	Pin_config.mode = Output_Push_pull;
	Pin_config.Speed_Output = speed_10;
	MCAL_GPIO_Init(GPIOB, &Pin_config);

	Pin_config.Pin_Num = 10;
	Pin_config.mode = Output_Push_pull;
	Pin_config.Speed_Output = speed_10;
	MCAL_GPIO_Init(GPIOB, &Pin_config);

	Pin_config.Pin_Num = 11;
	Pin_config.mode = Output_Push_pull;
	Pin_config.Speed_Output = speed_10;
	MCAL_GPIO_Init(GPIOB, &Pin_config);

	Pin_config.Pin_Num = 12;
	Pin_config.mode = Output_Push_pull;
	Pin_config.Speed_Output = speed_10;
	MCAL_GPIO_Init(GPIOB, &Pin_config);

	Pin_config.Pin_Num = 13;
	Pin_config.mode = Output_Push_pull;
	Pin_config.Speed_Output = speed_10;
	MCAL_GPIO_Init(GPIOB, &Pin_config);


	Pin_config.Pin_Num = 14;
	Pin_config.mode = Output_Push_pull;
	Pin_config.Speed_Output = speed_10;
	MCAL_GPIO_Init(GPIOB, &Pin_config);

	Pin_config.Pin_Num = 15;
	Pin_config.mode = Output_Push_pull;
	Pin_config.Speed_Output = speed_10;
	MCAL_GPIO_Init(GPIOB, &Pin_config);

}


int main(void) {
unsigned char key_pressed;
unsigned char LCD_DISPLAY [11] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};
unsigned char DISPLAY [11] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, ZERO};
clock_init();
	LCD_Init();
	GPIO_7SEG_init();
	LCD_Send_String("HEY");
	wait_ms(30);
	LCD_Clear_Screen();
	for (unsigned char i = 0; i < 11; i++) {
		LCD_Send_Character(LCD_DISPLAY[i]);
		MCAL_GPIO_WritePort(GPIOB, DISPLAY[i] << 9); /* write data on to the 7SEG port */
		wait_ms(100);
		/* wait for 1 second */
	}
	LCD_Clear_Screen();
keypad_init();
	LCD_Send_String("Keypad is ready");
	wait_ms(15);
	LCD_Clear_Screen();

	while (1) {

		key_pressed = keypad_GETKEY();
		switch (key_pressed) {
		case 'A':
			break;
		case '?':
			LCD_Clear_Screen();
			break;
		default:
			LCD_Send_Character(key_pressed);
			break;
		}
	}
}
