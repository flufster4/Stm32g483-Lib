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
)

add_executable(cplusplus ${SOURCES})
