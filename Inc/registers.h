//
// Created by Oleg Vrublevsky on 5/28/25.
//

#ifndef REGISTERS_H
#define REGISTERS_H

    #ifndef reg
        #define reg volatile unsigned int //4 bytes
    #endif

    typedef struct {
        reg CR;
        reg ICSCR;
        reg CFGR;
        reg PLLCFGR;
        reg r0; // |
        reg r1; // |- 8 reserved bytes
        reg CIER;
        reg CIFR;
        reg CICR;
        reg r2;
        reg AHB1RSTR;
        reg AHB2RSTR;
        reg AHB3RSTR;
        reg r3;
        reg APB1RSTR1;
        reg APB1RSTR2;
        reg APB2RSTR;
        reg r4;
        reg AHB1ENR;
        reg AHB2ENR;
        reg AHB3ENR;
        reg r5;
        reg APB1ENR1;
        reg APB1ENR2;
        reg APB2ENR;
        reg r6;
        reg AHB1SMENR;
        reg AHB2SMENR;
        reg AHB3SMENR;
        reg r7;
        reg APB1SMENR1;
        reg APB1SMENR2;
        reg APB2SMENR;
        reg r8;
        reg CCIPR;
        reg r9;
        reg BDCR;
        reg CSR;
        reg CRRCR;
        reg CCIPR2;
    } RCC_Register_TypeDef;
#endif //REGISTERS_H
