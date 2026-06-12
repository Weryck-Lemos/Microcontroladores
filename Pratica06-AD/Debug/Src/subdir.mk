################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/ADC.c \
../Src/DMA.c \
../Src/gpio.c \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/timer3.c 

OBJS += \
./Src/ADC.o \
./Src/DMA.o \
./Src/gpio.o \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/timer3.o 

C_DEPS += \
./Src/ADC.d \
./Src/DMA.d \
./Src/gpio.d \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/timer3.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DSTM32F103xB=STM32F103xB -c -I"/home/ubuntu/Documentos/Microcontroladores/Pratica06-AD/F1_Header/Include" -I/home/ubuntu/Documentos/Microcontroladores/Pratica06-AD/F1_Header/Include -I"/home/ubuntu/Documentos/Microcontroladores/Pratica06-AD/F1_Header/Device/ST/STM32F1xx/Include" -I"/home/ubuntu/Documentos/Microcontroladores/Pratica06-AD/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/ADC.cyclo ./Src/ADC.d ./Src/ADC.o ./Src/ADC.su ./Src/DMA.cyclo ./Src/DMA.d ./Src/DMA.o ./Src/DMA.su ./Src/gpio.cyclo ./Src/gpio.d ./Src/gpio.o ./Src/gpio.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/timer3.cyclo ./Src/timer3.d ./Src/timer3.o ./Src/timer3.su

.PHONY: clean-Src

