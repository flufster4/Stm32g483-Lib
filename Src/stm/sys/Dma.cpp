//
// Created by Markian on 7/28/2025.
//

#include "../../../Inc/stm/sys/Dma.h"

namespace stm32::system::dma {

    void Dma::enableChannel(const uint8_t channel) const {
        constexpr uint8_t bndChannel = (channel <= 8) ? channel : 8;
        volatile uint32_t* ccr = &dmaRegisters->ISR + 0x8 + 0x14 * (bndChannel - 1);
        *ccr |= 1;
    }

    void Dma::disableChannel(const uint8_t channel) const {
        constexpr uint8_t bndChannel = (channel <= 8) ? channel : 8;
        volatile uint32_t* ccr = &dmaRegisters->ISR + 0x8 + 0x14 * (bndChannel - 1);
        *ccr &= ~1;
    }

    void Dma::configureChannel(const DmaChannelConfiguration& configuration, const uint8_t channel) const {
        constexpr uint8_t bndChannel = (channel <= 8) ? channel : 8;

        volatile uint32_t* ccr = &dmaRegisters->ISR + 0x8 + 0x14 * (bndChannel - 1);
        volatile uint32_t* cndtr = &dmaRegisters->ISR + 0x0C + 0x14 * (bndChannel - 1);
        volatile uint32_t* cpar = &dmaRegisters->ISR + 0x10 + 0x14 * (bndChannel - 1);
        volatile uint32_t* cmar = &dmaRegisters->ISR + 0x14 + 0x14 * (bndChannel - 1);

        *ccr &= ~0x3FFF;
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
        *cpar |= configuration.peripheralAddress;

        *cmar &= ~0xFFFFFFFF;
        *cmar |= configuration.memoryAddress;
    }

    DmaChannelStatus Dma::getStatus(const uint8_t channel) const {
        constexpr uint8_t bndChannel = ((channel > 8) ? 8 : ((channel < 1) ? 0 : (channel - 1))) * 4; //Offset
        return DmaChannelStatus{
            static_cast<bool>(dmaRegisters->ISR & (1 << bndChannel)),
            static_cast<bool>(dmaRegisters->ISR & (1 << (bndChannel + 1))),
            static_cast<bool>(dmaRegisters->ISR & (1 << (bndChannel + 2))),
            static_cast<bool>(dmaRegisters->ISR & (1 << (bndChannel + 3)))
        };
    }

    void Dma::clearInterruptFlags(const DmaChannelStatus& flags, const uint8_t channel) const {
        constexpr uint8_t bndChannel = ((channel > 8) ? 8 : ((channel < 1) ? 0 : (channel - 1))) * 4; //Offset
        dmaRegisters->IFCR |= (flags.global << bndChannel) |
            (flags.transferComplete << (bndChannel + 1)) |
            (flags.halfTransfer << (bndChannel + 2)) |
            (flags.transferError << (bndChannel + 3));
    }

}
