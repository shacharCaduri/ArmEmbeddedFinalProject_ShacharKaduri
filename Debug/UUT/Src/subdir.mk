################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../UUT/Src/ETH_GENERICS.c \
../UUT/Src/ExtraTools.c \
../UUT/Src/I2C_DMA_UUT.c \
../UUT/Src/MAIN_UUT.c \
../UUT/Src/SPI_DMA_UUT.c \
../UUT/Src/TIMER_UUT.c \
../UUT/Src/UART_DMA_UUT.c \
../UUT/Src/UDP_Client.c 

OBJS += \
./UUT/Src/ETH_GENERICS.o \
./UUT/Src/ExtraTools.o \
./UUT/Src/I2C_DMA_UUT.o \
./UUT/Src/MAIN_UUT.o \
./UUT/Src/SPI_DMA_UUT.o \
./UUT/Src/TIMER_UUT.o \
./UUT/Src/UART_DMA_UUT.o \
./UUT/Src/UDP_Client.o 

C_DEPS += \
./UUT/Src/ETH_GENERICS.d \
./UUT/Src/ExtraTools.d \
./UUT/Src/I2C_DMA_UUT.d \
./UUT/Src/MAIN_UUT.d \
./UUT/Src/SPI_DMA_UUT.d \
./UUT/Src/TIMER_UUT.d \
./UUT/Src/UART_DMA_UUT.d \
./UUT/Src/UDP_Client.d 


# Each subdirectory must supply rules for building sources it contributes
UUT/Src/%.o UUT/Src/%.su: ../UUT/Src/%.c UUT/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../UUT/Inc -I../LWIP/App -I../LWIP/Target -I../Middlewares/Third_Party/LwIP/src/include -I../Middlewares/Third_Party/LwIP/system -I../Drivers/BSP/Components/lan8742 -I../Middlewares/Third_Party/LwIP/src/include/netif/ppp -I../Middlewares/Third_Party/LwIP/src/include/lwip -I../Middlewares/Third_Party/LwIP/src/include/lwip/apps -I../Middlewares/Third_Party/LwIP/src/include/lwip/priv -I../Middlewares/Third_Party/LwIP/src/include/lwip/prot -I../Middlewares/Third_Party/LwIP/src/include/netif -I../Middlewares/Third_Party/LwIP/src/include/compat/posix -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/arpa -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/net -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/sys -I../Middlewares/Third_Party/LwIP/src/include/compat/stdc -I../Middlewares/Third_Party/LwIP/system/arch -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-UUT-2f-Src

clean-UUT-2f-Src:
	-$(RM) ./UUT/Src/ETH_GENERICS.d ./UUT/Src/ETH_GENERICS.o ./UUT/Src/ETH_GENERICS.su ./UUT/Src/ExtraTools.d ./UUT/Src/ExtraTools.o ./UUT/Src/ExtraTools.su ./UUT/Src/I2C_DMA_UUT.d ./UUT/Src/I2C_DMA_UUT.o ./UUT/Src/I2C_DMA_UUT.su ./UUT/Src/MAIN_UUT.d ./UUT/Src/MAIN_UUT.o ./UUT/Src/MAIN_UUT.su ./UUT/Src/SPI_DMA_UUT.d ./UUT/Src/SPI_DMA_UUT.o ./UUT/Src/SPI_DMA_UUT.su ./UUT/Src/TIMER_UUT.d ./UUT/Src/TIMER_UUT.o ./UUT/Src/TIMER_UUT.su ./UUT/Src/UART_DMA_UUT.d ./UUT/Src/UART_DMA_UUT.o ./UUT/Src/UART_DMA_UUT.su ./UUT/Src/UDP_Client.d ./UUT/Src/UDP_Client.o ./UUT/Src/UDP_Client.su

.PHONY: clean-UUT-2f-Src

