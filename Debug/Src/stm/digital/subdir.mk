################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Src/stm/digital/gpio.cpp 

OBJS += \
./Src/stm/digital/gpio.o 

CPP_DEPS += \
./Src/stm/digital/gpio.d 


# Each subdirectory must supply rules for building sources it contributes
Src/stm/digital/%.o Src/stm/digital/%.su Src/stm/digital/%.cyclo: ../Src/stm/digital/%.cpp Src/stm/digital/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++20 -g3 -DDEBUG -DSTM32 -DSTM32G4 -DSTM32G483CETx -c -I../Inc -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-stm-2f-digital

clean-Src-2f-stm-2f-digital:
	-$(RM) ./Src/stm/digital/gpio.cyclo ./Src/stm/digital/gpio.d ./Src/stm/digital/gpio.o ./Src/stm/digital/gpio.su

.PHONY: clean-Src-2f-stm-2f-digital

