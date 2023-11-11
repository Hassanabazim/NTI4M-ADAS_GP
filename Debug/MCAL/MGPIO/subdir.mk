################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/MGPIO/MGPIO_prog.c 

OBJS += \
./MCAL/MGPIO/MGPIO_prog.o 

C_DEPS += \
./MCAL/MGPIO/MGPIO_prog.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/MGPIO/%.o MCAL/MGPIO/%.su MCAL/MGPIO/%.cyclo: ../MCAL/MGPIO/%.c MCAL/MGPIO/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -I"D:/NTI/New folder/Final_proj/MCAL" -I"D:/NTI/New folder/Final_proj/Src" -I"D:/NTI/New folder/Final_proj/APP" -I"D:/NTI/New folder/Final_proj/HAL" -I"D:/NTI/New folder/Final_proj/HAL/DC MOTOR" -I"D:/NTI/New folder/Final_proj/Inc" -I"D:/NTI/New folder/Final_proj/LIB" -I"D:/NTI/New folder/Final_proj/MCAL/GPTIM" -I"D:/NTI/New folder/Final_proj/MCAL/MADC" -I"D:/NTI/New folder/Final_proj/MCAL/MAFIO" -I"D:/NTI/New folder/Final_proj/MCAL/MEXTI" -I"D:/NTI/New folder/Final_proj/MCAL/MGPIO" -I"D:/NTI/New folder/Final_proj/MCAL/MNVIC" -I"D:/NTI/New folder/Final_proj/MCAL/MRCC" -I"D:/NTI/New folder/Final_proj/MCAL/MSYSTICK" -I"D:/NTI/New folder/Final_proj/MCAL/MUSART" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-MCAL-2f-MGPIO

clean-MCAL-2f-MGPIO:
	-$(RM) ./MCAL/MGPIO/MGPIO_prog.cyclo ./MCAL/MGPIO/MGPIO_prog.d ./MCAL/MGPIO/MGPIO_prog.o ./MCAL/MGPIO/MGPIO_prog.su

.PHONY: clean-MCAL-2f-MGPIO

