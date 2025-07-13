/*
 * rcc.h
 *
 *  Created on: Jul 9, 2025
 *      Author: markian
 */

#pragma once

namespace stm32::system {
     struct RccRegisters {
        volatile uint32_t CR, ICSCR, CFGR, PLLCFGR, r0[2], CIER, CIFR, CICR, r2, AHB1RSTR, AHB2RSTR, AHB3RSTR, r3,
         APB1RSTR1, APB1RSTR2, APB2RSTR, r4, AHB1ENR, AHB2ENR, AHB3ENR, r5, APB1ENR1, APB1ENR2, APB2ENR, r6, AHB1SMENR,
         AHB2SMENR, AHB3SMENR, r7, APB1SMENR1, APB1SMENR2, APB2SMENR, r8, CCIPR, r9, BDCR, CSR, CRRCR, CCIPR2;
    };
}

