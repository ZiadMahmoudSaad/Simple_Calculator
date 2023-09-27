################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Stm32F103C6_Drivers/MCAL/GPIO/subdir.mk
-include Stm32F103C6_Drivers/MCAL/EXTI/subdir.mk
-include Stm32F103C6_Drivers/HAL/LCD_DRIVER/subdir.mk
-include Stm32F103C6_Drivers/HAL/KEYPAD_DRIVER/subdir.mk
-include Startup/subdir.mk
-include Src/subdir.mk
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
Simple_Calculator.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Simple_Calculator.list \

OBJCOPY_HEX += \
Simple_Calculator.hex \

OBJCOPY_BIN += \
Simple_Calculator.bin \


# All Target
all: Simple_Calculator.elf secondary-outputs

# Tool invocations
Simple_Calculator.elf: $(OBJS) $(USER_OBJS) D:\Projects\Simple_Calculator\STM32F103C6TX_FLASH.ld
	arm-none-eabi-gcc -gdwarf-2 -o "Simple_Calculator.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"D:\Projects\Simple_Calculator\STM32F103C6TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Simple_Calculator.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Simple_Calculator.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Simple_Calculator.list"
	@echo 'Finished building: $@'
	@echo ' '

Simple_Calculator.hex: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "Simple_Calculator.hex"
	@echo 'Finished building: $@'
	@echo ' '

Simple_Calculator.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "Simple_Calculator.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
