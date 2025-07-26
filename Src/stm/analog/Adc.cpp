/*
 * adc.cpp
 *
 *  Created on: Jul 12, 2025
 *      Author: markian
 */

#include "../../../Inc/stm/analog/Adc.h"

namespace stm32::analog::adc {

    void Adc::disable() const {
        adcRegisters->CR |= 1 << 1;
        while (adcRegisters->CR & 1 << 1);
    }

    void Adc::enable() const {
        adcRegisters->CR |= 1;
    }

    void Adc::startConversion() const {
        adcRegisters->CR |= 1 << 2;
    }

    void Adc::stopConversion() const {
        adcRegisters->CR |= 1 << 4;
        while (adcRegisters->CR & 1 << 4);
    }

    void Adc::startInjectedConversion() const {
        adcRegisters->CR |= 1 << 3;
    }

    void Adc::stopInjectedConversion() const {
        adcRegisters->CR |= 1 << 5;
        while (adcRegisters->CR & 1 << 5);
    }

    void Adc::setDeepPowerDown(const bool enable) const {
        adcRegisters->CR &= ~(1 << 29);
        adcRegisters->CR |= enable << 29;
    }

    AdcStatus Adc::getStatus() const {
        AdcStatus status = {};
        status.ready = adcRegisters->ISR & 1;
        status.eosmp = adcRegisters->ISR & (1 << 1);
        status.eoconv = adcRegisters->ISR & (1 << 2);
        status.eoseq = adcRegisters->ISR & (1 << 3);
        status.overrun = adcRegisters->ISR & (1 << 4);
        status.jeoconv = adcRegisters->ISR & (1 << 5);
        status.jeoseq = adcRegisters->ISR & (1 << 6);
        status.watchdog1 = adcRegisters->ISR & (1 << 7);
        status.watchdog2 = adcRegisters->ISR & (1 << 8);
        status.watchdog3 = adcRegisters->ISR & (1 << 9);
        status.jqovf = adcRegisters->ISR & (1 << 10);
        return status;
    }


}


