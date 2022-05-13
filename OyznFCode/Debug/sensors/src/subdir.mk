################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../sensors/src/accelerometer.c \
../sensors/src/barometer.c \
../sensors/src/compass.c \
../sensors/src/gyro.c \
../sensors/src/sensorsalignment.c 

OBJS += \
./sensors/src/accelerometer.o \
./sensors/src/barometer.o \
./sensors/src/compass.o \
./sensors/src/gyro.o \
./sensors/src/sensorsalignment.o 

C_DEPS += \
./sensors/src/accelerometer.d \
./sensors/src/barometer.d \
./sensors/src/compass.d \
./sensors/src/gyro.d \
./sensors/src/sensorsalignment.d 


# Each subdirectory must supply rules for building sources it contributes
sensors/src/%.o: ../sensors/src/%.c sensors/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F405xx -DUSE_HAL_DRIVER -DDEBUG -DUSE_USB_OTG_FS -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../common/interface -I../usb_vcp/interface -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../system/sys -I../fc/interface -I../sensors/interface -I../drive/interface -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../system/delay -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../communicate/interface -I../Drivers/CMSIS/Include -I../flight/interface -I../Core/Inc -I../config/interface -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I../MyFATFS -I../STM32_USB_Library/interface -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

