################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/HAL/KeyPad/KPD_program.c 

OBJS += \
./Src/HAL/KeyPad/KPD_program.o 

C_DEPS += \
./Src/HAL/KeyPad/KPD_program.d 


# Each subdirectory must supply rules for building sources it contributes
Src/HAL/KeyPad/%.o Src/HAL/KeyPad/%.su Src/HAL/KeyPad/%.cyclo: ../Src/HAL/KeyPad/%.c Src/HAL/KeyPad/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-HAL-2f-KeyPad

clean-Src-2f-HAL-2f-KeyPad:
	-$(RM) ./Src/HAL/KeyPad/KPD_program.cyclo ./Src/HAL/KeyPad/KPD_program.d ./Src/HAL/KeyPad/KPD_program.o ./Src/HAL/KeyPad/KPD_program.su

.PHONY: clean-Src-2f-HAL-2f-KeyPad

