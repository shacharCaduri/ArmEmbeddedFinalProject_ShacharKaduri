################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../APIs/Src/I2C_DMA.c \
../APIs/Src/SPI_DMA.c \
../APIs/Src/TIMER.c \
../APIs/Src/UART_DMA.c \
../APIs/Src/UUT.c \
../APIs/Src/printf_redefenition.c 

OBJS += \
./APIs/Src/I2C_DMA.o \
./APIs/Src/SPI_DMA.o \
./APIs/Src/TIMER.o \
./APIs/Src/UART_DMA.o \
./APIs/Src/UUT.o \
./APIs/Src/printf_redefenition.o 

C_DEPS += \
./APIs/Src/I2C_DMA.d \
./APIs/Src/SPI_DMA.d \
./APIs/Src/TIMER.d \
./APIs/Src/UART_DMA.d \
./APIs/Src/UUT.d \
./APIs/Src/printf_redefenition.d 


# Each subdirectory must supply rules for building sources it contributes
APIs/Src/%.o APIs/Src/%.su: ../APIs/Src/%.c APIs/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Core/Inc -I../APIs/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-APIs-2f-Src

clean-APIs-2f-Src:
	-$(RM) ./APIs/Src/I2C_DMA.d ./APIs/Src/I2C_DMA.o ./APIs/Src/I2C_DMA.su ./APIs/Src/SPI_DMA.d ./APIs/Src/SPI_DMA.o ./APIs/Src/SPI_DMA.su ./APIs/Src/TIMER.d ./APIs/Src/TIMER.o ./APIs/Src/TIMER.su ./APIs/Src/UART_DMA.d ./APIs/Src/UART_DMA.o ./APIs/Src/UART_DMA.su ./APIs/Src/UUT.d ./APIs/Src/UUT.o ./APIs/Src/UUT.su ./APIs/Src/printf_redefenition.d ./APIs/Src/printf_redefenition.o ./APIs/Src/printf_redefenition.su

.PHONY: clean-APIs-2f-Src

