################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Generated_Code/Cpu.c" \
"../Generated_Code/Send.c" \
"../Generated_Code/Send1.c" \
"../Generated_Code/can_pal0.c" \
"../Generated_Code/can_pal1.c" \
"../Generated_Code/clockMan1.c" \
"../Generated_Code/dmaController1.c" \
"../Generated_Code/flexTimer_pwm1.c" \
"../Generated_Code/i2c1.c" \
"../Generated_Code/lpuart0_uart.c" \
"../Generated_Code/lpuart1_uart.c" \
"../Generated_Code/pin_mux.c" \
"../Generated_Code/wdg_pal1.c" \

C_SRCS += \
../Generated_Code/Cpu.c \
../Generated_Code/Send.c \
../Generated_Code/Send1.c \
../Generated_Code/can_pal0.c \
../Generated_Code/can_pal1.c \
../Generated_Code/clockMan1.c \
../Generated_Code/dmaController1.c \
../Generated_Code/flexTimer_pwm1.c \
../Generated_Code/i2c1.c \
../Generated_Code/lpuart0_uart.c \
../Generated_Code/lpuart1_uart.c \
../Generated_Code/pin_mux.c \
../Generated_Code/wdg_pal1.c \

OBJS_OS_FORMAT += \
./Generated_Code/Cpu.o \
./Generated_Code/Send.o \
./Generated_Code/Send1.o \
./Generated_Code/can_pal0.o \
./Generated_Code/can_pal1.o \
./Generated_Code/clockMan1.o \
./Generated_Code/dmaController1.o \
./Generated_Code/flexTimer_pwm1.o \
./Generated_Code/i2c1.o \
./Generated_Code/lpuart0_uart.o \
./Generated_Code/lpuart1_uart.o \
./Generated_Code/pin_mux.o \
./Generated_Code/wdg_pal1.o \

C_DEPS_QUOTED += \
"./Generated_Code/Cpu.d" \
"./Generated_Code/Send.d" \
"./Generated_Code/Send1.d" \
"./Generated_Code/can_pal0.d" \
"./Generated_Code/can_pal1.d" \
"./Generated_Code/clockMan1.d" \
"./Generated_Code/dmaController1.d" \
"./Generated_Code/flexTimer_pwm1.d" \
"./Generated_Code/i2c1.d" \
"./Generated_Code/lpuart0_uart.d" \
"./Generated_Code/lpuart1_uart.d" \
"./Generated_Code/pin_mux.d" \
"./Generated_Code/wdg_pal1.d" \

OBJS += \
./Generated_Code/Cpu.o \
./Generated_Code/Send.o \
./Generated_Code/Send1.o \
./Generated_Code/can_pal0.o \
./Generated_Code/can_pal1.o \
./Generated_Code/clockMan1.o \
./Generated_Code/dmaController1.o \
./Generated_Code/flexTimer_pwm1.o \
./Generated_Code/i2c1.o \
./Generated_Code/lpuart0_uart.o \
./Generated_Code/lpuart1_uart.o \
./Generated_Code/pin_mux.o \
./Generated_Code/wdg_pal1.o \

OBJS_QUOTED += \
"./Generated_Code/Cpu.o" \
"./Generated_Code/Send.o" \
"./Generated_Code/Send1.o" \
"./Generated_Code/can_pal0.o" \
"./Generated_Code/can_pal1.o" \
"./Generated_Code/clockMan1.o" \
"./Generated_Code/dmaController1.o" \
"./Generated_Code/flexTimer_pwm1.o" \
"./Generated_Code/i2c1.o" \
"./Generated_Code/lpuart0_uart.o" \
"./Generated_Code/lpuart1_uart.o" \
"./Generated_Code/pin_mux.o" \
"./Generated_Code/wdg_pal1.o" \

C_DEPS += \
./Generated_Code/Cpu.d \
./Generated_Code/Send.d \
./Generated_Code/Send1.d \
./Generated_Code/can_pal0.d \
./Generated_Code/can_pal1.d \
./Generated_Code/clockMan1.d \
./Generated_Code/dmaController1.d \
./Generated_Code/flexTimer_pwm1.d \
./Generated_Code/i2c1.d \
./Generated_Code/lpuart0_uart.d \
./Generated_Code/lpuart1_uart.d \
./Generated_Code/pin_mux.d \
./Generated_Code/wdg_pal1.d \


# Each subdirectory must supply rules for building sources it contributes
Generated_Code/Cpu.o: ../Generated_Code/Cpu.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Generated_Code/Cpu.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Generated_Code/Cpu.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/Send.o: ../Generated_Code/Send.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Generated_Code/Send.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Generated_Code/Send.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/Send1.o: ../Generated_Code/Send1.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Generated_Code/Send1.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Generated_Code/Send1.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/can_pal0.o: ../Generated_Code/can_pal0.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Generated_Code/can_pal0.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Generated_Code/can_pal0.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/can_pal1.o: ../Generated_Code/can_pal1.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Generated_Code/can_pal1.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Generated_Code/can_pal1.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/clockMan1.o: ../Generated_Code/clockMan1.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Generated_Code/clockMan1.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Generated_Code/clockMan1.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/dmaController1.o: ../Generated_Code/dmaController1.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Generated_Code/dmaController1.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Generated_Code/dmaController1.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/flexTimer_pwm1.o: ../Generated_Code/flexTimer_pwm1.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Generated_Code/flexTimer_pwm1.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Generated_Code/flexTimer_pwm1.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/i2c1.o: ../Generated_Code/i2c1.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Generated_Code/i2c1.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Generated_Code/i2c1.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/lpuart0_uart.o: ../Generated_Code/lpuart0_uart.c
	@echo 'Building file: $<'
	@echo 'Executing target #10 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Generated_Code/lpuart0_uart.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Generated_Code/lpuart0_uart.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/lpuart1_uart.o: ../Generated_Code/lpuart1_uart.c
	@echo 'Building file: $<'
	@echo 'Executing target #11 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Generated_Code/lpuart1_uart.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Generated_Code/lpuart1_uart.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/pin_mux.o: ../Generated_Code/pin_mux.c
	@echo 'Building file: $<'
	@echo 'Executing target #12 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Generated_Code/pin_mux.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Generated_Code/pin_mux.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/wdg_pal1.o: ../Generated_Code/wdg_pal1.c
	@echo 'Building file: $<'
	@echo 'Executing target #13 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Generated_Code/wdg_pal1.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Generated_Code/wdg_pal1.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


