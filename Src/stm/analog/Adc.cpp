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


}


