################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/lib/analog/adc.c \
../Src/lib/analog/dac.c 

OBJS += \
./Src/lib/analog/adc.o \
./Src/lib/analog/dac.o 

C_DEPS += \
./Src/lib/analog/adc.d \
./Src/lib/analog/dac.d 


# Each subdirectory must supply rules for building sources it contributes
Src/lib/analog/%.o Src/lib/analog/%.su Src/lib/analog/%.cyclo: ../Src/lib/analog/%.c Src/lib/analog/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32G4 -DSTM32G483CETx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-lib-2f-analog

clean-Src-2f-lib-2f-analog:
	-$(RM) ./Src/lib/analog/adc.cyclo ./Src/lib/analog/adc.d ./Src/lib/analog/adc.o ./Src/lib/analog/adc.su ./Src/lib/analog/dac.cyclo ./Src/lib/analog/dac.d ./Src/lib/analog/dac.o ./Src/lib/analog/dac.su

.PHONY: clean-Src-2f-lib-2f-analog

