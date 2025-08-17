//
// Created by Markian on 8/9/2025.
//

#pragma once
#include <cstdint>

namespace arm::nvic {

    struct NvicRegisters {
        volatile uint32_t ISER[8], r0[24], ICER[8], r1[24], ISPR[8], r2[24], ICPR[8], r3[24], IABR[8], r4[56];
        volatile uint8_t IPR[240];
    };

    enum class Irq : uint8_t {
        WWDG = 0,
        PVD_PVM = 1,
        RTC_TAMP_CSS_LSE = 2,
        RTC_WKUP = 3,
        FLASH = 4,
        RCC = 5,
        EXTI0 = 6,
        EXTI1 = 7,
        EXTI2 = 8,
        EXTI3 = 9,
        EXTI4 = 10,
        DMA1_CH1 = 11,
        DMA1_CH2 = 12,
        DMA1_CH3 = 13,
        DMA1_CH4 = 14,
        DMA1_CH5 = 15,
        DMA1_CH6 = 16,
        DMA1_CH7 = 17,
        ADC1_2 = 18,
        USB_HP = 19,
        USB_LP = 20,
        FDCAN1_IT0 = 21,
        FDCAN1_IT1 = 22,
        EXTI9_5 = 23,
        TIM1_BRK_TIM15 = 24,
        TIM1_UP_TIM16 = 25,
        TIM1_TRG_COM_TIM17_TIM1_DIR_TIM1_IDX = 26,
        TIM1_CC = 27,
        TIM2 = 28,
        TIM3 = 29,
        TIM4 = 30,
        I2C1_EV = 31,
        I2C1_ER = 32,
        I2C2_EV = 33,
        I2C2_ER = 34,
        SPI1 = 35,
        SPI2 = 36,
        USART1 = 37,
        USART2 = 38,
        USART3 = 39,
        EXTI15_10 = 40,
        RTC_ALARM = 41,
        USBWakeUP = 42,
        TIM8_BRK_TIM8_TERR_TIM8_IERR = 43,
        TIM8_UP = 44,
        TIM8_TRG_COM_TIM8_DIR_TIM8_IDX = 45,
        TIM8_CC = 46,
        ADC3 = 47,
        FSMC = 48,
        LPTIM1 = 49,
        TIM5 = 50,
        SPI3 = 51,
        UART4 = 52,
        UART5 = 53,
        TIM6_DACUNDER = 54,
        TIM7_DACUNDER = 55,
        DMA2_CH1 = 56,
        DMA2_CH2 = 57,
        DMA2_CH3 = 58,
        DMA2_CH4 = 59,
        DMA2_CH5 = 60,
        ADC4 = 61,
        ADC5 = 62,
        UCPD1_global_interrupt = 63,
        COMP1_2_3 = 64,
        COMP4_5_6 = 65,
        COMP7 = 66,
        HRTIM_Master_IRQn = 67,
        HRTIM_TIMA_IRQn = 68,
        HRTIM_TIMB_IRQn = 69,
        HRTIM_TIMC_IRQn = 70,
        HRTIM_TIMD_IRQn = 71,
        HRTIM_TIME_IRQn = 72,
        HRTIM_TIM_FLT_IRQn = 73,
        HRTIM_TIMF_IRQn = 74,
        CRS = 75,
        SAI = 76,
        TIM20_BRK_TIM20_TERR_TIM20_IERR = 77,
        TIM20_UP = 78,
        TIM20_TRG_COM_TIM20_DIR_TIM20_IDX = 79,
        TIM20_CC = 80,
        FPU = 81,
        I2C4_EV = 82,
        I2C4_ER = 83,
        SPI4 = 84,
        AES = 85,
        FDCAN2_IT0 = 86,
        FDCAN2_IT1 = 87,
        FDCAN3_IT0 = 88,
        FDCAN3_IT1 = 89,
        RNG = 90,
        LPUART = 91,
        I2C3_EV = 92,
        I2C3_ER = 93,
        DMAMUX_OVR = 94,
        QUADSPI = 95,
        DMA1_CH8 = 96,
        DMA2_CH6 = 97,
        DMA2_CH7 = 98,
        DMA2_CH8 = 99,
        CORDIC = 100,
        FMAC = 101
    };

    class Nvic {
        NvicRegisters* registers;

    public:
        Nvic() : registers(reinterpret_cast<NvicRegisters*>(0xE000E100)) {}

        void setInterruptHandler(const uint32_t* handlerAddress) const;

        void enableIrq(Irq irq, bool enable) const;
        void setPendingIrq(Irq irq, bool set) const;
        void setIrqPriority(Irq irq, uint8_t priority) const;

        [[nodiscard]] bool isIrqEnabled(Irq irq) const;
        [[nodiscard]] bool isIrqPending(Irq irq) const;
        [[nodiscard]] uint8_t getIrqPriority(Irq irq) const;
    };

    extern "C" inline void defaultIrqHandler() {
        while (true);
    }

}
