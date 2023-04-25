################################################################################
# Automatically-generated file. Do not edit!
################################################################################

#Progress monitor hint: 55
first : all
-include ../makefile.init

# This file contains definitions of environment variables used in the makefiles and .args files if exist.
-include makefile.local

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include Generated_Code/subdir.mk
-include Project_Settings/Linker_Files/subdir.mk
-include Project_Settings/Startup_Code/subdir.mk
-include SDK/platform/devices/S32K144/startup/subdir.mk
-include SDK/platform/devices/subdir.mk
-include SDK/platform/drivers/src/clock/S32K1xx/subdir.mk
-include SDK/platform/drivers/src/clock/subdir.mk
-include SDK/platform/drivers/src/edma/subdir.mk
-include SDK/platform/drivers/src/ewm/subdir.mk
-include SDK/platform/drivers/src/flexcan/subdir.mk
-include SDK/platform/drivers/src/ftm/subdir.mk
-include SDK/platform/drivers/src/interrupt/subdir.mk
-include SDK/platform/drivers/src/lpi2c/subdir.mk
-include SDK/platform/drivers/src/lpspi/subdir.mk
-include SDK/platform/drivers/src/lpuart/subdir.mk
-include SDK/platform/drivers/src/pins/subdir.mk
-include SDK/platform/drivers/src/wdog/subdir.mk
-include SDK/platform/pal/can/src/subdir.mk
-include SDK/platform/pal/i2c/src/subdir.mk
-include SDK/platform/pal/uart/src/subdir.mk
-include SDK/platform/pal/wdg/src/subdir.mk
-include SDK/rtos/osif/subdir.mk
-include Sources/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
s32k144.elf \

EXECUTABLES_QUOTED += \
"s32k144.elf" \

EXECUTABLES_OS_FORMAT += \
s32k144.elf \

SECONDARY_SIZE += \
s32k144.siz \
s32k144.siz \

SECONDARY_SIZE_QUOTED += \
"s32k144.siz" \
"s32k144.siz" \

SECONDARY_SIZE_OS_FORMAT += \
s32k144.siz \
s32k144.siz \

SECONDARY_SIZE += \
s32k144.siz \
s32k144.siz \

SECONDARY_SIZE_QUOTED += \
"s32k144.siz" \
"s32k144.siz" \

SECONDARY_SIZE_OS_FORMAT += \
s32k144.siz \
s32k144.siz \


# All Target
all: warning-messages explicit-dependencies s32k144.elf secondary-outputs

# Tool invocations
s32k144.elf: $(OBJS) C:/NXP/S32DS_ARM_v2018.R1/S32DS/S32SDK_S32K14x_EAR_0.8.6/platform/devices/S32K144/linker/gcc/S32K144_64_ram.ld $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Executing target #56 $@'
	@echo 'Invoking: Standard S32DS C Linker'
	arm-none-eabi-gcc -o "s32k144.elf" "@s32k144.args"  $(USER_OBJS_QUOTED) 
	@echo 'Finished building target: $@'
	@echo ' '

s32k144.siz: $(EXECUTABLES)
	@echo 'Executing target #57 $@'
	@echo 'Invoking: Standard S32DS Print Size'
	arm-none-eabi-size --format=berkeley $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) ./*/*.d ./*/*/*/*.d ./*/*/*/*/*/*.d ./*/*/*/*/*/*/*.d  ./*/*.o ./*/*/*/*.o ./*/*/*/*/*/*.o ./*/*/*/*/*/*/*.o ./*/*/*.o  $(SECONDARY_SIZE_QUOTED) $(EXECUTABLES_QUOTED)
	-@echo ' '

secondary-outputs: $(SECONDARY_SIZE) $(SECONDARY_SIZE)

.PHONY: all clean dependents explicit-dependencies warning-messages
.SECONDARY:

-include ../makefile.targets

explicit-dependencies: 

warning-messages: 

