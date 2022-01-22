################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MCAL/subdir.mk
-include ECUAL/subdir.mk
-include APP/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
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
LSS += \
TEMP_SHOW_ON_LCD.lss \

FLASH_IMAGE += \
TEMP_SHOW_ON_LCD.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: TEMP_SHOW_ON_LCD.elf secondary-outputs

# Tool invocations
TEMP_SHOW_ON_LCD.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,TEMP_SHOW_ON_LCD.map -mmcu=atmega32 -o "TEMP_SHOW_ON_LCD.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

TEMP_SHOW_ON_LCD.lss: TEMP_SHOW_ON_LCD.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S TEMP_SHOW_ON_LCD.elf  >"TEMP_SHOW_ON_LCD.lss"
	@echo 'Finished building: $@'
	@echo ' '

TEMP_SHOW_ON_LCD.hex: TEMP_SHOW_ON_LCD.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex TEMP_SHOW_ON_LCD.elf  "TEMP_SHOW_ON_LCD.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: TEMP_SHOW_ON_LCD.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 TEMP_SHOW_ON_LCD.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) TEMP_SHOW_ON_LCD.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
