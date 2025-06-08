################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/lib/digital/gpio.c 

OBJS += \
./Src/lib/digital/gpio.o 

C_DEPS += \
./Src/lib/digital/gpio.d 


# Each subdirectory must supply rules for building sources it contributes
Src/lib/digital/%.o Src/lib/digital/%.su Src/lib/digital/%.cyclo: ../Src/lib/digital/%.c Src/lib/digital/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32G4 -DSTM32G483CETx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-lib-2f-digital

clean-Src-2f-lib-2f-digital:
	-$(RM) ./Src/lib/digital/gpio.cyclo ./Src/lib/digital/gpio.d ./Src/lib/digital/gpio.o ./Src/lib/digital/gpio.su

.PHONY: clean-Src-2f-lib-2f-digital

