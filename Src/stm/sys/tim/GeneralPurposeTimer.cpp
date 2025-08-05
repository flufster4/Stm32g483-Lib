//
// Created by Markian on 8/1/2025.
//

#include "../../../../Inc/stm/sys/Tim.h"

namespace stm32::system::tim {

    void GeneralPurposeTimer::configure(const GeneralPurposeTimerConfiguration& configuration) const {
        timerRegisters->CR1 &= ~((0x7F << 2) | (0x3 << 11));
        timerRegisters->CR1 |= (configuration.onlyCounterUpdates << 2) |
            (configuration.onePulseMode << 3) |
            (configuration.downcountingMode << 4) |
            (static_cast<uint8_t>(configuration.centerAlignedMode) << 5) |
            (configuration.bufferedARR << 7) |
            (static_cast<uint8_t>(configuration.filterPrescaler) << 8) |
            (configuration.enableRemapping << 11) |
            (configuration.enableDithering << 12);

        timerRegisters->DIER &= ~(0x1F | (1 << 6) | (0x1F << 8) | (1 << 14) | (0xF << 20));
        timerRegisters->DIER |= configuration.enableUpdateInterrupt |
            (configuration.enableCC1interrupt << 1) |
            (configuration.enableCC2interrupt << 2) |
            (configuration.enableCC3interrupt << 3) |
            (configuration.enableCC4interrupt << 4) |
            (configuration.enableTriggerInterrupt << 6) |
            (configuration.enableUpdateDMArequest << 8) |
            (configuration.enableCC1dmaRequest << 9) |
            (configuration.enableCC2dmaRequest << 10) |
            (configuration.enableCC3dmaRequest << 11) |
            (configuration.enableCC4dmaRequest << 12) |
            (configuration.enableTriggerDMArequest << 14) |
            (configuration.enableIndexInterrupt << 20) |
            (configuration.enableDirectionChangeInterrupt << 21) |
            (configuration.enableIndexErrorInterrupt << 22) |
            (configuration.enableTransitionErrorInterrupt << 23);
    }

    GeneralPurposeTimerConfiguration GeneralPurposeTimer::getConfiguration() const {
        return GeneralPurposeTimerConfiguration{
            static_cast<bool>(timerRegisters->CR1 & (1 << 2)),
            static_cast<bool>(timerRegisters->CR1 & (1 << 3)),
            static_cast<bool>(timerRegisters->CR1 & (1 << 4)),
            static_cast<GeneralPurposeTimerCenterAlignedMode>(timerRegisters->CR1 & (0x3 << 5)),
            static_cast<bool>(timerRegisters->CR1 & (1 << 7)),
            static_cast<GeneralPurposeTimerFilterPrescaler>(timerRegisters->CR1 & (0x3 << 8)),
            static_cast<bool>(timerRegisters->CR1 & (1 << 11)),
            static_cast<bool>(timerRegisters->CR1 & (1 << 12))
        };
    }

    void GeneralPurposeTimer::setClockPrescaler(const uint16_t prescaler) const {
        timerRegisters->PSC &= ~0xFFFF;
        timerRegisters->PSC |= prescaler;
    }

    void GeneralPurposeTimer::setAutoReloadValue(const uint32_t value) const {
        timerRegisters->ARR &= isThirtyTwoBit ? 0xFFFFFFFF : 0x7FFFF;
        timerRegisters->ARR |= isThirtyTwoBit ? value : (value & 0x7FFFF);
    }

    void GeneralPurposeTimer::enableUpdates() const {
        timerRegisters->CR1 &= ~(1 << 1);
    }

    void GeneralPurposeTimer::disableUpdates() const {
        timerRegisters->CR1 |= (1 << 1);
    }

    void GeneralPurposeTimer::update() const {
        timerRegisters->EGR |= 1;
    }

    void GeneralPurposeTimer::startCounter() const {
        timerRegisters->CR1 |= 1;
    }

    void GeneralPurposeTimer::stopCounter() const {
        timerRegisters->CR1 &= ~1;
    }

    uint32_t GeneralPurposeTimer::getCount() const {
        return isThirtyTwoBit ? (timerRegisters->CNT & ~(1 << 31)) : (timerRegisters->CNT & 0xFFFF);
    }

}