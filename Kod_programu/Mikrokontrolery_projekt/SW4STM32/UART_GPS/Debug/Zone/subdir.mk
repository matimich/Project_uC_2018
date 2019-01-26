################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Zone/zone.c 

OBJS += \
./Zone/zone.o 

C_DEPS += \
./Zone/zone.d 


# Each subdirectory must supply rules for building sources it contributes
Zone/%.o: ../Zone/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F411xE -I"C:/Users/Mateusz/STM32Cube/Mikrokontrolery_projekt/Inc" -I"C:/Users/Mateusz/STM32Cube/Mikrokontrolery_projekt/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Mateusz/STM32Cube/Mikrokontrolery_projekt/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Mateusz/STM32Cube/Mikrokontrolery_projekt/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Mateusz/STM32Cube/Mikrokontrolery_projekt/Drivers/CMSIS/Include" -I"C:/Users/Mateusz/STM32Cube/Mikrokontrolery_projekt/SW4STM32/UART_GPS/Zone" -I"C:/Users/Mateusz/STM32Cube/Mikrokontrolery_projekt/SW4STM32/UART_GPS/EEPROM" -I"C:/Users/Mateusz/STM32Cube/Mikrokontrolery_projekt/SW4STM32/UART_GPS/GSM" -I"C:/Users/Mateusz/STM32Cube/Mikrokontrolery_projekt/Middlewares/Third_Party/FatFs/src" -I"C:/Users/Mateusz/STM32Cube/Mikrokontrolery_projekt/SW4STM32/UART_GPS/SPI_Card"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


