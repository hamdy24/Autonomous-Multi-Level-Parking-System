################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/HAL/Servo/Servo.c 

OBJS += \
./Src/HAL/Servo/Servo.o 

C_DEPS += \
./Src/HAL/Servo/Servo.d 


# Each subdirectory must supply rules for building sources it contributes
Src/HAL/Servo/%.o Src/HAL/Servo/%.su Src/HAL/Servo/%.cyclo: ../Src/HAL/Servo/%.c Src/HAL/Servo/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-HAL-2f-Servo

clean-Src-2f-HAL-2f-Servo:
	-$(RM) ./Src/HAL/Servo/Servo.cyclo ./Src/HAL/Servo/Servo.d ./Src/HAL/Servo/Servo.o ./Src/HAL/Servo/Servo.su

.PHONY: clean-Src-2f-HAL-2f-Servo

