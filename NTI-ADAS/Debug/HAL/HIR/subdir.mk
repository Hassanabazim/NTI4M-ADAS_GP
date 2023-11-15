################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/HIR/HIR_prog.c 

OBJS += \
./HAL/HIR/HIR_prog.o 

C_DEPS += \
./HAL/HIR/HIR_prog.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/HIR/HIR_prog.o: ../HAL/HIR/HIR_prog.c HAL/HIR/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I"D:/00-Tools/NTI_GP/NTI-ADAS/APP" -I"D:/00-Tools/NTI_GP/NTI-ADAS/HAL/HIR" -I"D:/00-Tools/NTI_GP/NTI-ADAS/HAL/HLCD" -I"D:/00-Tools/NTI_GP/NTI-ADAS/HAL/HLM35 TEMP" -I"D:/00-Tools/NTI_GP/NTI-ADAS/HAL/HRAIN SENSOR" -I"D:/00-Tools/NTI_GP/NTI-ADAS/HAL/IR" -I"D:/00-Tools/NTI_GP/NTI-ADAS/HAL/PIR" -I"D:/00-Tools/NTI_GP/NTI-ADAS/HAL/RPLIDAR" -I"D:/00-Tools/NTI_GP/NTI-ADAS/LIB" -I"D:/00-Tools/NTI_GP/NTI-ADAS/MCAL/MADC" -I"D:/00-Tools/NTI_GP/NTI-ADAS/MCAL/MAFIO" -I"D:/00-Tools/NTI_GP/NTI-ADAS/MCAL/MEXTI" -I"D:/00-Tools/NTI_GP/NTI-ADAS/MCAL/MGPIO" -I"D:/00-Tools/NTI_GP/NTI-ADAS/MCAL/MNVIC" -I"D:/00-Tools/NTI_GP/NTI-ADAS/MCAL/MRCC" -I"D:/00-Tools/NTI_GP/NTI-ADAS/MCAL/MSYSTICK" -I"D:/00-Tools/NTI_GP/NTI-ADAS/MCAL/MUSART" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"HAL/HIR/HIR_prog.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

