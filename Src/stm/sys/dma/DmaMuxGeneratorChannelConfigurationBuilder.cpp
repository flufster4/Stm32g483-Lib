//
// Created by Markian on 7/29/2025.
//

#include "../../../../Inc/stm/sys/Dma.h"

namespace stm32::system::dma {

    DmaMuxGeneratorChannelConfigurationBuilder &DmaMuxGeneratorChannelConfigurationBuilder::setSignal(const DmaMuxDmaInput signal) {
        configuration.signal = signal;
        return *this;
    }

    DmaMuxGeneratorChannelConfigurationBuilder &DmaMuxGeneratorChannelConfigurationBuilder::enableTriggerOverrunInterrupt(const bool enable) {
        configuration.enableTriggerOverrunInterrupt = enable;
        return *this;
    }

    DmaMuxGeneratorChannelConfigurationBuilder &DmaMuxGeneratorChannelConfigurationBuilder::setTriggerPolarity(const DmaMuxSynchronizationPolarity polarity) {
        configuration.triggerPolarity = polarity;
        return *this;
    }

    DmaMuxGeneratorChannelConfigurationBuilder &DmaMuxGeneratorChannelConfigurationBuilder::setNumberOfRequests(const uint8_t number) {
        configuration.numberOfRequests = (number > 0) ? (number - 1) : 0;
        return *this;
    }

    DmaMuxGeneratorChannelConfiguration DmaMuxGeneratorChannelConfigurationBuilder::build() const {
        return configuration;
    }

}