################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/Stm32_F103C6_Drivers/USART/subdir.mk
-include Src/Stm32_F103C6_Drivers/TIMER/subdir.mk
-include Src/Stm32_F103C6_Drivers/RCC/subdir.mk
-include Src/Stm32_F103C6_Drivers/I2C/subdir.mk
-include Src/Stm32_F103C6_Drivers/GPIO/subdir.mk
-include Src/Stm32_F103C6_Drivers/EXTI/subdir.mk
-include Src/HAL/UltraSonic_HC_SR04/subdir.mk
-include Src/HAL/Stepper/subdir.mk
-include Src/HAL/MPU6050/subdir.mk
-include Src/HAL/LED/subdir.mk
-include Src/HAL/LCD/subdir.mk
-include Src/HAL/DC_Motor/subdir.mk
-include Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := MPUisBackToLife
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
MPUisBackToLife.elf \

MAP_FILES += \
MPUisBackToLife.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
MPUisBackToLife.list \

OBJCOPY_HEX += \
MPUisBackToLife.hex \


# All Target
all: main-build

# Main-build Target
main-build: MPUisBackToLife.elf secondary-outputs

# Tool invocations
MPUisBackToLife.elf MPUisBackToLife.map: $(OBJS) $(USER_OBJS) C:\Users\Abdallah\STM32CubeIDE\workspace_1.4.0\MPUisBackToLife\STM32F103C8TX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -gdwarf-2 -o "MPUisBackToLife.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"C:\Users\Abdallah\STM32CubeIDE\workspace_1.4.0\MPUisBackToLife\STM32F103C8TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="MPUisBackToLife.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

MPUisBackToLife.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "MPUisBackToLife.list"
	@echo 'Finished building: $@'
	@echo ' '

MPUisBackToLife.hex: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "MPUisBackToLife.hex"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) MPUisBackToLife.elf MPUisBackToLife.hex MPUisBackToLife.list MPUisBackToLife.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
