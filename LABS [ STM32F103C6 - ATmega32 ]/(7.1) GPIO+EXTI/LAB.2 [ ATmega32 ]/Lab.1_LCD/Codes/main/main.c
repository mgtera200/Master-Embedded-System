#include "lcd.h"

int main(){
	
	LCD_Init();
	//LCD_Send_Character('A');
	LCD_Send_String("Hello in embedded system diploma By:Eng.Mostafa Tera :)");
	LCD_Clear_Screen();
	LCD_Send_String("Numbers Examples:");
	LCD_Display_Real_Number(30.127);
	LCD_Send_String("  ");
	LCD_Display_Number(12);
	LCD_Clear_Screen(); 
	while(1)
	{
	}
	return 0;
}
