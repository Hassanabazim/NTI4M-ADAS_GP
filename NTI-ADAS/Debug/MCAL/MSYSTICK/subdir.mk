################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/MSYSTICK/MSYSTICK_prog.c 

OBJS += \
./MCAL/MSYSTICK/MSYSTICK_prog.o 

C_DEPS += \
./MCAL/MSYSTICK/MSYSTICK_prog.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/MSYSTICK/MSYSTICK_prog.o: ../MCAL/MSYSTICK/MSYSTICK_prog.c MCAL/MSYSTICK/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I"D:/NTI-Embedded System/Automotive 4M/GP Project/NTI-ADAS/MCAL/MADC" -I"D:/NTI-Embedded System/Automotive 4M/GP Project/NTI-ADAS/HAL/HRAIN SENSOR" -I"D:/NTI-Embedded System/Automotive 4M/GP Project/NTI-ADAS/HAL/HLCD" -I"D:/NTI-Embedded System/Automotive 4M/GP Project/NTI-ADAS/HAL/HIR" -I"D:/NTI-Embedded System/Automotive 4M/GP Project/NTI-ADAS/HAL/HLM35 TEMP" -I"D:/NTI-Embedded System/Automotive 4M/GP Project/NTI-ADAS/APP" -I"D:/NTI-Embedded System/Automotive 4M/GP Project/NTI-ADAS/LIB" -I"D:/NTI-Embedded System/Automotive 4M/GP Project/NTI-ADAS/MCAL/MAFIO" -I"D:/NTI-Embedded System/Automotive 4M/GP Project/NTI-ADAS/MCAL/MEXTI" -I"D:/NTI-Embedded System/Automotive 4M/GP Project/NTI-ADAS/MCAL/MGPIO" -I"D:/NTI-Embedded System/Automotive 4M/GP Project/NTI-ADAS/MCAL/MNVIC" -I"D:/NTI-Embedded System/Automotive 4M/GP Project/NTI-ADAS/MCAL/MRCC" -I"D:/NTI-Embedded System/Automotive 4M/GP Project/NTI-ADAS/MCAL/MSYSTICK" -I"D:/NTI-Embedded System/Automotive 4M/GP Project/NTI-ADAS/MCAL/MUSART" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"MCAL/MSYSTICK/MSYSTICK_prog.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

