################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Components/st7735/st7735.c 

OBJS += \
./Components/st7735/st7735.o 

C_DEPS += \
./Components/st7735/st7735.d 


# Each subdirectory must supply rules for building sources it contributes
Components/st7735/%.o Components/st7735/%.su Components/st7735/%.cyclo: ../Components/st7735/%.c Components/st7735/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L475xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"/home/jomaa/Projects/git/setr2-monorepo/P5_SETR2/BSP" -I"/home/jomaa/Projects/git/setr2-monorepo/P5_SETR2/LibWIFI/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Components-2f-st7735

clean-Components-2f-st7735:
	-$(RM) ./Components/st7735/st7735.cyclo ./Components/st7735/st7735.d ./Components/st7735/st7735.o ./Components/st7735/st7735.su

.PHONY: clean-Components-2f-st7735

