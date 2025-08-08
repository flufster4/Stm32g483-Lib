//
// Created by Markian on 7/28/2025.
//

#include "../../../Inc/stm/sys/Dma.h"

namespace stm32::system::dma {

    void Dma::enableChannel(const DmaChannel channel) const {
        const auto channel_number = static_cast<uint8_t>(channel);
        volatile uint32_t* ccr = &dmaRegisters->CCR1 + 0x14 * (channel_number - 1);
        *ccr |= 1;
    }

    void Dma::disableChannel(const DmaChannel channel) const {
        const auto channel_number = static_cast<uint8_t>(channel);
        volatile uint32_t* ccr = &dmaRegisters->CCR1 + 0x14 * (channel_number - 1);
        *ccr &= ~1;
    }

    void Dma::configureChannel(const DmaChannelConfiguration& configuration, const DmaChannel channel) const {
        const auto channel_number = static_cast<uint8_t>(channel);

        volatile uint32_t* ccr = &dmaRegisters->CCR1 + 0x14 * (channel_number - 1);
        volatile uint32_t* cndtr = &dmaRegisters->CNDTR1 + 0x14 * (channel_number - 1);
        volatile uint32_t* cpar = &dmaRegisters->CPAR1 + 0x14 * (channel_number - 1);
        volatile uint32_t* cmar = &dmaRegisters->CMAR1 + 0x14 * (channel_number - 1);

        *ccr &= ~0x7FFF;
        *ccr |= (configuration.transferCompleteInterrupt << 1) |
            (configuration.halfTransferInterrupt << 2) |
            (configuration.transferErrorInterrupt << 3) |
            (configuration.fromMemory << 4) |
            (configuration.circularMode << 5) |
            (configuration.peripheralIncrement << 6) |
            (configuration.memoryIncrement << 7) |
            (static_cast<uint8_t>(configuration.peripheralSize) << 8) |
            (static_cast<uint8_t>(configuration.memorySize) << 10) |
            (static_cast<uint8_t>(configuration.priority) << 12) |
            (configuration.memoryToMemoryMode << 14);

        *cndtr &= ~0xFFFF;
        *cndtr |= configuration.numberOfData;

        *cpar &= ~0xFFFFFFFF;
        *cpar = (uint32_t)configuration.peripheralAddress;

        *cmar &= ~0xFFFFFFFF;
        *cmar = (uint32_t)configuration.memoryAddress;
    }

    DmaChannelStatus Dma::getStatus(const DmaChannel channel) const {
        const uint8_t channelOffset = (static_cast<uint8_t>(channel) - 1) * 4;
        return DmaChannelStatus{
            static_cast<bool>(dmaRegisters->ISR & (1 << channelOffset)),
            static_cast<bool>(dmaRegisters->ISR & (1 << (channelOffset + 1))),
            static_cast<bool>(dmaRegisters->ISR & (1 << (channelOffset + 2))),
            static_cast<bool>(dmaRegisters->ISR & (1 << (channelOffset + 3)))
        };
    }

    void Dma::clearInterruptFlags(const DmaChannelStatus& flags, const DmaChannel channel) const {
        const uint8_t channelOffset = (static_cast<uint8_t>(channel) - 1) * 4;
        dmaRegisters->IFCR |= (flags.global << channelOffset) |
            (flags.transferComplete << (channelOffset + 1)) |
            (flags.halfTransfer << (channelOffset + 2)) |
            (flags.transferError << (channelOffset + 3));
    }

}
