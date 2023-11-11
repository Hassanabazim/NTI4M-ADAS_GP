################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/MUSART/MUSART_prog.c 

OBJS += \
./MCAL/MUSART/MUSART_prog.o 

C_DEPS += \
./MCAL/MUSART/MUSART_prog.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/MUSART/%.o MCAL/MUSART/%.su MCAL/MUSART/%.cyclo: ../MCAL/MUSART/%.c MCAL/MUSART/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -I"D:/NTI/New folder/Final_proj/MCAL" -I"D:/NTI/New folder/Final_proj/Src" -I"D:/NTI/New folder/Final_proj/APP" -I"D:/NTI/New folder/Final_proj/HAL" -I"D:/NTI/New folder/Final_proj/HAL/DC MOTOR" -I"D:/NTI/New folder/Final_proj/Inc" -I"D:/NTI/New folder/Final_proj/LIB" -I"D:/NTI/New folder/Final_proj/MCAL/GPTIM" -I"D:/NTI/New folder/Final_proj/MCAL/MADC" -I"D:/NTI/New folder/Final_proj/MCAL/MAFIO" -I"D:/NTI/New folder/Final_proj/MCAL/MEXTI" -I"D:/NTI/New folder/Final_proj/MCAL/MGPIO" -I"D:/NTI/New folder/Final_proj/MCAL/MNVIC" -I"D:/NTI/New folder/Final_proj/MCAL/MRCC" -I"D:/NTI/New folder/Final_proj/MCAL/MSYSTICK" -I"D:/NTI/New folder/Final_proj/MCAL/MUSART" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-MCAL-2f-MUSART

clean-MCAL-2f-MUSART:
	-$(RM) ./MCAL/MUSART/MUSART_prog.cyclo ./MCAL/MUSART/MUSART_prog.d ./MCAL/MUSART/MUSART_prog.o ./MCAL/MUSART/MUSART_prog.su

.PHONY: clean-MCAL-2f-MUSART

