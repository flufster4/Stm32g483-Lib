//
// Created by Markian on 7/29/2025.
//

#include "../../../../Inc/stm/sys/Tim.h"

namespace stm32::system::tim {

    void BasicTimer::configure(const BasicTimerConfiguration &configuration) const {
        timerRegisters->CR1 &= ~((0x3 << 2) | (1 << 7) | (0x3 << 11));
        timerRegisters->CR1 |= (configuration.onlyCounterUpdates << 2) |
            (configuration.onePulseMode << 3) |
            (configuration.bufferARR << 7) |
            (configuration.enableRemaping << 11) |
            (configuration.enableDithering << 12);

        timerRegisters->CR2 &= ~(0x7 << 4);
        timerRegisters->CR2 |= (static_cast<uint8_t>(configuration.masterMode) << 4);

        timerRegisters->DIER &= ~(1 | (1 << 8));
        timerRegisters->DIER |= configuration.enableUpdateInterrupt | (configuration.enableUpdateDmaRequest << 8);
    }

    BasicTimerConfiguration BasicTimer::getConfiguration() const {
        return BasicTimerConfiguration{
            static_cast<bool>(timerRegisters->CR1 & (1 << 2)),
            static_cast<bool>(timerRegisters->CR1 & (1 << 3)),
            static_cast<bool>(timerRegisters->CR1 & (1 << 7)),
            static_cast<bool>(timerRegisters->CR1 & (1 << 11)),
            static_cast<bool>(timerRegisters->CR1 & (1 << 12)),
            static_cast<BasicTimerMasterMode>(timerRegisters->CR2 & (0x7 << 4)),
            static_cast<bool>(timerRegisters->DIER & 1),
            static_cast<bool>(timerRegisters->DIER & (1 << 8))
        };
    }

    void BasicTimer::setCounter(const uint16_t count) const {
        timerRegisters->CNT &= ~0xFFFF;
        timerRegisters->CNT |= count;
    }

    void BasicTimer::setClockPrescaler(const uint16_t prescaler) const {
        timerRegisters->PSC &= ~0xFFFF;
        timerRegisters->PSC |= prescaler;
    }

    void BasicTimer::setAutoReloadValue(const uint32_t value) const {
        timerRegisters->ARR &= ~0x7FFFF;
        timerRegisters->ARR |= (value & 0x7FFFF);
    }

    uint16_t BasicTimer::getCount() const {
        return timerRegisters->CNT;
    }

    void BasicTimer::enableUpdates() const {
        timerRegisters->CR1 &= ~(1 << 1);
    }

    void BasicTimer::disableUpdates() const {
        timerRegisters->CR1 |= (1 << 1);
    }

    void BasicTimer::update() const {
        timerRegisters->EGR |= 1;
    }

    void BasicTimer::startCounter() const {
        timerRegisters->CR1 |= 1;
    }

    void BasicTimer::stopCounter() const {
        timerRegisters->CR1 &= ~1;
    }

    bool BasicTimer::isUpdateInterruptFlagSet() const {
        return timerRegisters->SR & 1;
    }


}