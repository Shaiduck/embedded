################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/main.c \
../source/semihost_hardfault.c \
../source/threads.c 

OBJS += \
./source/main.o \
./source/semihost_hardfault.o \
./source/threads.o 

C_DEPS += \
./source/main.d \
./source/semihost_hardfault.d \
./source/threads.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DSCANF_FLOAT_ENABLE=0 -DPRINTF_FLOAT_ENABLE=0 -DFRDM_K64F -DCR_INTEGER_PRINTF -DFREEDOM -DPRINTF_ADVANCED_ENABLE=0 -DSCANF_ADVANCED_ENABLE=0 -DSDK_DEBUGCONSOLE=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DCPU_MK64FN1M0VLL12 -DCPU_MK64FN1M0VLL12_cm4 -I"C:\Users\Shaiduck\Git\Operative Systems\frdmk64f_demo_apps_Thread-template.zip_expanded\frdmk64f_demo_apps_Thread-template\board" -I"C:\Users\Shaiduck\Git\Operative Systems\frdmk64f_demo_apps_Thread-template.zip_expanded\frdmk64f_demo_apps_Thread-template\source" -I"C:\Users\Shaiduck\Git\Operative Systems\frdmk64f_demo_apps_Thread-template.zip_expanded\frdmk64f_demo_apps_Thread-template" -I"C:\Users\Shaiduck\Git\Operative Systems\frdmk64f_demo_apps_Thread-template.zip_expanded\frdmk64f_demo_apps_Thread-template\drivers" -I"C:\Users\Shaiduck\Git\Operative Systems\frdmk64f_demo_apps_Thread-template.zip_expanded\frdmk64f_demo_apps_Thread-template\CMSIS" -I"C:\Users\Shaiduck\Git\Operative Systems\frdmk64f_demo_apps_Thread-template.zip_expanded\frdmk64f_demo_apps_Thread-template\utilities" -I"C:\Users\Shaiduck\Git\Operative Systems\frdmk64f_demo_apps_Thread-template.zip_expanded\frdmk64f_demo_apps_Thread-template\startup" -O0 -fno-common -g -Wall -c  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


