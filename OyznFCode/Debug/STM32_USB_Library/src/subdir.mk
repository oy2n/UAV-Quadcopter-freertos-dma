################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../STM32_USB_Library/src/usb_core.c \
../STM32_USB_Library/src/usb_dcd.c \
../STM32_USB_Library/src/usb_dcd_int.c \
../STM32_USB_Library/src/usbd_cdc_core.c \
../STM32_USB_Library/src/usbd_core.c \
../STM32_USB_Library/src/usbd_ioreq.c \
../STM32_USB_Library/src/usbd_req.c 

OBJS += \
./STM32_USB_Library/src/usb_core.o \
./STM32_USB_Library/src/usb_dcd.o \
./STM32_USB_Library/src/usb_dcd_int.o \
./STM32_USB_Library/src/usbd_cdc_core.o \
./STM32_USB_Library/src/usbd_core.o \
./STM32_USB_Library/src/usbd_ioreq.o \
./STM32_USB_Library/src/usbd_req.o 

C_DEPS += \
./STM32_USB_Library/src/usb_core.d \
./STM32_USB_Library/src/usb_dcd.d \
./STM32_USB_Library/src/usb_dcd_int.d \
./STM32_USB_Library/src/usbd_cdc_core.d \
./STM32_USB_Library/src/usbd_core.d \
./STM32_USB_Library/src/usbd_ioreq.d \
./STM32_USB_Library/src/usbd_req.d 


# Each subdirectory must supply rules for building sources it contributes
STM32_USB_Library/src/%.o: ../STM32_USB_Library/src/%.c STM32_USB_Library/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F405xx -DUSE_HAL_DRIVER -DDEBUG -DUSE_USB_OTG_FS -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../common/interface -I../usb_vcp/interface -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../system/sys -I../fc/interface -I../sensors/interface -I../drive/interface -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../system/delay -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../communicate/interface -I../Drivers/CMSIS/Include -I../flight/interface -I../Core/Inc -I../config/interface -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I../MyFATFS -I../STM32_USB_Library/interface -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

