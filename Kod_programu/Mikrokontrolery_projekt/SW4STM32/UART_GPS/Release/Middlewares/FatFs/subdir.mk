################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/Mateusz/STM32Cube/UART_GPS/Middlewares/Third_Party/FatFs/src/diskio.c \
C:/Users/Mateusz/STM32Cube/UART_GPS/Middlewares/Third_Party/FatFs/src/ff.c \
C:/Users/Mateusz/STM32Cube/UART_GPS/Middlewares/Third_Party/FatFs/src/ff_gen_drv.c \
C:/Users/Mateusz/STM32Cube/UART_GPS/Middlewares/Third_Party/FatFs/src/option/syscall.c 

OBJS += \
./Middlewares/FatFs/diskio.o \
./Middlewares/FatFs/ff.o \
./Middlewares/FatFs/ff_gen_drv.o \
./Middlewares/FatFs/syscall.o 

C_DEPS += \
./Middlewares/FatFs/diskio.d \
./Middlewares/FatFs/ff.d \
./Middlewares/FatFs/ff_gen_drv.d \
./Middlewares/FatFs/syscall.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/FatFs/diskio.o: C:/Users/Mateusz/STM32Cube/UART_GPS/Middlewares/Third_Party/FatFs/src/diskio.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F411xE -I"C:/Users/Mateusz/STM32Cube/UART_GPS/Inc" -I"C:/Users/Mateusz/STM32Cube/UART_GPS/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Mateusz/STM32Cube/UART_GPS/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Mateusz/STM32Cube/UART_GPS/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Mateusz/STM32Cube/UART_GPS/Drivers/CMSIS/Include" -I"C:/Users/Mateusz/STM32Cube/UART_GPS/Inc" -I"C:/Users/Mateusz/STM32Cube/UART_GPS/Middlewares/Third_Party/FatFs/src"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/FatFs/ff.o: C:/Users/Mateusz/STM32Cube/UART_GPS/Middlewares/Third_Party/FatFs/src/ff.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F411xE -I"C:/Users/Mateusz/STM32Cube/UART_GPS/Inc" -I"C:/Users/Mateusz/STM32Cube/UART_GPS/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Mateusz/STM32Cube/UART_GPS/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Mateusz/STM32Cube/UART_GPS/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Mateusz/STM32Cube/UART_GPS/Drivers/CMSIS/Include" -I"C:/Users/Mateusz/STM32Cube/UART_GPS/Inc" -I"C:/Users/Mateusz/STM32Cube/UART_GPS/Middlewares/Third_Party/FatFs/src"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/FatFs/ff_gen_drv.o: C:/Users/Mateusz/STM32Cube/UART_GPS/Middlewares/Third_Party/FatFs/src/ff_gen_drv.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F411xE -I"C:/Users/Mateusz/STM32Cube/UART_GPS/Inc" -I"C:/Users/Mateusz/STM32Cube/UART_GPS/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Mateusz/STM32Cube/UART_GPS/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Mateusz/STM32Cube/UART_GPS/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Mateusz/STM32Cube/UART_GPS/Drivers/CMSIS/Include" -I"C:/Users/Mateusz/STM32Cube/UART_GPS/Inc" -I"C:/Users/Mateusz/STM32Cube/UART_GPS/Middlewares/Third_Party/FatFs/src"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/FatFs/syscall.o: C:/Users/Mateusz/STM32Cube/UART_GPS/Middlewares/Third_Party/FatFs/src/option/syscall.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F411xE -I"C:/Users/Mateusz/STM32Cube/UART_GPS/Inc" -I"C:/Users/Mateusz/STM32Cube/UART_GPS/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Mateusz/STM32Cube/UART_GPS/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Mateusz/STM32Cube/UART_GPS/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Mateusz/STM32Cube/UART_GPS/Drivers/CMSIS/Include" -I"C:/Users/Mateusz/STM32Cube/UART_GPS/Inc" -I"C:/Users/Mateusz/STM32Cube/UART_GPS/Middlewares/Third_Party/FatFs/src"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


