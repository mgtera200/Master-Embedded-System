/*
 * lcd.h
 *
 * Created: 11/10/2023 1:40:56 AM
 *  Author: Dell
 */ 


#ifndef LCD_H_
#define LCD_H_

#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "GPIO_DRIVER.h"
#include "STM32F103x8.h"
#define F_CPU 1000000UL



#define LCD_CTRL GPIOA
#define RS_SWITCH 8
#define RW_SWITCH 9
#define EN_SWITCH 10
#define DATA_SHIFT         4

// Hexadecimal instructions to be written to the instruction register
#define LCD_FUNCTION_8BIT_2LINES     (0x38)
#define LCD_FUNCTION_4BIT_2LINES     (0x28)
#define LCD_MOVE_DISP_RIGHT          (0x1C)
#define LCD_MOVE_DISP_LEFT           (0x18)
#define LCD_MOVE_CURSOR_RIGHT        (0x14)
#define LCD_MOVE_CURSOR_LEFT         (0x10)
#define LCD_DISP_OFF                 (0x08)
#define LCD_DISP_ON_CURSOR           (0x0E)
#define LCD_DISP_ON_CURSOR_BLINK     (0x0F)
#define LCD_DISP_ON_BLINK            (0x0D)
#define LCD_DISP_ON                  (0x0C)
#define LCD_ENTRY_DEC                (0x04)
#define LCD_ENTRY_DEC_SHIFT          (0x05)
#define LCD_ENTRY_INC                (0x06)
#define LCD_ENTRY_INC_SHIFT          (0x07)
#define LCD_BEGIN_AT_FIRST_ROW       (0x80)
#define LCD_BEGIN_AT_SECOND_ROW      (0xC0)
#define LCD_CLEAR                    (0x01)
#define LCD_ENTRY_MODE               (0x06)


void wait_ms(uint32_t time);
void LCD_Init(void);
void LCD_Clear_Screen(void);
void LCD_Send_Command(uint16_t command);
void LCD_Send_Character(uint16_t character);
void LCD_Send_String(const char* string);
void LCD_Kick(void);
void LCD_Check_Is_Busy(void);
void LCD_gotoXY(uint8_t line, uint8_t position);
void LCD_Display_Number(int Number);
void LCD_Display_Real_Number(float Number);
void LCD_SEND_A_Command_4mode(unsigned char command);


#endif /* LCD_H_ */
