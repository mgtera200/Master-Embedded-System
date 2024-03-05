################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include STM32F103C6_DRIVERS/USART/subdir.mk
-include STM32F103C6_DRIVERS/SPI/subdir.mk
-include STM32F103C6_DRIVERS/RCC\ (\ DEMO\ )/subdir.mk
-include STM32F103C6_DRIVERS/I2C/subdir.mk
-include STM32F103C6_DRIVERS/GPIO/subdir.mk
-include STM32F103C6_DRIVERS/EXTI/subdir.mk
-include HAL/LCD/subdir.mk
-include HAL/KEYPAD/subdir.mk
-include HAL/I2C_Slave_EEPROM/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Drivers1.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Drivers1.list \

OBJCOPY_BIN += \
Drivers1.bin \


# All Target
all:
	+@make --no-print-directory main-build && make --no-print-directory post-build

# Main-build Target
main-build: Drivers1.elf secondary-outputs

# Tool invocations
Drivers1.elf: $(OBJS) $(USER_OBJS) F:\Mostafa\Drivers\Drivers\STM32F103C6TX_FLASH.ld
	arm-none-eabi-gcc  -gdwarf-2 -o "Drivers1.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"F:\Mostafa\Drivers\Drivers\STM32F103C6TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Drivers1.map" -Wl,--gc-sections -static -L"F:\Mostafa\Drivers\Drivers\HAL\inc" -L"F:\Mostafa\Drivers\Drivers\STM32F103C6_DRIVERS\inc" -L"F:\Mostafa\Drivers\Drivers\Inc" --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Drivers1.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Drivers1.list"
	@echo 'Finished building: $@'
	@echo ' '

Drivers1.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "Drivers1.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

post-build:
	arm-none-eabi-objcopy -O ihex Drivers1.elf Drivers1.hex
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
