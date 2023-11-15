################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/MSYSTICK/MSYSTICK_prog.c 

OBJS += \
./MCAL/MSYSTICK/MSYSTICK_prog.o 

C_DEPS += \
./MCAL/MSYSTICK/MSYSTICK_prog.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/MSYSTICK/%.o MCAL/MSYSTICK/%.su MCAL/MSYSTICK/%.cyclo: ../MCAL/MSYSTICK/%.c MCAL/MSYSTICK/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I"E:/Mido/Courses/Embedded Systems/Embedded Systems/NTI 4M/Graduation Project/project/NTI4M-ADAS_GP/NTI-ADAS/MCAL/MADC" -I"E:/Mido/Courses/Embedded Systems/Embedded Systems/NTI 4M/Graduation Project/project/NTI4M-ADAS_GP/NTI-ADAS/HAL/HRAIN SENSOR" -I"E:/Mido/Courses/Embedded Systems/Embedded Systems/NTI 4M/Graduation Project/project/NTI4M-ADAS_GP/NTI-ADAS/HAL/HLCD" -I"E:/Mido/Courses/Embedded Systems/Embedded Systems/NTI 4M/Graduation Project/project/NTI4M-ADAS_GP/NTI-ADAS/HAL/HIR" -I"E:/Mido/Courses/Embedded Systems/Embedded Systems/NTI 4M/Graduation Project/project/NTI4M-ADAS_GP/NTI-ADAS/HAL/HLM35 TEMP" -I"E:/Mido/Courses/Embedded Systems/Embedded Systems/NTI 4M/Graduation Project/project/NTI4M-ADAS_GP/NTI-ADAS/APP" -I"E:/Mido/Courses/Embedded Systems/Embedded Systems/NTI 4M/Graduation Project/project/NTI4M-ADAS_GP/NTI-ADAS/LIB" -I"E:/Mido/Courses/Embedded Systems/Embedded Systems/NTI 4M/Graduation Project/project/NTI4M-ADAS_GP/NTI-ADAS/MCAL/MAFIO" -I"E:/Mido/Courses/Embedded Systems/Embedded Systems/NTI 4M/Graduation Project/project/NTI4M-ADAS_GP/NTI-ADAS/MCAL/MEXTI" -I"E:/Mido/Courses/Embedded Systems/Embedded Systems/NTI 4M/Graduation Project/project/NTI4M-ADAS_GP/NTI-ADAS/MCAL/MGPIO" -I"E:/Mido/Courses/Embedded Systems/Embedded Systems/NTI 4M/Graduation Project/project/NTI4M-ADAS_GP/NTI-ADAS/MCAL/MNVIC" -I"E:/Mido/Courses/Embedded Systems/Embedded Systems/NTI 4M/Graduation Project/project/NTI4M-ADAS_GP/NTI-ADAS/MCAL/MRCC" -I"E:/Mido/Courses/Embedded Systems/Embedded Systems/NTI 4M/Graduation Project/project/NTI4M-ADAS_GP/NTI-ADAS/MCAL/MSYSTICK" -I"E:/Mido/Courses/Embedded Systems/Embedded Systems/NTI 4M/Graduation Project/project/NTI4M-ADAS_GP/NTI-ADAS/MCAL/MUSART" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-MCAL-2f-MSYSTICK

clean-MCAL-2f-MSYSTICK:
	-$(RM) ./MCAL/MSYSTICK/MSYSTICK_prog.cyclo ./MCAL/MSYSTICK/MSYSTICK_prog.d ./MCAL/MSYSTICK/MSYSTICK_prog.o ./MCAL/MSYSTICK/MSYSTICK_prog.su

.PHONY: clean-MCAL-2f-MSYSTICK

