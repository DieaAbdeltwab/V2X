################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/7SEG_program.c \
../Src/ADC_program.c \
../Src/AFIO_program.c \
../Src/CARKIT_program.c \
../Src/DAC_program.c \
../Src/DMA_program.c \
../Src/EXTI_program.c \
../Src/GPIO_program.c \
../Src/GPTIMER_program.c \
../Src/GUI_program.c \
../Src/I2C_program.c \
../Src/INA219_program.c \
../Src/IR_program.c \
../Src/KPD_program.c \
../Src/LCD_program.c \
../Src/LEDMRX_program.c \
../Src/MPU6050_program.c \
../Src/NVIC_program.c \
../Src/RCC_program.c \
../Src/RTC_program.c \
../Src/SCB_program.c \
../Src/SPI_program.c \
../Src/STK_program.c \
../Src/STP_program.c \
../Src/TFT_program.c \
../Src/TIMERS_program.c \
../Src/ULTRASONIC_program.c \
../Src/USART_program.c \
../Src/V2G_program.c \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/7SEG_program.o \
./Src/ADC_program.o \
./Src/AFIO_program.o \
./Src/CARKIT_program.o \
./Src/DAC_program.o \
./Src/DMA_program.o \
./Src/EXTI_program.o \
./Src/GPIO_program.o \
./Src/GPTIMER_program.o \
./Src/GUI_program.o \
./Src/I2C_program.o \
./Src/INA219_program.o \
./Src/IR_program.o \
./Src/KPD_program.o \
./Src/LCD_program.o \
./Src/LEDMRX_program.o \
./Src/MPU6050_program.o \
./Src/NVIC_program.o \
./Src/RCC_program.o \
./Src/RTC_program.o \
./Src/SCB_program.o \
./Src/SPI_program.o \
./Src/STK_program.o \
./Src/STP_program.o \
./Src/TFT_program.o \
./Src/TIMERS_program.o \
./Src/ULTRASONIC_program.o \
./Src/USART_program.o \
./Src/V2G_program.o \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/7SEG_program.d \
./Src/ADC_program.d \
./Src/AFIO_program.d \
./Src/CARKIT_program.d \
./Src/DAC_program.d \
./Src/DMA_program.d \
./Src/EXTI_program.d \
./Src/GPIO_program.d \
./Src/GPTIMER_program.d \
./Src/GUI_program.d \
./Src/I2C_program.d \
./Src/INA219_program.d \
./Src/IR_program.d \
./Src/KPD_program.d \
./Src/LCD_program.d \
./Src/LEDMRX_program.d \
./Src/MPU6050_program.d \
./Src/NVIC_program.d \
./Src/RCC_program.d \
./Src/RTC_program.d \
./Src/SCB_program.d \
./Src/SPI_program.d \
./Src/STK_program.d \
./Src/STP_program.d \
./Src/TFT_program.d \
./Src/TIMERS_program.d \
./Src/ULTRASONIC_program.d \
./Src/USART_program.d \
./Src/V2G_program.d \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/7SEG_program.d ./Src/7SEG_program.o ./Src/7SEG_program.su ./Src/ADC_program.d ./Src/ADC_program.o ./Src/ADC_program.su ./Src/AFIO_program.d ./Src/AFIO_program.o ./Src/AFIO_program.su ./Src/CARKIT_program.d ./Src/CARKIT_program.o ./Src/CARKIT_program.su ./Src/DAC_program.d ./Src/DAC_program.o ./Src/DAC_program.su ./Src/DMA_program.d ./Src/DMA_program.o ./Src/DMA_program.su ./Src/EXTI_program.d ./Src/EXTI_program.o ./Src/EXTI_program.su ./Src/GPIO_program.d ./Src/GPIO_program.o ./Src/GPIO_program.su ./Src/GPTIMER_program.d ./Src/GPTIMER_program.o ./Src/GPTIMER_program.su ./Src/GUI_program.d ./Src/GUI_program.o ./Src/GUI_program.su ./Src/I2C_program.d ./Src/I2C_program.o ./Src/I2C_program.su ./Src/INA219_program.d ./Src/INA219_program.o ./Src/INA219_program.su ./Src/IR_program.d ./Src/IR_program.o ./Src/IR_program.su ./Src/KPD_program.d ./Src/KPD_program.o ./Src/KPD_program.su ./Src/LCD_program.d ./Src/LCD_program.o ./Src/LCD_program.su ./Src/LEDMRX_program.d ./Src/LEDMRX_program.o ./Src/LEDMRX_program.su ./Src/MPU6050_program.d ./Src/MPU6050_program.o ./Src/MPU6050_program.su ./Src/NVIC_program.d ./Src/NVIC_program.o ./Src/NVIC_program.su ./Src/RCC_program.d ./Src/RCC_program.o ./Src/RCC_program.su ./Src/RTC_program.d ./Src/RTC_program.o ./Src/RTC_program.su ./Src/SCB_program.d ./Src/SCB_program.o ./Src/SCB_program.su ./Src/SPI_program.d ./Src/SPI_program.o ./Src/SPI_program.su ./Src/STK_program.d ./Src/STK_program.o ./Src/STK_program.su ./Src/STP_program.d ./Src/STP_program.o ./Src/STP_program.su ./Src/TFT_program.d ./Src/TFT_program.o ./Src/TFT_program.su ./Src/TIMERS_program.d ./Src/TIMERS_program.o ./Src/TIMERS_program.su ./Src/ULTRASONIC_program.d ./Src/ULTRASONIC_program.o ./Src/ULTRASONIC_program.su ./Src/USART_program.d ./Src/USART_program.o ./Src/USART_program.su ./Src/V2G_program.d ./Src/V2G_program.o ./Src/V2G_program.su ./Src/main.d ./Src/main.o ./Src/main.su ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su

.PHONY: clean-Src

