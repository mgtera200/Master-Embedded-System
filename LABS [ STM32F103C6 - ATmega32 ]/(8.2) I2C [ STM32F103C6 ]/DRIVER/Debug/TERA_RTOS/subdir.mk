################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../TERA_RTOS/CortexMx_OS_Porting.c \
../TERA_RTOS/Scheduler.c \
../TERA_RTOS/TERA_RTOS_FIFO.c 

OBJS += \
./TERA_RTOS/CortexMx_OS_Porting.o \
./TERA_RTOS/Scheduler.o \
./TERA_RTOS/TERA_RTOS_FIFO.o 

C_DEPS += \
./TERA_RTOS/CortexMx_OS_Porting.d \
./TERA_RTOS/Scheduler.d \
./TERA_RTOS/TERA_RTOS_FIFO.d 


# Each subdirectory must supply rules for building sources it contributes
TERA_RTOS/CortexMx_OS_Porting.o: ../TERA_RTOS/CortexMx_OS_Porting.c
	arm-none-eabi-gcc  -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I"F:/Mostafa/Drivers/Drivers/HAL/inc" -I"F:/Mostafa/Drivers/Drivers/STM32F103C6_DRIVERS/inc" -I../Inc -I"F:/Mostafa/Drivers/Drivers/CMSIS_V5" -I"F:/Mostafa/Drivers/Drivers/TERA_RTOS/RTOS_inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"TERA_RTOS/CortexMx_OS_Porting.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
TERA_RTOS/Scheduler.o: ../TERA_RTOS/Scheduler.c
	arm-none-eabi-gcc  -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I"F:/Mostafa/Drivers/Drivers/HAL/inc" -I"F:/Mostafa/Drivers/Drivers/STM32F103C6_DRIVERS/inc" -I../Inc -I"F:/Mostafa/Drivers/Drivers/CMSIS_V5" -I"F:/Mostafa/Drivers/Drivers/TERA_RTOS/RTOS_inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"TERA_RTOS/Scheduler.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
TERA_RTOS/TERA_RTOS_FIFO.o: ../TERA_RTOS/TERA_RTOS_FIFO.c
	arm-none-eabi-gcc  -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I"F:/Mostafa/Drivers/Drivers/HAL/inc" -I"F:/Mostafa/Drivers/Drivers/STM32F103C6_DRIVERS/inc" -I../Inc -I"F:/Mostafa/Drivers/Drivers/CMSIS_V5" -I"F:/Mostafa/Drivers/Drivers/TERA_RTOS/RTOS_inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"TERA_RTOS/TERA_RTOS_FIFO.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

