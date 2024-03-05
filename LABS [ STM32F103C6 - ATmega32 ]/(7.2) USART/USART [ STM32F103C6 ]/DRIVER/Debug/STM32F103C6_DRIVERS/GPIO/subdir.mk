################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../STM32F103C6_DRIVERS/GPIO/GPIO_DRIVER.c 

OBJS += \
./STM32F103C6_DRIVERS/GPIO/GPIO_DRIVER.o 

C_DEPS += \
./STM32F103C6_DRIVERS/GPIO/GPIO_DRIVER.d 


# Each subdirectory must supply rules for building sources it contributes
STM32F103C6_DRIVERS/GPIO/GPIO_DRIVER.o: ../STM32F103C6_DRIVERS/GPIO/GPIO_DRIVER.c
	arm-none-eabi-gcc  -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I"F:/Mostafa/Embedded Course/Master-Embedded-System/[Unit.8] MCU Interfacing/STM32_USART_DRIVER/STM_IDE_Project/HAL/inc" -I"F:/Mostafa/Embedded Course/Master-Embedded-System/[Unit.8] MCU Interfacing/STM32_USART_DRIVER/STM_IDE_Project/STM32F103C6_DRIVERS/inc" -I../Inc -I"F:/Mostafa/Embedded Course/Master-Embedded-System/[Unit.8] MCU Interfacing/STM32_USART_DRIVER/STM_IDE_Project/CMSIS_V5" -I"F:/Mostafa/Embedded Course/Master-Embedded-System/[Unit.8] MCU Interfacing/STM32_USART_DRIVER/STM_IDE_Project/TERA_RTOS/RTOS_inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"STM32F103C6_DRIVERS/GPIO/GPIO_DRIVER.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

