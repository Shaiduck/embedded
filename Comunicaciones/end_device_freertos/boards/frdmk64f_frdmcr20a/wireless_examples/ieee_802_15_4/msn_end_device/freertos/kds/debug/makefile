################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include utilities/subdir.mk
-include usb/osa/subdir.mk
-include usb/device/source/khci/subdir.mk
-include usb/device/source/subdir.mk
-include startup/subdir.mk
-include source/subdir.mk
-include mmcau/mmcau_source/subdir.mk
-include ieee_802.15.4/phy/source/XcvrSPI/subdir.mk
-include ieee_802.15.4/phy/source/MCR20A/MCR20Drv/subdir.mk
-include ieee_802.15.4/phy/source/subdir.mk
-include ieee_802.15.4/App/subdir.mk
-include freertos/portable/subdir.mk
-include freertos/subdir.mk
-include framework/TimersManager/Source/subdir.mk
-include framework/SerialManager/Source/USB_VirtualCom/Source/subdir.mk
-include framework/SerialManager/Source/SPI_Adapter/subdir.mk
-include framework/SerialManager/Source/subdir.mk
-include framework/SecLib/subdir.mk
-include framework/Reset/Source/subdir.mk
-include framework/RNG/Source/subdir.mk
-include framework/Panic/Source/subdir.mk
-include framework/OSAbstraction/Interface/subdir.mk
-include framework/Messaging/Source/subdir.mk
-include framework/MemManager/Source/subdir.mk
-include framework/MWSCoexistence/Source/subdir.mk
-include framework/Lists/subdir.mk
-include framework/LED/Source/subdir.mk
-include framework/Keyboard/Source/subdir.mk
-include framework/GPIO/Source/subdir.mk
-include framework/FunctionLib/subdir.mk
-include framework/Flash/Internal/subdir.mk
-include drivers/subdir.mk
-include board/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
end_device_freertos.bin \


# All Target
all: pre-build main-build

# Main-build Target
main-build: end_device_freertos.elf secondary-outputs

# Tool invocations
end_device_freertos.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross ARM C++ Linker'
	arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -mfloat-abi=softfp -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -ffreestanding -fno-builtin -Wall  -g -T ../MK64FN1M0xxx12_connectivity.ld -Xlinker --gc-sections -Wl,-Map,"end_device_freertos.map" --specs=nano.specs -mapcs  -Xlinker -static  -Xlinker -z  -Xlinker muldefs  -Wl,--no-wchar-size-warning -o "end_device_freertos.elf" -Xlinker --start-group $(OBJS) $(USER_OBJS) $(LIBS) -Xlinker --end-group
	@echo 'Finished building target: $@'
	@echo ' '

end_device_freertos.bin: end_device_freertos.elf
	@echo 'Invoking: Cross ARM GNU Create Flash Image'
	arm-none-eabi-objcopy -O binary "end_device_freertos.elf"  "end_device_freertos.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C++_DEPS)$(OBJS)$(C_DEPS)$(ASM_DEPS)$(CC_DEPS)$(SECONDARY_FLASH)$(CPP_DEPS)$(CXX_DEPS)$(C_UPPER_DEPS)$(S_UPPER_DEPS) end_device_freertos.elf
	-@echo ' '

pre-build:
	-arm-none-eabi-gcc -E -x c -P -Iinclude "C:/Users/Shaiduck/Git/especialidad/masterEmbedded/Comunicaciones/end_device_freertos/boards/frdmk64f_frdmcr20a/wireless_examples/ieee_802_15_4/msn_end_device/freertos/kds/../../../../../../../middleware/wireless/framework_5.0.5/Common/devices/MK64F12/gcc/MK64FN1M0xxx12_connectivity.lld" -o "C:/Users/Shaiduck/Git/especialidad/masterEmbedded/Comunicaciones/end_device_freertos/boards/frdmk64f_frdmcr20a/wireless_examples/ieee_802_15_4/msn_end_device/freertos/kds/MK64FN1M0xxx12_connectivity.ld"
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH)

.PHONY: all clean dependents
.SECONDARY: main-build pre-build

-include ../makefile.targets
