################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/lib/dma.c 

OBJS += \
./Src/lib/dma.o 

C_DEPS += \
./Src/lib/dma.d 


# Each subdirectory must supply rules for building sources it contributes
Src/lib/%.o Src/lib/%.su Src/lib/%.cyclo: ../Src/lib/%.c Src/lib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32G4 -DSTM32G483CETx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-lib

clean-Src-2f-lib:
	-$(RM) ./Src/lib/dma.cyclo ./Src/lib/dma.d ./Src/lib/dma.o ./Src/lib/dma.su

.PHONY: clean-Src-2f-lib

