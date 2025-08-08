//
// Created by Markian on 7/29/2025.
//

#include "../../../../Inc/stm/sys/Dma.h"

namespace stm32::system::dma {

    DmaMuxChannelConfigurationBuilder &DmaMuxChannelConfigurationBuilder::setDmaRequest(const DmaMuxDmaInput request) {
        configuration.dmaRequest = request;
        return *this;
    }

    DmaMuxChannelConfigurationBuilder &DmaMuxChannelConfigurationBuilder::enableSynchronizationOverrunInterrupt(const bool enable) {
        configuration.synchronizationOverrunInterrupt = enable;
        return *this;
    }

    DmaMuxChannelConfigurationBuilder &DmaMuxChannelConfigurationBuilder::enableEventGeneration(const bool enable) {
        configuration.enableEventGeneration = enable;
        return *this;
    }

    DmaMuxChannelConfigurationBuilder &DmaMuxChannelConfigurationBuilder::enableSynchronization(const bool enable) {
        configuration.enableSynchronization = enable;
        return *this;
    }

    DmaMuxChannelConfigurationBuilder &DmaMuxChannelConfigurationBuilder::setSynchronizationPolarity(const DmaMuxSynchronizationPolarity polarity) {
        configuration.synchronizationPolarity = polarity;
        return *this;
    }

    DmaMuxChannelConfigurationBuilder &DmaMuxChannelConfigurationBuilder::setNumberOfRequests(const uint8_t number) {
        configuration.numberOfRequestsToForward = (number > 0) ? (number - 1) : 0;
        return *this;
    }

    DmaMuxChannelConfigurationBuilder &DmaMuxChannelConfigurationBuilder::setSynchronizationInput(const DmaMuxSynchronizationInput input) {
        configuration.synchronizationInput = input;
        return *this;
    }

    DmaMuxChannelConfiguration DmaMuxChannelConfigurationBuilder::build() const {
        return configuration;
    }

}