################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/fsl_clock.c \
../drivers/fsl_common.c \
../drivers/fsl_flash.c \
../drivers/fsl_gpio.c \
../drivers/fsl_smc.c \
../drivers/fsl_uart.c 

OBJS += \
./drivers/fsl_clock.o \
./drivers/fsl_common.o \
./drivers/fsl_flash.o \
./drivers/fsl_gpio.o \
./drivers/fsl_smc.o \
./drivers/fsl_uart.o 

C_DEPS += \
./drivers/fsl_clock.d \
./drivers/fsl_common.d \
./drivers/fsl_flash.d \
./drivers/fsl_gpio.d \
./drivers/fsl_smc.d \
./drivers/fsl_uart.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/%.o: ../drivers/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DSCANF_FLOAT_ENABLE=0 -DPRINTF_FLOAT_ENABLE=0 -DFRDM_K64F -DCR_INTEGER_PRINTF -DFREEDOM -DPRINTF_ADVANCED_ENABLE=0 -DSCANF_ADVANCED_ENABLE=0 -DSDK_DEBUGCONSOLE=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DCPU_MK64FN1M0VLL12 -DCPU_MK64FN1M0VLL12_cm4 -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_10.3.0_2200\workspace\frdmk64f_demo_apps_ContextSwitch-2\board" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_10.3.0_2200\workspace\frdmk64f_demo_apps_ContextSwitch-2\source" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_10.3.0_2200\workspace\frdmk64f_demo_apps_ContextSwitch-2" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_10.3.0_2200\workspace\frdmk64f_demo_apps_ContextSwitch-2\drivers" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_10.3.0_2200\workspace\frdmk64f_demo_apps_ContextSwitch-2\CMSIS" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_10.3.0_2200\workspace\frdmk64f_demo_apps_ContextSwitch-2\utilities" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_10.3.0_2200\workspace\frdmk64f_demo_apps_ContextSwitch-2\startup" -O0 -fno-common -g -Wall -c  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


