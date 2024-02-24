################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/SERVO_MOTOR/Servo_Motor.c 

OBJS += \
./HAL/SERVO_MOTOR/Servo_Motor.o 

C_DEPS += \
./HAL/SERVO_MOTOR/Servo_Motor.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/SERVO_MOTOR/Servo_Motor.o: ../HAL/SERVO_MOTOR/Servo_Motor.c
	arm-none-eabi-gcc  -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I"F:/Mostafa/Embedded Course/Master-Embedded-System/[Unit.8] MCU Interfacing/STM32_USART_DRIVER/STM_IDE_Project/HAL/inc" -I"F:/Mostafa/Embedded Course/Master-Embedded-System/[Unit.8] MCU Interfacing/STM32_USART_DRIVER/STM_IDE_Project/STM32F103C6_DRIVERS/inc" -I../Inc -I"F:/Mostafa/Embedded Course/Master-Embedded-System/[Unit.8] MCU Interfacing/STM32_USART_DRIVER/STM_IDE_Project/CMSIS_V5" -I"F:/Mostafa/Embedded Course/Master-Embedded-System/[Unit.8] MCU Interfacing/STM32_USART_DRIVER/STM_IDE_Project/TERA_RTOS/RTOS_inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"HAL/SERVO_MOTOR/Servo_Motor.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

