/*
 * Servo_Motor.h
 *
 *  ENG.TERA
 */



#ifndef SERVO_MOTOR_SERVO_MOTOR_H_
#define SERVO_MOTOR_SERVO_MOTOR_H_

#include "STM32F103x8.h"
#include "GPIO_DRIVER.h"
#include "Timer.h"

//Direction of motion
#define UP   1
#define Down 2

void Servo1_Entry_Gate_Init(void);
void Servo1_Entry_Gate(uint8_t Direction);

void Servo2_Exit_Gate_Init(void);
void Servo2_Exit_Gate(uint8_t Direction);





#endif /* SERVO_MOTOR_SERVO_MOTOR_H_ */
