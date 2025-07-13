################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Src/stm/analog/dac.cpp 

OBJS += \
./Src/stm/analog/dac.o 

CPP_DEPS += \
./Src/stm/analog/dac.d 


# Each subdirectory must supply rules for building sources it contributes
Src/stm/analog/%.o Src/stm/analog/%.su Src/stm/analog/%.cyclo: ../Src/stm/analog/%.cpp Src/stm/analog/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++20 -g3 -DDEBUG -DSTM32 -DSTM32G4 -DSTM32G483CETx -c -I../Inc -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-stm-2f-analog

clean-Src-2f-stm-2f-analog:
	-$(RM) ./Src/stm/analog/dac.cyclo ./Src/stm/analog/dac.d ./Src/stm/analog/dac.o ./Src/stm/analog/dac.su

.PHONY: clean-Src-2f-stm-2f-analog

