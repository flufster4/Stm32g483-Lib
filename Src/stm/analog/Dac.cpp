/*
 * dac.cpp
 *
 *  Created on: Jul 9, 2025
 *      Author: markian
 */

#include "../../../Inc/stm/analog/Dac.h"

namespace stm32::analog::dac {

    inline uint32_t _get_enable_mask(const Channel channel) {
        switch (channel) {
            case Channel::CHANNEL1: return 1;
            case Channel::CHANNEL2: return 1 << 16;
            case Channel::DUAL: return 1 | 1 << 16;
        }
        return 1;
    }

    void Dac::disable(const Channel channel) const {
        const uint32_t mask = _get_enable_mask(channel);
        dacRegisters->CR &= ~mask;
    }

    void Dac::enable(const Channel channel) const {
        const uint32_t mask = _get_enable_mask(channel);
        dacRegisters->CR |= mask;
    }

    DacStatus Dac::getStatus(const Channel channel) const {
        uint8_t offset = 11;
        if (channel == Channel::CHANNEL2)
            offset = 27;

        return DacStatus{
            static_cast<bool>(dacRegisters->SR & 1 << offset),
            static_cast<bool>(dacRegisters->SR & 1 << (offset + 1)),
            static_cast<bool>(dacRegisters->SR & 1 << (offset + 2)),
            static_cast<bool>(dacRegisters->SR & 1 << (offset + 3)),
            static_cast<bool>(dacRegisters->SR & 1 << (offset + 4))
        };
    }

    uint16_t Dac::getOutputValue(const Channel channel) const {
        const bool b = getStatus(channel).outputRegisterStatus;
        const uint8_t alignmentFactor = b ? 16 : 0;
        const uint32_t mask = 0x7FF << alignmentFactor;

        if (channel == Channel::CHANNEL2)
            return static_cast<uint16_t>((dacRegisters->DOR2 & mask) >> alignmentFactor);
        return static_cast<uint16_t>((dacRegisters->DOR1 & mask) >> alignmentFactor);
    }

    void _setOutputValue8(const uint8_t value, const Channel channel, DacRegisters* dacRegisters) {
        switch (channel) {
            case Channel::CHANNEL1:
                dacRegisters->DHR8R1 &= ~0xFF;
                dacRegisters->DHR8R1 |= value;
                break;
            case Channel::CHANNEL2:
                dacRegisters->DHR8R2 &= ~0xFF;
                dacRegisters->DHR8R2 |= value;
                break;
            case Channel::DUAL:
                dacRegisters->DHR8RD &= ~0xFFFF;
                dacRegisters->DHR8RD |= value | value << 8;
                break;
        }
    }

    void Dac::setOutputValue(const uint16_t value, const Channel channel, const DataAlignment alignment, const DataResolution resolution) const {
        if (resolution == DataResolution::EIGHT_BIT) {
            _setOutputValue8(static_cast<uint8_t>(value), channel, dacRegisters);
            return;
        }

        volatile uint32_t* reg = nullptr;
        switch (channel) {
            case Channel::CHANNEL2: reg = &dacRegisters->DHR12R2; break;
            case Channel::DUAL: reg = &dacRegisters->DHR12RD; break;
            default: reg = &dacRegisters->DHR12R1; break;
        }

        constexpr uint16_t mask = 0xFFF;

        if (alignment == DataAlignment::LEFT) {
            reg += 1;
            *reg &= ~(mask << 4);
            *reg |= (value & mask) << 4;

            if (channel == Channel::DUAL) {
                *reg &= ~(mask << 20);
                *reg |= (value & mask) << 20;
            }

            return;
        }

        *reg &= ~mask;
        *reg |= value & mask;
        if (channel == Channel::DUAL) {
            *reg &= ~(mask << 16);
            *reg |= (value & mask) << 16;
        }
    }

    void Dac::configure(DacChannelConfiguration &configuration, const Channel channel) const {
        const uint8_t offset = (channel == Channel::CHANNEL2) ? 16 : 0;

        if (channel == Channel::DUAL) {
            configure(configuration, Channel::CHANNEL1);
            configure(configuration, Channel::CHANNEL2);
            return;
        }

        dacRegisters->CR &= ~(0x7FFF << offset);
        dacRegisters->CR |= configuration.enableTrigger << (offset + 1);
        dacRegisters->CR |= (configuration.triggerSelection & 0xF) << (offset + 2);
        dacRegisters->CR |= (static_cast<uint8_t>(configuration.waveGeneration) & 0x3) << (offset + 6);
        dacRegisters->CR |= (configuration.waveMaskSelection & 0xF) << (offset + 8);
        dacRegisters->CR |= configuration.enableDma << (offset + 12);
        dacRegisters->CR |= configuration.enableDmaUnderrunInterrupt << (offset + 13);

        dacRegisters->MCR &= ~(0x7 << offset | 0x3 << (offset + 8) | 0x3 << 14);
        dacRegisters->MCR |= (configuration.mode & 0x7) << offset;
        dacRegisters->MCR |= configuration.enableDmaDoubleDataMode << (offset + 8);
        dacRegisters->MCR |= configuration.enableSignedMode << (offset + 9);
        dacRegisters->MCR |= (static_cast<uint8_t>(configuration.highFrequencyInterfaceMode) & 0x3) << 14;

        if (channel == Channel::CHANNEL1) {
            dacRegisters->SHSR1 &= ~0xFF;
            dacRegisters->SHSR1 |= configuration.sampleTime;
        } else {
            dacRegisters->SHSR2 &= ~0xFF;
            dacRegisters->SHSR2 |= configuration.sampleTime;
        }

        dacRegisters->SHHR &= ~(0xFF << offset);
        dacRegisters->SHHR |= configuration.holdTime << offset;
        dacRegisters->SHRR &= ~(0xFF << offset);
        dacRegisters->SHRR |= configuration.refreshTime << offset;
    }
}


