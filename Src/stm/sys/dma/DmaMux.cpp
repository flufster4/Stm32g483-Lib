//
// Created by Markian on 7/29/2025.
//

#include "../../../../Inc/stm/sys/Dma.h"

namespace stm32::system::dma {

    void DmaMux::configureChannel(const DmaMuxChannelConfiguration &configuration, const DmaMuxChannel channel) const {
        const auto channel_number = static_cast<uint8_t>(channel);
        volatile uint32_t* ccr = &dmaMuxRegisters->C0CR + 0x4 * channel_number;

        *ccr &= ~(0x1FF | (0xFFF << 16));
        *ccr |= static_cast<uint8_t>(configuration.dmaRequest) |
            (configuration.synchronizationOverrunInterrupt << 8) |
            (configuration.enableEventGeneration << 9) |
            (configuration.enableSynchronization << 16) |
            (static_cast<uint8_t>(configuration.synchronizationPolarity) << 17) |
            ((configuration.numberOfRequestsToForward & 0x1F) << 19) |
            (static_cast<uint8_t>(configuration.synchronizationInput) << 24);
    }

    void DmaMux::configureGeneratorChannel(const DmaMuxGeneratorChannelConfiguration &configuration, const DmaMuxGeneratorChannel channel) const {
        const auto channel_number = static_cast<uint8_t>(channel);
        volatile uint32_t* rgcr = &dmaMuxRegisters->RG0CR + 0x4 * channel_number;

        *rgcr &= ~(0xF | (1 << 8) | (0x7F << 16));
        *rgcr |= static_cast<uint8_t>(configuration.signal) |
            (configuration.enableTriggerOverrunInterrupt << 8) |
            (static_cast<uint8_t>(configuration.triggerPolarity) << 17) |
            ((configuration.numberOfRequests & 0x1F) << 19);
    }

    void DmaMux::enableGeneratorChannel(const DmaMuxGeneratorChannel channel) const {
        const auto channel_number = static_cast<uint8_t>(channel);
        volatile uint32_t* rgcr = &dmaMuxRegisters->RG0CR + 0x4 * channel_number;
        *rgcr |= (1 << 16);
    }

    void DmaMux::disableGeneratorChannel(const DmaMuxGeneratorChannel channel) const {
        const auto channel_number = static_cast<uint8_t>(channel);
        volatile uint32_t* rgcr = &dmaMuxRegisters->RG0CR + 0x4 * channel_number;
        *rgcr &= ~(1 << 16);
    }

    bool DmaMux::isChannelSynchronizationOverrun(const DmaMuxChannel channel) const {
        const auto channel_number = static_cast<uint8_t>(channel);
        return dmaMuxRegisters->CSR & (1 << channel_number);
    }

    void DmaMux::clearChannelSynchronizationOverrun(const DmaMuxChannel channel) const {
        const auto channel_number = static_cast<uint8_t>(channel);
        dmaMuxRegisters->CCFR |= (1 << channel_number);
    }

    bool DmaMux::isGeneratorChannelTriggerOverrun(const DmaMuxGeneratorChannel channel) const {
        const auto channel_number = static_cast<uint8_t>(channel);
        return dmaMuxRegisters->RGSR & (1 << channel_number);
    }

    void DmaMux::clearGeneratorChannelTriggerOverrun(const DmaMuxGeneratorChannel channel) const {
        const auto channel_number = static_cast<uint8_t>(channel);
        dmaMuxRegisters->RGCFR |= (1 << channel_number);
    }


}