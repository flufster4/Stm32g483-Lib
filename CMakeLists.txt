cmake_minimum_required(VERSION 3.30)
project(cplusplus)

set(CMAKE_CXX_STANDARD 26)

set(SOURCES
    Src/main.cpp
    Src/stm/sys/rcc.cpp
    Inc/stm/sys/rcc.h
    Src/stm/digital/gpio.cpp
    Inc/stm/digital/gpio.h
    Src/stm/analog/dac.cpp
    Inc/stm/analog/dac.h
    Src/stm/analog/dacChannelConfigurationBuilder.cpp
    Src/stm/analog/adc.cpp
    Inc/stm/analog/adc.h
)

add_executable(cplusplus ${SOURCES})
