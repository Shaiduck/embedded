################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/ContextSwitch-1.c \
../source/context_switch.c \
../source/semihost_hardfault.c 

OBJS += \
./source/ContextSwitch-1.o \
./source/context_switch.o \
./source/semihost_hardfault.o 

C_DEPS += \
./source/ContextSwitch-1.d \
./source/context_switch.d \
./source/semihost_hardfault.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DSCANF_FLOAT_ENABLE=0 -DPRINTF_FLOAT_ENABLE=0 -DFRDM_K64F -DCR_INTEGER_PRINTF -DFREEDOM -DPRINTF_ADVANCED_ENABLE=0 -DSCANF_ADVANCED_ENABLE=0 -DSDK_DEBUGCONSOLE=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DCPU_MK64FN1M0VLL12 -DCPU_MK64FN1M0VLL12_cm4 -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_10.3.0_2200\workspace\frdmk64f_demo_apps_ContextSwitch-1\board" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_10.3.0_2200\workspace\frdmk64f_demo_apps_ContextSwitch-1\source" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_10.3.0_2200\workspace\frdmk64f_demo_apps_ContextSwitch-1" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_10.3.0_2200\workspace\frdmk64f_demo_apps_ContextSwitch-1\drivers" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_10.3.0_2200\workspace\frdmk64f_demo_apps_ContextSwitch-1\CMSIS" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_10.3.0_2200\workspace\frdmk64f_demo_apps_ContextSwitch-1\utilities" -I"C:\Users\nxa16972\Documents\MCUXpressoIDE_10.3.0_2200\workspace\frdmk64f_demo_apps_ContextSwitch-1\startup" -O0 -fno-common -g -Wall -c  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


