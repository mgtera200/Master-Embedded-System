/* Eng.TERA  */


#include "lcd.h"
#include "keypad.h"
#include <stdlib.h>
#include <string.h>


int main(){
	float sum2;
	int sum;	
	int i=0;
	int flag=0;
	int count=0;
	char key_pressed;
	char num1[20]={0};
	char num2[20]={0};
	LCD_Init();
	keypad_init();
	while(1)
	{
		key_pressed = keypad_GETKEY();
		switch(key_pressed)
		{
			case 'A':
				break;
				
			case '*':{							/* When we press * its sets flag and copy the left side number(num1) to num2 array
												   then we reset num1 to zero to be ready to hold the right side number */
				LCD_Send_Character('*');
				flag=2;
				strcpy(num2,num1);
				for(i=0; i<count; i++){
					num1[i] = 0;
				}
				count =0;
				break;
			}
			case '/':{							/* When we press / its sets flag and copy the left side number(num1) to num2 array
												   then we reset num1 to zero to be ready to hold the right side number */
				LCD_Send_Character('/');
				flag=3;
				strcpy(num2,num1);
				for(i=0; i<count; i++){
					num1[i] = 0;
				}
				count =0;
				break;
			}
			
			case '-':{							/* When we press - its sets flag and copy the left side number(num1) to num2 array
												   then we reset num1 to zero to be ready to hold the right side number */
				LCD_Send_Character('-');
				flag=4;
				strcpy(num2,num1);
				for(i=0; i<count; i++){
					num1[i] = 0;
				}
				count =0;
				break;
			}
			
			
			case '+':{							/* When we press / its sets flag and copy the left side number(num1) to num2 array
												 then we reset num1 to zero to be ready to hold the right side number */
				LCD_Send_Character('+');
				flag=1;
				strcpy(num2,num1);
				for(i=0; i<count; i++){
					num1[i] = 0;
				}
				count =0;
				break;
				}
			case '=':{							/* When we press = it prints " = " then check which operation we want to make
												   depending on the flag then reset the flag to be ready for the next operation */
				LCD_Send_Character('=');
				if(flag==1){
					sum= atoi(num1)+atoi(num2);
					LCD_Display_Number(sum);
					flag=0;
					break;
				}
				else if(flag==2){
					sum= atoi(num1)*atoi(num2);
					LCD_Display_Number(sum);
					flag=0;
					break;
				}
				else if(flag==3){
					sum2= atof(num2)/atof(num1);
					LCD_Display_Real_Number(sum2);
					flag=0;
					break;
			}
				else if(flag==4){
					sum= atoi(num2) - atoi(num1);
					LCD_Display_Number(sum);
					flag=0;
					break;
					}
				break;
			}
				
			case '?':							/* When we press on\off its clears the screen and reset num1 and num2 and count to zero
												   to be ready for the next operation */
			{
				LCD_Clear_Screen();	
				for(i=0; i<count; i++){
					num1[i] = 0;
					num2[i] = 0;
				}
				count=0;
				flag=0;
				sum=0;
				break;
				}
			default:
				num1[count]=key_pressed;
				count++;
				LCD_Send_Character(key_pressed);
		}
	}
	return 0;
}
