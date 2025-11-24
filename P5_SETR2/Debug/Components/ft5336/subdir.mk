################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Components/ft5336/ft5336.c 

OBJS += \
./Components/ft5336/ft5336.o 

C_DEPS += \
./Components/ft5336/ft5336.d 


# Each subdirectory must supply rules for building sources it contributes
Components/ft5336/%.o Components/ft5336/%.su Components/ft5336/%.cyclo: ../Components/ft5336/%.c Components/ft5336/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L475xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"/home/jomaa/STM32CubeIDE/workspace_1.19.0/P5_SETR2/BSP" -I"/home/jomaa/STM32CubeIDE/workspace_1.19.0/P5_SETR2/LibWIFI/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Components-2f-ft5336

clean-Components-2f-ft5336:
	-$(RM) ./Components/ft5336/ft5336.cyclo ./Components/ft5336/ft5336.d ./Components/ft5336/ft5336.o ./Components/ft5336/ft5336.su

.PHONY: clean-Components-2f-ft5336

