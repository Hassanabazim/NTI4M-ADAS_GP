################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/GPTIM/TIMERx_program.c 

OBJS += \
./MCAL/GPTIM/TIMERx_program.o 

C_DEPS += \
./MCAL/GPTIM/TIMERx_program.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/GPTIM/TIMERx_program.o: ../MCAL/GPTIM/TIMERx_program.c MCAL/GPTIM/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I"C:/Users/ITUnit FCI/Desktop/project/NTI-ADAS/MCAL/MADC" -I"C:/Users/ITUnit FCI/Desktop/project/NTI-ADAS/HAL/HRAIN SENSOR" -I"C:/Users/ITUnit FCI/Desktop/project/NTI-ADAS/HAL/HLCD" -I"C:/Users/ITUnit FCI/Desktop/project/NTI-ADAS/HAL/HIR" -I"C:/Users/ITUnit FCI/Desktop/project/NTI-ADAS/HAL/HLM35 TEMP" -I"C:/Users/ITUnit FCI/Desktop/project/NTI-ADAS/APP" -I"C:/Users/ITUnit FCI/Desktop/project/NTI-ADAS/LIB" -I"C:/Users/ITUnit FCI/Desktop/project/NTI-ADAS/MCAL/MAFIO" -I"C:/Users/ITUnit FCI/Desktop/project/NTI-ADAS/MCAL/MEXTI" -I"C:/Users/ITUnit FCI/Desktop/project/NTI-ADAS/MCAL/MGPIO" -I"C:/Users/ITUnit FCI/Desktop/project/NTI-ADAS/MCAL/MNVIC" -I"C:/Users/ITUnit FCI/Desktop/project/NTI-ADAS/MCAL/MRCC" -I"C:/Users/ITUnit FCI/Desktop/project/NTI-ADAS/MCAL/MSYSTICK" -I"C:/Users/ITUnit FCI/Desktop/project/NTI-ADAS/MCAL/MUSART" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"MCAL/GPTIM/TIMERx_program.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

