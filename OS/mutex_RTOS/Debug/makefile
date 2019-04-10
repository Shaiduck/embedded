################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include utilities/subdir.mk
-include startup/subdir.mk
-include source/subdir.mk
-include drivers/subdir.mk
-include device/subdir.mk
-include component/uart/subdir.mk
-include component/serial_manager/subdir.mk
-include component/lists/subdir.mk
-include board/subdir.mk
-include amazon-freertos/FreeRTOS/portable/subdir.mk
-include amazon-freertos/FreeRTOS/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: mutex_RTOS.axf

# Tool invocations
mutex_RTOS.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -Xlinker -Map="mutex_RTOS.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -Xlinker --sort-section=alignment -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -T "mutex_RTOS_Debug.ld" -o "mutex_RTOS.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) mutex_RTOS.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "mutex_RTOS.axf"; # arm-none-eabi-objcopy -v -O binary "mutex_RTOS.axf" "mutex_RTOS.bin" ; # checksum -p MK64FN1M0xxx12 -d "mutex_RTOS.bin";
	-@echo ' '

.PHONY: all clean dependents post-build

-include ../makefile.targets
