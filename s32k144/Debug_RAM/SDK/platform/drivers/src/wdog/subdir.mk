################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"C:/NXP/S32DS_ARM_v2018.R1/S32DS/S32SDK_S32K14x_EAR_0.8.6/platform/drivers/src/wdog/wdog_driver.c" \
"C:/NXP/S32DS_ARM_v2018.R1/S32DS/S32SDK_S32K14x_EAR_0.8.6/platform/drivers/src/wdog/wdog_hw_access.c" \

C_SRCS += \
C:/NXP/S32DS_ARM_v2018.R1/S32DS/S32SDK_S32K14x_EAR_0.8.6/platform/drivers/src/wdog/wdog_driver.c \
C:/NXP/S32DS_ARM_v2018.R1/S32DS/S32SDK_S32K14x_EAR_0.8.6/platform/drivers/src/wdog/wdog_hw_access.c \

OBJS_OS_FORMAT += \
./SDK/platform/drivers/src/wdog/wdog_driver.o \
./SDK/platform/drivers/src/wdog/wdog_hw_access.o \

C_DEPS_QUOTED += \
"./SDK/platform/drivers/src/wdog/wdog_driver.d" \
"./SDK/platform/drivers/src/wdog/wdog_hw_access.d" \

OBJS += \
./SDK/platform/drivers/src/wdog/wdog_driver.o \
./SDK/platform/drivers/src/wdog/wdog_hw_access.o \

OBJS_QUOTED += \
"./SDK/platform/drivers/src/wdog/wdog_driver.o" \
"./SDK/platform/drivers/src/wdog/wdog_hw_access.o" \

C_DEPS += \
./SDK/platform/drivers/src/wdog/wdog_driver.d \
./SDK/platform/drivers/src/wdog/wdog_hw_access.d \


# Each subdirectory must supply rules for building sources it contributes
SDK/platform/drivers/src/wdog/wdog_driver.o: C:/NXP/S32DS_ARM_v2018.R1/S32DS/S32SDK_S32K14x_EAR_0.8.6/platform/drivers/src/wdog/wdog_driver.c
	@echo 'Building file: $<'
	@echo 'Executing target #43 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@SDK/platform/drivers/src/wdog/wdog_driver.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "SDK/platform/drivers/src/wdog/wdog_driver.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

SDK/platform/drivers/src/wdog/wdog_hw_access.o: C:/NXP/S32DS_ARM_v2018.R1/S32DS/S32SDK_S32K14x_EAR_0.8.6/platform/drivers/src/wdog/wdog_hw_access.c
	@echo 'Building file: $<'
	@echo 'Executing target #44 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@SDK/platform/drivers/src/wdog/wdog_hw_access.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "SDK/platform/drivers/src/wdog/wdog_hw_access.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


