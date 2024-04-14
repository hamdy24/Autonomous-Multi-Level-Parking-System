################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/HAL/MPU6050/MPU6050_Config.c \
../Src/HAL/MPU6050/MPU6050_Program.c 

OBJS += \
./Src/HAL/MPU6050/MPU6050_Config.o \
./Src/HAL/MPU6050/MPU6050_Program.o 

C_DEPS += \
./Src/HAL/MPU6050/MPU6050_Config.d \
./Src/HAL/MPU6050/MPU6050_Program.d 


# Each subdirectory must supply rules for building sources it contributes
Src/HAL/MPU6050/%.o Src/HAL/MPU6050/%.su Src/HAL/MPU6050/%.cyclo: ../Src/HAL/MPU6050/%.c Src/HAL/MPU6050/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-HAL-2f-MPU6050

clean-Src-2f-HAL-2f-MPU6050:
	-$(RM) ./Src/HAL/MPU6050/MPU6050_Config.cyclo ./Src/HAL/MPU6050/MPU6050_Config.d ./Src/HAL/MPU6050/MPU6050_Config.o ./Src/HAL/MPU6050/MPU6050_Config.su ./Src/HAL/MPU6050/MPU6050_Program.cyclo ./Src/HAL/MPU6050/MPU6050_Program.d ./Src/HAL/MPU6050/MPU6050_Program.o ./Src/HAL/MPU6050/MPU6050_Program.su

.PHONY: clean-Src-2f-HAL-2f-MPU6050

