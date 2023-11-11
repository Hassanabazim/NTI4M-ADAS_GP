################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include MCAL/MUSART/subdir.mk
-include MCAL/MTIM1/subdir.mk
-include MCAL/MSYSTICK/subdir.mk
-include MCAL/MRCC/subdir.mk
-include MCAL/MNVIC/subdir.mk
-include MCAL/MGPIO/subdir.mk
-include MCAL/MEXTI/subdir.mk
-include MCAL/MAFIO/subdir.mk
-include MCAL/MADC/subdir.mk
-include MCAL/GPTIM/subdir.mk
-include HAL/HULTRASONIC/subdir.mk
-include HAL/HRPLIDAR/subdir.mk
-include HAL/HRAIN\ SENSOR/subdir.mk
-include HAL/HPIR/subdir.mk
-include HAL/HLM35\ TEMP/subdir.mk
-include HAL/HLCD/subdir.mk
-include HAL/HIR/subdir.mk
-include HAL/DC\ MOTOR/subdir.mk
-include APP/subdir.mk
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


BUILD_ARTIFACT_NAME := NTI-ADAS
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
NTI-ADAS.elf \

MAP_FILES += \
NTI-ADAS.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
NTI-ADAS.list \

OBJCOPY_HEX += \
NTI-ADAS.hex \


# All Target
all: main-build

# Main-build Target
main-build: NTI-ADAS.elf secondary-outputs

# Tool invocations
NTI-ADAS.elf NTI-ADAS.map: $(OBJS) $(USER_OBJS) E:\Final\ Project\NTI4M-ADAS_GP\empty\STM32F103C8TX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "NTI-ADAS.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"E:\Final Project\NTI4M-ADAS_GP\empty\STM32F103C8TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="NTI-ADAS.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

NTI-ADAS.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "NTI-ADAS.list"
	@echo 'Finished building: $@'
	@echo ' '

NTI-ADAS.hex: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "NTI-ADAS.hex"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) NTI-ADAS.elf NTI-ADAS.hex NTI-ADAS.list NTI-ADAS.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
