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
-include freertos/subdir.mk
-include drivers/subdir.mk
-include board/subdir.mk
-include CMSIS/subdir.mk
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
all: MK20DN512xxx10_JadeRobot_Unsolved.axf

# Tool invocations
MK20DN512xxx10_JadeRobot_Unsolved.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -Xlinker -Map="MK20DN512xxx10_JadeRobot_Unsolved.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -Xlinker --sort-section=alignment -mcpu=cortex-m4 -mthumb -T "MK20DN512xxx10_JadeRobot_Debug.ld" -o "MK20DN512xxx10_JadeRobot_Unsolved.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) MK20DN512xxx10_JadeRobot_Unsolved.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "MK20DN512xxx10_JadeRobot_Unsolved.axf"; # arm-none-eabi-objcopy -v -O binary "MK20DN512xxx10_JadeRobot_Unsolved.axf" "MK20DN512xxx10_JadeRobot_Unsolved.bin" ; # checksum -p MK20DN512xxx10 -d "MK20DN512xxx10_JadeRobot_Unsolved.bin";
	-@echo ' '

.PHONY: all clean dependents post-build

-include ../makefile.targets
