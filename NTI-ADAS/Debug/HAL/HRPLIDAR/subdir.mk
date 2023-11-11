################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/HRPLIDAR/RPLIDAR_program.c 

OBJS += \
./HAL/HRPLIDAR/RPLIDAR_program.o 

C_DEPS += \
./HAL/HRPLIDAR/RPLIDAR_program.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/HRPLIDAR/%.o HAL/HRPLIDAR/%.su HAL/HRPLIDAR/%.cyclo: ../HAL/HRPLIDAR/%.c HAL/HRPLIDAR/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -I"E:/Final Project/NTI4M-ADAS_GP/NTI-ADAS" -I"E:/Final Project/NTI4M-ADAS_GP/NTI-ADAS" -I"E:/Final Project/NTI4M-ADAS_GP/NTI-ADAS/APP" -I"E:/Final Project/NTI4M-ADAS_GP/NTI-ADAS/HAL/DC MOTOR" -I"E:/Final Project/NTI4M-ADAS_GP/NTI-ADAS/HAL/HIR" -I"E:/Final Project/NTI4M-ADAS_GP/NTI-ADAS/HAL/HLCD" -I"E:/Final Project/NTI4M-ADAS_GP/NTI-ADAS/HAL/HLM35 TEMP" -I"E:/Final Project/NTI4M-ADAS_GP/NTI-ADAS/HAL/HPIR" -I"E:/Final Project/NTI4M-ADAS_GP/NTI-ADAS/HAL/HRAIN SENSOR" -I"E:/Final Project/NTI4M-ADAS_GP/NTI-ADAS/HAL/HRPLIDAR" -I"E:/Final Project/NTI4M-ADAS_GP/NTI-ADAS/HAL/HULTRASONIC" -I"E:/Final Project/NTI4M-ADAS_GP/NTI-ADAS/Inc" -I"E:/Final Project/NTI4M-ADAS_GP/NTI-ADAS/LIB" -I"E:/Final Project/NTI4M-ADAS_GP/NTI-ADAS/MCAL" -I"E:/Final Project/NTI4M-ADAS_GP/NTI-ADAS/MCAL/GPTIM" -I"E:/Final Project/NTI4M-ADAS_GP/NTI-ADAS/MCAL/MADC" -I"E:/Final Project/NTI4M-ADAS_GP/NTI-ADAS/MCAL/MAFIO" -I"E:/Final Project/NTI4M-ADAS_GP/NTI-ADAS/MCAL/MEXTI" -I"E:/Final Project/NTI4M-ADAS_GP/NTI-ADAS/MCAL/MGPIO" -I"E:/Final Project/NTI4M-ADAS_GP/NTI-ADAS/MCAL/MNVIC" -I"E:/Final Project/NTI4M-ADAS_GP/NTI-ADAS/MCAL/MRCC" -I"E:/Final Project/NTI4M-ADAS_GP/NTI-ADAS/MCAL/MSYSTICK" -I"E:/Final Project/NTI4M-ADAS_GP/NTI-ADAS/MCAL/MTIM1" -I"E:/Final Project/NTI4M-ADAS_GP/NTI-ADAS/MCAL/MUSART" -I"E:/Final Project/NTI4M-ADAS_GP/NTI-ADAS/Src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-HAL-2f-HRPLIDAR

clean-HAL-2f-HRPLIDAR:
	-$(RM) ./HAL/HRPLIDAR/RPLIDAR_program.cyclo ./HAL/HRPLIDAR/RPLIDAR_program.d ./HAL/HRPLIDAR/RPLIDAR_program.o ./HAL/HRPLIDAR/RPLIDAR_program.su

.PHONY: clean-HAL-2f-HRPLIDAR

