################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"C:/NXP/S32DS_ARM_v2018.R1/S32DS/S32SDK_S32K14x_EAR_0.8.6/platform/drivers/src/ewm/ewm_driver.c" \

C_SRCS += \
C:/NXP/S32DS_ARM_v2018.R1/S32DS/S32SDK_S32K14x_EAR_0.8.6/platform/drivers/src/ewm/ewm_driver.c \

OBJS_OS_FORMAT += \
./SDK/platform/drivers/src/ewm/ewm_driver.o \

C_DEPS_QUOTED += \
"./SDK/platform/drivers/src/ewm/ewm_driver.d" \

OBJS += \
./SDK/platform/drivers/src/ewm/ewm_driver.o \

OBJS_QUOTED += \
"./SDK/platform/drivers/src/ewm/ewm_driver.o" \

C_DEPS += \
./SDK/platform/drivers/src/ewm/ewm_driver.d \


# Each subdirectory must supply rules for building sources it contributes
SDK/platform/drivers/src/ewm/ewm_driver.o: C:/NXP/S32DS_ARM_v2018.R1/S32DS/S32SDK_S32K14x_EAR_0.8.6/platform/drivers/src/ewm/ewm_driver.c
	@echo 'Building file: $<'
	@echo 'Executing target #23 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@SDK/platform/drivers/src/ewm/ewm_driver.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "SDK/platform/drivers/src/ewm/ewm_driver.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

