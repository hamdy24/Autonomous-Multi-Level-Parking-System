################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/Stm32_F103C6_Drivers/GPIO/Stm32_F103C6_gpio_driver.c 

OBJS += \
./Src/Stm32_F103C6_Drivers/GPIO/Stm32_F103C6_gpio_driver.o 

C_DEPS += \
./Src/Stm32_F103C6_Drivers/GPIO/Stm32_F103C6_gpio_driver.d 


# Each subdirectory must supply rules for building sources it contributes
Src/Stm32_F103C6_Drivers/GPIO/%.o Src/Stm32_F103C6_Drivers/GPIO/%.su Src/Stm32_F103C6_Drivers/GPIO/%.cyclo: ../Src/Stm32_F103C6_Drivers/GPIO/%.c Src/Stm32_F103C6_Drivers/GPIO/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-Stm32_F103C6_Drivers-2f-GPIO

clean-Src-2f-Stm32_F103C6_Drivers-2f-GPIO:
	-$(RM) ./Src/Stm32_F103C6_Drivers/GPIO/Stm32_F103C6_gpio_driver.cyclo ./Src/Stm32_F103C6_Drivers/GPIO/Stm32_F103C6_gpio_driver.d ./Src/Stm32_F103C6_Drivers/GPIO/Stm32_F103C6_gpio_driver.o ./Src/Stm32_F103C6_Drivers/GPIO/Stm32_F103C6_gpio_driver.su

.PHONY: clean-Src-2f-Stm32_F103C6_Drivers-2f-GPIO

