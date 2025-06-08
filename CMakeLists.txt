cmake_minimum_required(VERSION 3.30)
project(test)

set(CMAKE_CXX_STANDARD 14)

add_executable(test
    Src/main.c
    Src/syscalls.c
    Src/sysmem.c
    Startup/startup_stm32g483cetx.s
    STM32G483CETX_FLASH.ld
    STM32G483CETX_RAM.ld
        Inc/util.h
        Inc/registers.h
    Inc/gpio.h
    Src/lib/digital/gpio.c
        Src/lib/analog/dac.c
        Inc/dac.h
        Inc/adc.h
        Src/lib/analog/adc.c
        Src/lib/dma.c
        Inc/dma.h
)
