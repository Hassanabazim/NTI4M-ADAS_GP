################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../APP/APP_prog.c 

OBJS += \
./APP/APP_prog.o 

C_DEPS += \
./APP/APP_prog.d 


# Each subdirectory must supply rules for building sources it contributes
APP/APP_prog.o: ../APP/APP_prog.c APP/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -I"C:/Users/Hassa/git/NTI4M-ADAS_GP/NTI-ADAS/APP" -I"C:/Users/Hassa/git/NTI4M-ADAS_GP/NTI-ADAS/Inc" -I"C:/Users/Hassa/git/NTI4M-ADAS_GP/NTI-ADAS/LIB" -I"C:/Users/Hassa/git/NTI4M-ADAS_GP/NTI-ADAS/MCAL/MADC" -I"C:/Users/Hassa/git/NTI4M-ADAS_GP/NTI-ADAS/MCAL/MAFIO" -I"C:/Users/Hassa/git/NTI4M-ADAS_GP/NTI-ADAS/MCAL/MEXTI" -I"C:/Users/Hassa/git/NTI4M-ADAS_GP/NTI-ADAS/MCAL/MGPIO" -I"C:/Users/Hassa/git/NTI4M-ADAS_GP/NTI-ADAS/MCAL/MNVIC" -I"C:/Users/Hassa/git/NTI4M-ADAS_GP/NTI-ADAS/MCAL/MRCC" -I"C:/Users/Hassa/git/NTI4M-ADAS_GP/NTI-ADAS/MCAL/MSYSTICK" -I"C:/Users/Hassa/git/NTI4M-ADAS_GP/NTI-ADAS/MCAL/MUSART" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"APP/APP_prog.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

