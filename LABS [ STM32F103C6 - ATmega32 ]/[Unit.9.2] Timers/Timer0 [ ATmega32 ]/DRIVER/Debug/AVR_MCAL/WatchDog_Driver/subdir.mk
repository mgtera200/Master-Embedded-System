################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../AVR_MCAL/WatchDog_Driver/WatchDog.c 

OBJS += \
./AVR_MCAL/WatchDog_Driver/WatchDog.o 

C_DEPS += \
./AVR_MCAL/WatchDog_Driver/WatchDog.d 


# Each subdirectory must supply rules for building sources it contributes
AVR_MCAL/WatchDog_Driver/%.o: ../AVR_MCAL/WatchDog_Driver/%.c AVR_MCAL/WatchDog_Driver/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"C:\Users\Dell\eclipse-workspace\AVR_Project2\AVR_MCAL\inc" -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


