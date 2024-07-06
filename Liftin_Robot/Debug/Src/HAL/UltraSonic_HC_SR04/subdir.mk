################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/HAL/UltraSonic_HC_SR04/UltraSonic_Config.c \
../Src/HAL/UltraSonic_HC_SR04/UltraSonic_Program.c 

OBJS += \
./Src/HAL/UltraSonic_HC_SR04/UltraSonic_Config.o \
./Src/HAL/UltraSonic_HC_SR04/UltraSonic_Program.o 

C_DEPS += \
./Src/HAL/UltraSonic_HC_SR04/UltraSonic_Config.d \
./Src/HAL/UltraSonic_HC_SR04/UltraSonic_Program.d 


# Each subdirectory must supply rules for building sources it contributes
Src/HAL/UltraSonic_HC_SR04/%.o Src/HAL/UltraSonic_HC_SR04/%.su Src/HAL/UltraSonic_HC_SR04/%.cyclo: ../Src/HAL/UltraSonic_HC_SR04/%.c Src/HAL/UltraSonic_HC_SR04/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-HAL-2f-UltraSonic_HC_SR04

clean-Src-2f-HAL-2f-UltraSonic_HC_SR04:
	-$(RM) ./Src/HAL/UltraSonic_HC_SR04/UltraSonic_Config.cyclo ./Src/HAL/UltraSonic_HC_SR04/UltraSonic_Config.d ./Src/HAL/UltraSonic_HC_SR04/UltraSonic_Config.o ./Src/HAL/UltraSonic_HC_SR04/UltraSonic_Config.su ./Src/HAL/UltraSonic_HC_SR04/UltraSonic_Program.cyclo ./Src/HAL/UltraSonic_HC_SR04/UltraSonic_Program.d ./Src/HAL/UltraSonic_HC_SR04/UltraSonic_Program.o ./Src/HAL/UltraSonic_HC_SR04/UltraSonic_Program.su

.PHONY: clean-Src-2f-HAL-2f-UltraSonic_HC_SR04

