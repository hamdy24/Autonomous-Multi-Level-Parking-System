################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/HAL/PIR/PIR.c 

OBJS += \
./Src/HAL/PIR/PIR.o 

C_DEPS += \
./Src/HAL/PIR/PIR.d 


# Each subdirectory must supply rules for building sources it contributes
Src/HAL/PIR/%.o Src/HAL/PIR/%.su Src/HAL/PIR/%.cyclo: ../Src/HAL/PIR/%.c Src/HAL/PIR/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-HAL-2f-PIR

clean-Src-2f-HAL-2f-PIR:
	-$(RM) ./Src/HAL/PIR/PIR.cyclo ./Src/HAL/PIR/PIR.d ./Src/HAL/PIR/PIR.o ./Src/HAL/PIR/PIR.su

.PHONY: clean-Src-2f-HAL-2f-PIR

