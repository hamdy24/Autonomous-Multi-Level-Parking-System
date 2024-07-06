################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/HAL/DC_Motor/DC_Motor.c 

OBJS += \
./Src/HAL/DC_Motor/DC_Motor.o 

C_DEPS += \
./Src/HAL/DC_Motor/DC_Motor.d 


# Each subdirectory must supply rules for building sources it contributes
Src/HAL/DC_Motor/%.o Src/HAL/DC_Motor/%.su Src/HAL/DC_Motor/%.cyclo: ../Src/HAL/DC_Motor/%.c Src/HAL/DC_Motor/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-HAL-2f-DC_Motor

clean-Src-2f-HAL-2f-DC_Motor:
	-$(RM) ./Src/HAL/DC_Motor/DC_Motor.cyclo ./Src/HAL/DC_Motor/DC_Motor.d ./Src/HAL/DC_Motor/DC_Motor.o ./Src/HAL/DC_Motor/DC_Motor.su

.PHONY: clean-Src-2f-HAL-2f-DC_Motor

