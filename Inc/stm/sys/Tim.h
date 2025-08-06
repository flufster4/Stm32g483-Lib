//
// Created by Markian on 7/29/2025.
//

#pragma once
#include <cstdint>

#include "./BasicTim.h"
#include "./GeneralPurposeTim.h"

#warning "Please include each timer header individually."

namespace stm32::system::tim {

    struct AdvancedControlTimerRegisters {
        volatile uint32_t CR1, CR2, SMCR, DIER, SR, EGR, CCMR1, CCMR2, CCER, CNT, PSC, ARR, RCR, CCR1, CCR2, CCR3, CCR4,
            BDTR, CCR5, CCR6, CCMR3, DTR2, ECR, TISEL, AF1, AF2, r2[221], DCR, DMAR;
    };

    struct Timer15Registers {
        volatile uint32_t CR1, CR2, SMCR, DIER, SR, EGR, CCMR1, CCER, CNT, PSC, ARR, RCR, CCR1, CCR2, r0[3], BDTR, r1[3],
            DTR2, r2, TISEL, AF1, AF2, r3[221], DCR, DMAR;
    };

    struct Timer16and17Registers {
        volatile uint32_t CR1, CR2, r0, DIER, SR, EGR, CCMR1, r1, CCER, CNT, PSC, ARR, RCR, CCR1, r2[3], BDTR, r3[3],
            DTR2, r4, TISEL, AF1, AF2, OR1, r5[221], DCR, DMAR;
    };

    struct LowPowerTimerRegisters {
        volatile uint32_t ISR, ICR, IER, CFGR, CR, CMP, ARR, CNT, OR;
    };
}
