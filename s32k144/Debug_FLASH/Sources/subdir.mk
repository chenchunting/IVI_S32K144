################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/can_receiver.c" \
"../Sources/init.c" \
"../Sources/ledstrip.c" \
"../Sources/main.c" \
"../Sources/test.c" \
"../Sources/uart_receiver.c" \

C_SRCS += \
../Sources/can_receiver.c \
../Sources/init.c \
../Sources/ledstrip.c \
../Sources/main.c \
../Sources/test.c \
../Sources/uart_receiver.c \

OBJS_OS_FORMAT += \
./Sources/can_receiver.o \
./Sources/init.o \
./Sources/ledstrip.o \
./Sources/main.o \
./Sources/test.o \
./Sources/uart_receiver.o \

C_DEPS_QUOTED += \
"./Sources/can_receiver.d" \
"./Sources/init.d" \
"./Sources/ledstrip.d" \
"./Sources/main.d" \
"./Sources/test.d" \
"./Sources/uart_receiver.d" \

OBJS += \
./Sources/can_receiver.o \
./Sources/init.o \
./Sources/ledstrip.o \
./Sources/main.o \
./Sources/test.o \
./Sources/uart_receiver.o \

OBJS_QUOTED += \
"./Sources/can_receiver.o" \
"./Sources/init.o" \
"./Sources/ledstrip.o" \
"./Sources/main.o" \
"./Sources/test.o" \
"./Sources/uart_receiver.o" \

C_DEPS += \
./Sources/can_receiver.d \
./Sources/init.d \
./Sources/ledstrip.d \
./Sources/main.d \
./Sources/test.d \
./Sources/uart_receiver.d \


# Each subdirectory must supply rules for building sources it contributes
Sources/can_receiver.o: ../Sources/can_receiver.c
	@echo 'Building file: $<'
	@echo 'Executing target #53 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/can_receiver.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/can_receiver.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/init.o: ../Sources/init.c
	@echo 'Building file: $<'
	@echo 'Executing target #54 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/init.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/init.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/ledstrip.o: ../Sources/ledstrip.c
	@echo 'Building file: $<'
	@echo 'Executing target #55 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/ledstrip.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/ledstrip.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/main.o: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #56 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/main.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/main.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/test.o: ../Sources/test.c
	@echo 'Building file: $<'
	@echo 'Executing target #57 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/test.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/test.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/uart_receiver.o: ../Sources/uart_receiver.c
	@echo 'Building file: $<'
	@echo 'Executing target #58 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/uart_receiver.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/uart_receiver.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


