################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../GSM/GSM.c 

OBJS += \
./GSM/GSM.o 

C_DEPS += \
./GSM/GSM.d 


# Each subdirectory must supply rules for building sources it contributes
GSM/%.o: ../GSM/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F411xE -I"C:/Users/Mateusz/STM32Cube/UART_GPS/Inc" -I"C:/Users/Mateusz/STM32Cube/UART_GPS/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Mateusz/STM32Cube/UART_GPS/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Mateusz/STM32Cube/UART_GPS/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Mateusz/STM32Cube/UART_GPS/Drivers/CMSIS/Include" -I"C:/Users/Mateusz/STM32Cube/UART_GPS/Inc" -I"C:/Users/Mateusz/STM32Cube/UART_GPS/Middlewares/Third_Party/FatFs/src"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


