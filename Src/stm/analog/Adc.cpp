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

    void Adc::setVoltageRegulator(const bool enable) const {
        adcRegisters->CR &= ~(1 << 28);
        adcRegisters->CR |= enable << 28;
    }

    void Adc::setConversionSequence(const AdcConversionSequence& sequence) const {
        constexpr uint8_t conversionMask = 0x1F;
        uint32_t mask = (conversionMask << 24) | (conversionMask << 18) | (conversionMask << 12) | (conversionMask << 6) | 0xF;

        adcRegisters->SQR1 &= ~mask;
        adcRegisters->SQR1 |= (sequence.sequenceLength & 0xF);
        adcRegisters->SQR1 |= (sequence.conversions[0] & conversionMask) << 6;
        adcRegisters->SQR1 |= (sequence.conversions[1] & conversionMask) << 12;
        adcRegisters->SQR1 |= (sequence.conversions[2] & conversionMask) << 18;
        adcRegisters->SQR1 |= (sequence.conversions[3] & conversionMask) << 24;

        if (sequence.sequenceLength <= 4)
            return;
        mask |= (1 << 5);
        adcRegisters->SQR2 &= ~mask;
        adcRegisters->SQR2 |= (sequence.conversions[4] & conversionMask);
        adcRegisters->SQR2 |= (sequence.conversions[5] & conversionMask) << 6;
        adcRegisters->SQR2 |= (sequence.conversions[6] & conversionMask) << 12;
        adcRegisters->SQR2 |= (sequence.conversions[7] & conversionMask) << 18;
        adcRegisters->SQR2 |= (sequence.conversions[8] & conversionMask) << 24;

        if(sequence.sequenceLength <= 9)
            return;
        adcRegisters->SQR3 &= ~mask;
        adcRegisters->SQR3 |= (sequence.conversions[9] & conversionMask);
        adcRegisters->SQR3 |= (sequence.conversions[10] & conversionMask) << 6;
        adcRegisters->SQR3 |= (sequence.conversions[11] & conversionMask) << 12;
        adcRegisters->SQR3 |= (sequence.conversions[12] & conversionMask) << 18;
        adcRegisters->SQR3 |= (sequence.conversions[13] & conversionMask) << 24;

        if(sequence.sequenceLength <= 14)
            return;
        adcRegisters->SQR4 &= ~(conversionMask | (conversionMask << 6));
        adcRegisters->SQR4 |= (sequence.conversions[14] & conversionMask);
        adcRegisters->SQR4 |= (sequence.conversions[15] & conversionMask) << 6;
    }

    void Adc::setSamplingTime(const AdcSamplingTime samplingTime, const uint8_t channel, const bool additionalCycle) const {
        if(channel > 18)
            return;

        adcRegisters->SMPR1 &= ~(1 << 31);
        adcRegisters->SMPR1 |= (additionalCycle << 31);

        volatile uint32_t* reg = &adcRegisters->SMPR1;
        if (channel > 9)
            reg = &adcRegisters->SMPR2;

        *reg &= ~(0x7 << (channel * 3));
        *reg |= ((static_cast<uint8_t>(samplingTime) & 0x7) << (channel * 3));
    }

    uint16_t Adc::getValue() const {
        return static_cast<uint16_t>(adcRegisters->DR);
    }

    AdcCalibration Adc::calibrateAdc() const {
        adcRegisters->CR |= 1 << 31;
        while (adcRegisters->CR & (1 << 31)) {}

        return AdcCalibration{
            static_cast<uint8_t>(adcRegisters->CALDFACT & 0x7F),
            static_cast<uint8_t>((adcRegisters->CALDFACT & (0x7F << 16)) >> 16)
        };
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


