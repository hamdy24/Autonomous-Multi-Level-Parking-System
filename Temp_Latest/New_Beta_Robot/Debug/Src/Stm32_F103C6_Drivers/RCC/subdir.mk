################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/Stm32_F103C6_Drivers/RCC/Stm32_F103C6_RCC_driver.c 

OBJS += \
./Src/Stm32_F103C6_Drivers/RCC/Stm32_F103C6_RCC_driver.o 

C_DEPS += \
./Src/Stm32_F103C6_Drivers/RCC/Stm32_F103C6_RCC_driver.d 


# Each subdirectory must supply rules for building sources it contributes
Src/Stm32_F103C6_Drivers/RCC/%.o Src/Stm32_F103C6_Drivers/RCC/%.su Src/Stm32_F103C6_Drivers/RCC/%.cyclo: ../Src/Stm32_F103C6_Drivers/RCC/%.c Src/Stm32_F103C6_Drivers/RCC/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-Stm32_F103C6_Drivers-2f-RCC

clean-Src-2f-Stm32_F103C6_Drivers-2f-RCC:
	-$(RM) ./Src/Stm32_F103C6_Drivers/RCC/Stm32_F103C6_RCC_driver.cyclo ./Src/Stm32_F103C6_Drivers/RCC/Stm32_F103C6_RCC_driver.d ./Src/Stm32_F103C6_Drivers/RCC/Stm32_F103C6_RCC_driver.o ./Src/Stm32_F103C6_Drivers/RCC/Stm32_F103C6_RCC_driver.su

.PHONY: clean-Src-2f-Stm32_F103C6_Drivers-2f-RCC

