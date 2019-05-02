################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/ContextSwitch-2.c \
../source/context_switch.c \
../source/semihost_hardfault.c \
../source/syscall.c 

OBJS += \
./source/ContextSwitch-2.o \
./source/context_switch.o \
./source/semihost_hardfault.o \
./source/syscall.o 

C_DEPS += \
./source/ContextSwitch-2.d \
./source/context_switch.d \
./source/semihost_hardfault.d \
./source/syscall.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DSCANF_FLOAT_ENABLE=0 -DPRINTF_FLOAT_ENABLE=0 -DFRDM_K64F -DCR_INTEGER_PRINTF -DFREEDOM -DPRINTF_ADVANCED_ENABLE=0 -DSCANF_ADVANCED_ENABLE=0 -DSDK_DEBUGCONSOLE=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DCPU_MK64FN1M0VLL12 -DCPU_MK64FN1M0VLL12_cm4 -I"C:\Users\Shaiduck\Git\Operative Systems\frdmk64f_demo_apps_ContextSwitch-2.zip_expanded\frdmk64f_demo_apps_ContextSwitch-2\board" -I"C:\Users\Shaiduck\Git\Operative Systems\frdmk64f_demo_apps_ContextSwitch-2.zip_expanded\frdmk64f_demo_apps_ContextSwitch-2\source" -I"C:\Users\Shaiduck\Git\Operative Systems\frdmk64f_demo_apps_ContextSwitch-2.zip_expanded\frdmk64f_demo_apps_ContextSwitch-2" -I"C:\Users\Shaiduck\Git\Operative Systems\frdmk64f_demo_apps_ContextSwitch-2.zip_expanded\frdmk64f_demo_apps_ContextSwitch-2\drivers" -I"C:\Users\Shaiduck\Git\Operative Systems\frdmk64f_demo_apps_ContextSwitch-2.zip_expanded\frdmk64f_demo_apps_ContextSwitch-2\CMSIS" -I"C:\Users\Shaiduck\Git\Operative Systems\frdmk64f_demo_apps_ContextSwitch-2.zip_expanded\frdmk64f_demo_apps_ContextSwitch-2\utilities" -I"C:\Users\Shaiduck\Git\Operative Systems\frdmk64f_demo_apps_ContextSwitch-2.zip_expanded\frdmk64f_demo_apps_ContextSwitch-2\startup" -O0 -fno-common -g -Wall -c  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


