################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Src/stm/sys/rcc.cpp 

OBJS += \
./Src/stm/sys/rcc.o 

CPP_DEPS += \
./Src/stm/sys/rcc.d 


# Each subdirectory must supply rules for building sources it contributes
Src/stm/sys/%.o Src/stm/sys/%.su Src/stm/sys/%.cyclo: ../Src/stm/sys/%.cpp Src/stm/sys/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++20 -g3 -DDEBUG -DSTM32 -DSTM32G4 -DSTM32G483CETx -c -I../Inc -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-stm-2f-sys

clean-Src-2f-stm-2f-sys:
	-$(RM) ./Src/stm/sys/rcc.cyclo ./Src/stm/sys/rcc.d ./Src/stm/sys/rcc.o ./Src/stm/sys/rcc.su

.PHONY: clean-Src-2f-stm-2f-sys

