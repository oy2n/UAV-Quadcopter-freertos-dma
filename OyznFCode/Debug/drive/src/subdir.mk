################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drive/src/GPS.c \
../drive/src/adc1.c \
../drive/src/beeper.c \
../drive/src/bmp280.c \
../drive/src/compass_qmc5883l.c \
../drive/src/cppm.c \
../drive/src/iic.c \
../drive/src/led.c \
../drive/src/motors.c \
../drive/src/mpu6000.c \
../drive/src/stmflash.c \
../drive/src/system.c \
../drive/src/uart1.c \
../drive/src/uart4.c \
../drive/src/watchdog.c \
../drive/src/ws2812.c 

OBJS += \
./drive/src/GPS.o \
./drive/src/adc1.o \
./drive/src/beeper.o \
./drive/src/bmp280.o \
./drive/src/compass_qmc5883l.o \
./drive/src/cppm.o \
./drive/src/iic.o \
./drive/src/led.o \
./drive/src/motors.o \
./drive/src/mpu6000.o \
./drive/src/stmflash.o \
./drive/src/system.o \
./drive/src/uart1.o \
./drive/src/uart4.o \
./drive/src/watchdog.o \
./drive/src/ws2812.o 

C_DEPS += \
./drive/src/GPS.d \
./drive/src/adc1.d \
./drive/src/beeper.d \
./drive/src/bmp280.d \
./drive/src/compass_qmc5883l.d \
./drive/src/cppm.d \
./drive/src/iic.d \
./drive/src/led.d \
./drive/src/motors.d \
./drive/src/mpu6000.d \
./drive/src/stmflash.d \
./drive/src/system.d \
./drive/src/uart1.d \
./drive/src/uart4.d \
./drive/src/watchdog.d \
./drive/src/ws2812.d 


# Each subdirectory must supply rules for building sources it contributes
drive/src/%.o: ../drive/src/%.c drive/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F405xx -DUSE_HAL_DRIVER -DDEBUG -DUSE_USB_OTG_FS -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../common/interface -I../usb_vcp/interface -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../system/sys -I../fc/interface -I../sensors/interface -I../drive/interface -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../system/delay -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../communicate/interface -I../Drivers/CMSIS/Include -I../flight/interface -I../Core/Inc -I../config/interface -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I../MyFATFS -I../STM32_USB_Library/interface -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

