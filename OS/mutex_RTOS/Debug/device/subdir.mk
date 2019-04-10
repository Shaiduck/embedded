################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../device/system_MK64F12.c 

OBJS += \
./device/system_MK64F12.o 

C_DEPS += \
./device/system_MK64F12.d 


# Each subdirectory must supply rules for building sources it contributes
device/%.o: ../device/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -DFRDM_K64F -DFREEDOM -DFSL_RTOS_FREE_RTOS -DCPU_MK64FN1M0VLL12 -DCPU_MK64FN1M0VLL12_cm4 -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -I../board -I../source -I../ -I../drivers -I../device -I../CMSIS -I../amazon-freertos/include -I../amazon-freertos/FreeRTOS/portable -I../utilities -I../component/serial_manager -I../component/uart -I../component/lists -O0 -fno-common -g3 -Wall -c  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


