################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/MNVIC/MNVIC_prog.c 

OBJS += \
./MCAL/MNVIC/MNVIC_prog.o 

C_DEPS += \
./MCAL/MNVIC/MNVIC_prog.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/MNVIC/%.o MCAL/MNVIC/%.su MCAL/MNVIC/%.cyclo: ../MCAL/MNVIC/%.c MCAL/MNVIC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -I"E:/Final Project/NTI4M-ADAS_GP/NTI-ADAS" -I"E:/Final Project/NTI4M-ADAS_GP/NTI-ADAS" -I"E:/Final Project/NTI4M-ADAS_GP/NTI-ADAS/APP" -I"E:/Final Project/NTI4M-ADAS_GP/NTI-ADAS/HAL/DC MOTOR" -I"E:/Final Project/NTI4M-ADAS_GP/NTI-ADAS/HAL/HIR" -I"E:/Final Project/NTI4M-ADAS_GP/NTI-ADAS/HAL/HLCD" -I"E:/Final Project/NTI4M-ADAS_GP/NTI-ADAS/HAL/HLM35 TEMP" -I"E:/Final Project/NTI4M-ADAS_GP/NTI-ADAS/HAL/HPIR" -I"E:/Final Project/NTI4M-ADAS_GP/NTI-ADAS/HAL/HRAIN SENSOR" -I"E:/Final Project/NTI4M-ADAS_GP/NTI-ADAS/HAL/HRPLIDAR" -I"E:/Final Project/NTI4M-ADAS_GP/NTI-ADAS/HAL/HULTRASONIC" -I"E:/Final Project/NTI4M-ADAS_GP/NTI-ADAS/Inc" -I"E:/Final Project/NTI4M-ADAS_GP/NTI-ADAS/LIB" -I"E:/Final Project/NTI4M-ADAS_GP/NTI-ADAS/MCAL" -I"E:/Final Project/NTI4M-ADAS_GP/NTI-ADAS/MCAL/GPTIM" -I"E:/Final Project/NTI4M-ADAS_GP/NTI-ADAS/MCAL/MADC" -I"E:/Final Project/NTI4M-ADAS_GP/NTI-ADAS/MCAL/MAFIO" -I"E:/Final Project/NTI4M-ADAS_GP/NTI-ADAS/MCAL/MEXTI" -I"E:/Final Project/NTI4M-ADAS_GP/NTI-ADAS/MCAL/MGPIO" -I"E:/Final Project/NTI4M-ADAS_GP/NTI-ADAS/MCAL/MNVIC" -I"E:/Final Project/NTI4M-ADAS_GP/NTI-ADAS/MCAL/MRCC" -I"E:/Final Project/NTI4M-ADAS_GP/NTI-ADAS/MCAL/MSYSTICK" -I"E:/Final Project/NTI4M-ADAS_GP/NTI-ADAS/MCAL/MTIM1" -I"E:/Final Project/NTI4M-ADAS_GP/NTI-ADAS/MCAL/MUSART" -I"E:/Final Project/NTI4M-ADAS_GP/NTI-ADAS/Src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-MCAL-2f-MNVIC

clean-MCAL-2f-MNVIC:
	-$(RM) ./MCAL/MNVIC/MNVIC_prog.cyclo ./MCAL/MNVIC/MNVIC_prog.d ./MCAL/MNVIC/MNVIC_prog.o ./MCAL/MNVIC/MNVIC_prog.su

.PHONY: clean-MCAL-2f-MNVIC

