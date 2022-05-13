################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../flight/src/imu.c \
../flight/src/pid.c \
../flight/src/pos_estimator.c \
../flight/src/power_control.c \
../flight/src/sensors.c \
../flight/src/stabilizer.c \
../flight/src/state_control.c 

OBJS += \
./flight/src/imu.o \
./flight/src/pid.o \
./flight/src/pos_estimator.o \
./flight/src/power_control.o \
./flight/src/sensors.o \
./flight/src/stabilizer.o \
./flight/src/state_control.o 

C_DEPS += \
./flight/src/imu.d \
./flight/src/pid.d \
./flight/src/pos_estimator.d \
./flight/src/power_control.d \
./flight/src/sensors.d \
./flight/src/stabilizer.d \
./flight/src/state_control.d 


# Each subdirectory must supply rules for building sources it contributes
flight/src/%.o: ../flight/src/%.c flight/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F405xx -DUSE_HAL_DRIVER -DDEBUG -DUSE_USB_OTG_FS -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../common/interface -I../usb_vcp/interface -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../system/sys -I../fc/interface -I../sensors/interface -I../drive/interface -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../system/delay -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../communicate/interface -I../Drivers/CMSIS/Include -I../flight/interface -I../Core/Inc -I../config/interface -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I../MyFATFS -I../STM32_USB_Library/interface -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

