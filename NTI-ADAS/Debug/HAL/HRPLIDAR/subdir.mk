################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/HRPLIDAR/RPLIDAR_program.c 

OBJS += \
./HAL/HRPLIDAR/RPLIDAR_program.o 

C_DEPS += \
./HAL/HRPLIDAR/RPLIDAR_program.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/HRPLIDAR/RPLIDAR_program.o: ../HAL/HRPLIDAR/RPLIDAR_program.c HAL/HRPLIDAR/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I"C:/Users/ITUnit FCI/Desktop/project/NTI-ADAS/MCAL/MADC" -I"C:/Users/ITUnit FCI/Desktop/project/NTI-ADAS/HAL/HRAIN SENSOR" -I"C:/Users/ITUnit FCI/Desktop/project/NTI-ADAS/HAL/HLCD" -I"C:/Users/ITUnit FCI/Desktop/project/NTI-ADAS/HAL/HIR" -I"C:/Users/ITUnit FCI/Desktop/project/NTI-ADAS/HAL/HLM35 TEMP" -I"C:/Users/ITUnit FCI/Desktop/project/NTI-ADAS/APP" -I"C:/Users/ITUnit FCI/Desktop/project/NTI-ADAS/LIB" -I"C:/Users/ITUnit FCI/Desktop/project/NTI-ADAS/MCAL/MAFIO" -I"C:/Users/ITUnit FCI/Desktop/project/NTI-ADAS/MCAL/MEXTI" -I"C:/Users/ITUnit FCI/Desktop/project/NTI-ADAS/MCAL/MGPIO" -I"C:/Users/ITUnit FCI/Desktop/project/NTI-ADAS/MCAL/MNVIC" -I"C:/Users/ITUnit FCI/Desktop/project/NTI-ADAS/MCAL/MRCC" -I"C:/Users/ITUnit FCI/Desktop/project/NTI-ADAS/MCAL/MSYSTICK" -I"C:/Users/ITUnit FCI/Desktop/project/NTI-ADAS/MCAL/MUSART" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"HAL/HRPLIDAR/RPLIDAR_program.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

