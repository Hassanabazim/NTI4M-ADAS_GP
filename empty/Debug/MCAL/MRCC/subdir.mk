################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/MRCC/MRCC_prog.c 

OBJS += \
./MCAL/MRCC/MRCC_prog.o 

C_DEPS += \
./MCAL/MRCC/MRCC_prog.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/MRCC/%.o MCAL/MRCC/%.su MCAL/MRCC/%.cyclo: ../MCAL/MRCC/%.c MCAL/MRCC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -I"E:/Final Project/NTI4M-ADAS_GP/empty" -I"E:/Final Project/NTI4M-ADAS_GP/empty/APP" -I"E:/Final Project/NTI4M-ADAS_GP/empty/HAL" -I"E:/Final Project/NTI4M-ADAS_GP/empty/HAL/DC MOTOR" -I"E:/Final Project/NTI4M-ADAS_GP/empty/HAL/HIR" -I"E:/Final Project/NTI4M-ADAS_GP/empty/HAL/HLCD" -I"E:/Final Project/NTI4M-ADAS_GP/empty/HAL/HLM35 TEMP" -I"E:/Final Project/NTI4M-ADAS_GP/empty/HAL/HPIR" -I"E:/Final Project/NTI4M-ADAS_GP/empty/HAL/HRAIN SENSOR" -I"E:/Final Project/NTI4M-ADAS_GP/empty/HAL/HRPLIDAR" -I"E:/Final Project/NTI4M-ADAS_GP/empty/HAL/HULTRASONIC" -I"E:/Final Project/NTI4M-ADAS_GP/empty/LIB" -I"E:/Final Project/NTI4M-ADAS_GP/empty/MCAL" -I"E:/Final Project/NTI4M-ADAS_GP/empty/MCAL/GPTIM" -I"E:/Final Project/NTI4M-ADAS_GP/empty/MCAL/MADC" -I"E:/Final Project/NTI4M-ADAS_GP/empty/MCAL/MAFIO" -I"E:/Final Project/NTI4M-ADAS_GP/empty/MCAL/MEXTI" -I"E:/Final Project/NTI4M-ADAS_GP/empty/MCAL/MGPIO" -I"E:/Final Project/NTI4M-ADAS_GP/empty/MCAL/MNVIC" -I"E:/Final Project/NTI4M-ADAS_GP/empty/MCAL/MRCC" -I"E:/Final Project/NTI4M-ADAS_GP/empty/MCAL/MSYSTICK" -I"E:/Final Project/NTI4M-ADAS_GP/empty/MCAL/MTIM1" -I"E:/Final Project/NTI4M-ADAS_GP/empty/MCAL/MUSART" -I"E:/Final Project/NTI4M-ADAS_GP/empty/Src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-MCAL-2f-MRCC

clean-MCAL-2f-MRCC:
	-$(RM) ./MCAL/MRCC/MRCC_prog.cyclo ./MCAL/MRCC/MRCC_prog.d ./MCAL/MRCC/MRCC_prog.o ./MCAL/MRCC/MRCC_prog.su

.PHONY: clean-MCAL-2f-MRCC

