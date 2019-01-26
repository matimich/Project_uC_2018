################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
C:/Users/Mateusz/STM32Cube/UART_GPS/SW4STM32/startup_stm32f411xe.s 

C_SRCS += \
C:/Users/Mateusz/STM32Cube/UART_GPS/SW4STM32/syscalls.c 

OBJS += \
./Application/SW4STM32/startup_stm32f411xe.o \
./Application/SW4STM32/syscalls.o 

C_DEPS += \
./Application/SW4STM32/syscalls.d 


# Each subdirectory must supply rules for building sources it contributes
Application/SW4STM32/startup_stm32f411xe.o: C:/Users/Mateusz/STM32Cube/UART_GPS/SW4STM32/startup_stm32f411xe.s
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Assembler'
	@echo $(PWD)
	arm-none-eabi-as -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/SW4STM32/syscalls.o: C:/Users/Mateusz/STM32Cube/UART_GPS/SW4STM32/syscalls.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F411xE -I"C:/Users/Mateusz/STM32Cube/UART_GPS/Inc" -I"C:/Users/Mateusz/STM32Cube/UART_GPS/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Mateusz/STM32Cube/UART_GPS/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Mateusz/STM32Cube/UART_GPS/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Mateusz/STM32Cube/UART_GPS/Drivers/CMSIS/Include" -I"C:/Users/Mateusz/STM32Cube/UART_GPS/Inc" -I"C:/Users/Mateusz/STM32Cube/UART_GPS/Middlewares/Third_Party/FatFs/src"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


