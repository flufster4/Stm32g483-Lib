cmake_minimum_required(VERSION 3.30)
project(cplusplus)

set(CMAKE_CXX_STANDARD 26)

set(SOURCES
        Src/main.cpp
        Src/stm/sys/Rcc.cpp
        Inc/stm/sys/Rcc.h
        Src/stm/digital/Gpio.cpp
        Inc/stm/digital/Gpio.h
        Src/stm/analog/Dac.cpp
        Inc/stm/analog/Dac.h
        Src/stm/analog/DacChannelConfigurationBuilder.cpp
        Src/stm/analog/Adc.cpp
        Inc/stm/analog/Adc.h
        Src/stm/analog/AdcConversionSequenceBuilder.cpp
        Src/stm/analog/AdcConfigurationBuilder.cpp
        Inc/stm/sys/Dma.h
        Src/stm/sys/Dma.cpp
        Src/stm/sys/DmaChannelConfigurationBuilder.cpp
        Src/stm/sys/DmaMuxGeneratorChannelConfigurationBuilder.cpp
        Src/stm/sys/DmaMuxChannelConfigurationBuilder.cpp
        Src/stm/sys/DmaMux.cpp
        Inc/stm/sys/Tim.h
        Src/stm/sys/tim/BasicTimerConfigurationBuilder.cpp
        Src/stm/sys/tim/BasicTimer.cpp
)

add_executable(cplusplus ${SOURCES})
