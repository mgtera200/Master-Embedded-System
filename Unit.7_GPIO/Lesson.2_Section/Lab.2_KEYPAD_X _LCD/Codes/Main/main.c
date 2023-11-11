#include "lcd.h"
#include "keypad.h"
int main(){
	
	char key_pressed;
	LCD_Init();
	keypad_init();
	
	
	//LCD_Send_Character('A');
	/* LCD_Send_String("Hello in embedded system diploma By:Eng.Mostafa Tera :)");
	LCD_Clear_Screen();
	LCD_Send_String("Numbers Examples:");
	LCD_Display_Real_Number(30.127);
	LCD_Send_String("  ");
	LCD_Display_Number(12);
	LCD_Clear_Screen(); */
	
	
	
	while(1)
	{
		key_pressed = keypad_GETKEY();
		switch(key_pressed)
		{
			case 'A':
				break;
			case '?':
				LCD_Clear_Screen();
				break;
			default:
				LCD_Send_Character(key_pressed);
		}
	}
	return 0;
}
