/*
 * dacChannelConfigurationBuilder.cpp
 *
 *  Created on: Jul 11, 2025
 *      Author: markian
 */

#include "../../../Inc/stm/analog/dac.h"

namespace stm32::analog::dac {

    ChannelConfigurationBuilder &ChannelConfigurationBuilder::enableTrigger(const bool enable) {
        this->configuration.enableTrigger = enable;
        return *this;
    }

    ChannelConfigurationBuilder &ChannelConfigurationBuilder::setTriggerSelection(const uint8_t triggerSelection) {
        if (triggerSelection > 15)
            return *this;
        this->configuration.triggerSelection = triggerSelection;
        return *this;
    }

    ChannelConfigurationBuilder &ChannelConfigurationBuilder::setWaveGeneration(const WaveGeneration waveGeneration) {
        this->configuration.waveGeneration = waveGeneration;
        return *this;
    }

    ChannelConfigurationBuilder &ChannelConfigurationBuilder::setWaveMaskSelection(const uint8_t waveMaskSelection) {
        if (waveMaskSelection > 15)
            return *this;
        this->configuration.waveMaskSelection = waveMaskSelection;
        return *this;
    }

    ChannelConfigurationBuilder &ChannelConfigurationBuilder::enableDma(const bool enable) {
        this->configuration.enableDma = enable;
        return *this;
    }

    ChannelConfigurationBuilder &ChannelConfigurationBuilder::enableDmaUnderrunInterrupt(const bool enable) {
        this->configuration.enableDmaUnderrunInterrupt = enable;
        return *this;
    }

    ChannelConfigurationBuilder &ChannelConfigurationBuilder::enableSoftwareTrigger(const bool enable) {
        this->configuration.enableSoftwareTrigger = enable;
        return *this;
    }

    ChannelConfigurationBuilder &ChannelConfigurationBuilder::enableDmaDoubleDataMode(const bool enable) {
        this->configuration.enableDmaDoubleDataMode = enable;
        return *this;
    }

    ChannelConfigurationBuilder &ChannelConfigurationBuilder::enableSignedMode(const bool enable) {
        this->configuration.enableSignedMode = enable;
        return *this;
    }

    ChannelConfigurationBuilder &ChannelConfigurationBuilder::setHighFrequencyInterfaceMode(const HighFrequencyInterfaceMode mode) {
        this->configuration.highFrequencyInterfaceMode = mode;
        return *this;
    }

    ChannelConfigurationBuilder &ChannelConfigurationBuilder::setChannelMode(const uint8_t mode) {
        if (mode > 7)
            return *this;
        this->configuration.mode = mode;
        return *this;
    }

    ChannelConfigurationBuilder &ChannelConfigurationBuilder::setSampleAndHoldTime(const uint8_t sampleTime, const uint8_t holdTime, const uint8_t refreshTime) {
        this->configuration.sampleTime = sampleTime;
        this->configuration.holdTime = holdTime;
        this->configuration.refreshTime = refreshTime;
        return *this;
    }


    ChannelConfiguration ChannelConfigurationBuilder::build() const {
        return this->configuration;
    }

}


