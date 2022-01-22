################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ECUAL/keypad_program.c \
../ECUAL/lcd_program.c 

OBJS += \
./ECUAL/keypad_program.o \
./ECUAL/lcd_program.o 

C_DEPS += \
./ECUAL/keypad_program.d \
./ECUAL/lcd_program.d 


# Each subdirectory must supply rules for building sources it contributes
ECUAL/%.o: ../ECUAL/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


