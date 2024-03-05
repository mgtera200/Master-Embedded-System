/* Eng.TERA */



#include "lcd.h"

Pin_Config_t Pin_config;




void LCD_Kick(void){

	//LCD_CONTROL_PINS &= ~(1<<EN_PIN); //enable pin = 0;
	MCAL_GPIO_WritePin(GPIOA, 10, 1);
	wait_ms(50);
	MCAL_GPIO_WritePin(GPIOA, 10, 0);
}
void LCD_GPIO_init() {
	Pin_config.Pin_Num = RS_SWITCH;
	Pin_config.mode = Output_Push_pull;
	Pin_config.Speed_Output = speed_10;
	MCAL_GPIO_Init(GPIOA, &Pin_config);


	Pin_config.Pin_Num = RW_SWITCH;
	Pin_config.mode = Output_Push_pull;
	Pin_config.Speed_Output = speed_10;
	MCAL_GPIO_Init(GPIOA, &Pin_config);


	Pin_config.Pin_Num = EN_SWITCH;
	Pin_config.mode = Output_Push_pull;
	Pin_config.Speed_Output = speed_10;
	MCAL_GPIO_Init(GPIOA, &Pin_config);


	//============================
	// SET THE NEXT 8 PINS AS OUTPUT
	Pin_config.Pin_Num = 0;
	Pin_config.mode = Output_Push_pull;
	Pin_config.Speed_Output = speed_10;
	MCAL_GPIO_Init(GPIOA, &Pin_config);

	Pin_config.Pin_Num = 1;
	Pin_config.mode = Output_Push_pull;
	Pin_config.Speed_Output = speed_10;
	MCAL_GPIO_Init(GPIOA, &Pin_config);

	Pin_config.Pin_Num = 2;
	Pin_config.mode = Output_Push_pull;
	Pin_config.Speed_Output = speed_10;
	MCAL_GPIO_Init(GPIOA, &Pin_config);

	Pin_config.Pin_Num = 3;
	Pin_config.mode = Output_Push_pull;
	Pin_config.Speed_Output = speed_10;
	MCAL_GPIO_Init(GPIOA, &Pin_config);

	Pin_config.Pin_Num = 4;
	Pin_config.mode = Output_Push_pull;
	Pin_config.Speed_Output = speed_10;
	MCAL_GPIO_Init(GPIOA, &Pin_config);

	Pin_config.Pin_Num = 5;
	Pin_config.mode = Output_Push_pull;
	Pin_config.Speed_Output = speed_10;
	MCAL_GPIO_Init(GPIOA, &Pin_config);

	Pin_config.Pin_Num = 6;
	Pin_config.mode = Output_Push_pull;
	Pin_config.Speed_Output = speed_10;
	MCAL_GPIO_Init(GPIOA, &Pin_config);

	Pin_config.Pin_Num = 7;
	Pin_config.mode = Output_Push_pull;
	Pin_config.Speed_Output = speed_10;
	MCAL_GPIO_Init(GPIOA, &Pin_config);

	MCAL_GPIO_WritePin(LCD_CTRL, EN_SWITCH, 0);
	MCAL_GPIO_WritePin(LCD_CTRL, RS_SWITCH, 0);
	MCAL_GPIO_WritePin(LCD_CTRL, RW_SWITCH, 0);

}

void LCD_Check_Is_Busy(void){
	//  Configure Data pins as an inputs
	Pin_config.Pin_Num = 0;
	Pin_config.mode = Input_floating;
	MCAL_GPIO_Init(GPIOA, &Pin_config);

	Pin_config.Pin_Num = 1;
	Pin_config.mode = Input_floating;
	MCAL_GPIO_Init(GPIOA, &Pin_config);

	Pin_config.Pin_Num = 2;
	Pin_config.mode = Input_floating;
	MCAL_GPIO_Init(GPIOA, &Pin_config);

	Pin_config.Pin_Num = 3;
	Pin_config.mode = Input_floating;
	MCAL_GPIO_Init(GPIOA, &Pin_config);

	Pin_config.Pin_Num = 4;
	Pin_config.mode = Input_floating;
	MCAL_GPIO_Init(GPIOA, &Pin_config);

	Pin_config.Pin_Num = 5;
	Pin_config.mode = Input_floating;
	MCAL_GPIO_Init(GPIOA, &Pin_config);

	Pin_config.Pin_Num = 6;
	Pin_config.mode = Input_floating;
	MCAL_GPIO_Init(GPIOA, &Pin_config);

	Pin_config.Pin_Num = 7;
	Pin_config.mode = Input_floating;
	MCAL_GPIO_Init(GPIOA, &Pin_config);

	// Read mode
	MCAL_GPIO_WritePin(GPIOA, 9, 1);
	// Instruction register is on
	MCAL_GPIO_WritePin(GPIOA, 8, 0);
	LCD_Kick();


	// Write mode
	MCAL_GPIO_WritePin(GPIOA, 9, 0);


}
void LCD_Send_Command(uint16_t command){
	MCAL_GPIO_WritePort(LCD_CTRL, command);
	MCAL_GPIO_WritePin(LCD_CTRL, RW_SWITCH, 0);
	MCAL_GPIO_WritePin(LCD_CTRL, RS_SWITCH, 0);
	wait_ms(1);
	LCD_Kick();


}

void LCD_Send_Character(uint16_t character){

	MCAL_GPIO_WritePort(LCD_CTRL, character);
	MCAL_GPIO_WritePin(LCD_CTRL, RW_SWITCH, 0);
	MCAL_GPIO_WritePin(LCD_CTRL, RS_SWITCH, 1);
	wait_ms(1);
	LCD_Kick();

}

void LCD_Clear_Screen(void){

	LCD_Send_Command(LCD_CLEAR);
}

void LCD_Init(void){

	wait_ms(20);
	LCD_GPIO_init();
	wait_ms(15);
	LCD_Clear_Screen();
	LCD_Send_Command(LCD_FUNCTION_8BIT_2LINES);
	LCD_Send_Command(LCD_ENTRY_MODE);
	LCD_Send_Command(LCD_BEGIN_AT_FIRST_ROW);
	LCD_Send_Command(LCD_DISP_ON_CURSOR_BLINK);
}
void LCD_Send_String(const char* string){

	int count =0;
	while(1){
		if(count == 16)//First line end reached
		{
			LCD_Send_Command(LCD_BEGIN_AT_SECOND_ROW);
		}
		if(count == 32)//Second line end reached
		{
			LCD_Clear_Screen();
			LCD_Send_Command(LCD_BEGIN_AT_FIRST_ROW);
			count=0;
		}
		LCD_Send_Character(*string);
		string++;
		count++;
		if(*string == '\0')//End of the string reached
		{
			break;//stop
		}
	}
}
void LCD_Display_Number(int Number){

	char str[20];
	sprintf(str,"%d",Number);//Converting integer to string
	LCD_Send_String(str);

}
void LCD_Display_Real_Number(float Number){
	char str[20];
	sprintf(str,"%.1f",Number);//Converting integer to string
	LCD_Send_String(str);
}



