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
        Src/stm/sys/dma/Dma.cpp
        Src/stm/sys/dma/DmaChannelConfigurationBuilder.cpp
        Src/stm/sys/dma/DmaMuxGeneratorChannelConfigurationBuilder.cpp
        Src/stm/sys/dma/DmaMuxChannelConfigurationBuilder.cpp
        Src/stm/sys/dma/DmaMux.cpp
        Inc/stm/sys/Tim.h
        Src/stm/sys/tim/BasicTimerConfigurationBuilder.cpp
        Src/stm/sys/tim/BasicTimer.cpp
        Src/stm/sys/tim/GeneralPurposeTimerConfigurationBuilder.cpp
        Src/stm/sys/tim/GeneralPurposeTimer.cpp
        Inc/stm/Result.h
        Inc/stm/sys/GeneralPurposeTim.h
        Inc/stm/sys/BasicTim.h
        Inc/stm/sys/Rng.h
        Src/stm/sys/Rng.cpp
        Inc/stm/sys/Crc.h
        Src/stm/sys/crc/CrcPolynomialBuilder.cpp
        Src/stm/sys/crc/Crc.cpp
        Inc/stm/sys/Device.h
        Src/stm/sys/Device.cpp
        Inc/stm/sys/VRefBuf.h
        Src/stm/sys/VRefBuf.cpp
        Inc/stm/sys/Cordic.h
        Src/stm/sys/cordic/CordicConfigurationBuilder.cpp
)

add_executable(cplusplus ${SOURCES})
