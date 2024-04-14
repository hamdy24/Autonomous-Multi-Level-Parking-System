################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/HAL/Stepper/Stepper.c 

OBJS += \
./Src/HAL/Stepper/Stepper.o 

C_DEPS += \
./Src/HAL/Stepper/Stepper.d 


# Each subdirectory must supply rules for building sources it contributes
Src/HAL/Stepper/%.o Src/HAL/Stepper/%.su Src/HAL/Stepper/%.cyclo: ../Src/HAL/Stepper/%.c Src/HAL/Stepper/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-HAL-2f-Stepper

clean-Src-2f-HAL-2f-Stepper:
	-$(RM) ./Src/HAL/Stepper/Stepper.cyclo ./Src/HAL/Stepper/Stepper.d ./Src/HAL/Stepper/Stepper.o ./Src/HAL/Stepper/Stepper.su

.PHONY: clean-Src-2f-HAL-2f-Stepper

