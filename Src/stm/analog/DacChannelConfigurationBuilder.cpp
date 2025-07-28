/*
 * dacChannelConfigurationBuilder.cpp
 *
 *  Created on: Jul 11, 2025
 *      Author: markian
 */

#include "../../../Inc/stm/analog/Dac.h"

namespace stm32::analog::dac {

    DacChannelConfigurationBuilder &DacChannelConfigurationBuilder::enableTrigger(const bool enable) {
        this->configuration.enableTrigger = enable;
        return *this;
    }

    DacChannelConfigurationBuilder &DacChannelConfigurationBuilder::setTriggerSelection(const uint8_t triggerSelection) {
        if (triggerSelection > 15)
            return *this;
        this->configuration.triggerSelection = triggerSelection;
        return *this;
    }

    DacChannelConfigurationBuilder &DacChannelConfigurationBuilder::setWaveGeneration(const WaveGeneration waveGeneration) {
        this->configuration.waveGeneration = waveGeneration;
        return *this;
    }

    DacChannelConfigurationBuilder &DacChannelConfigurationBuilder::setWaveMaskSelection(const uint8_t waveMaskSelection) {
        if (waveMaskSelection > 15)
            return *this;
        this->configuration.waveMaskSelection = waveMaskSelection;
        return *this;
    }

    DacChannelConfigurationBuilder &DacChannelConfigurationBuilder::enableDma(const bool enable) {
        this->configuration.enableDma = enable;
        return *this;
    }

    DacChannelConfigurationBuilder &DacChannelConfigurationBuilder::enableDmaUnderrunInterrupt(const bool enable) {
        this->configuration.enableDmaUnderrunInterrupt = enable;
        return *this;
    }

    DacChannelConfigurationBuilder &DacChannelConfigurationBuilder::enableSoftwareTrigger(const bool enable) {
        this->configuration.enableSoftwareTrigger = enable;
        return *this;
    }

    DacChannelConfigurationBuilder &DacChannelConfigurationBuilder::enableDmaDoubleDataMode(const bool enable) {
        this->configuration.enableDmaDoubleDataMode = enable;
        return *this;
    }

    DacChannelConfigurationBuilder &DacChannelConfigurationBuilder::enableSignedMode(const bool enable) {
        this->configuration.enableSignedMode = enable;
        return *this;
    }

    DacChannelConfigurationBuilder &DacChannelConfigurationBuilder::setHighFrequencyInterfaceMode(const HighFrequencyInterfaceMode mode) {
        this->configuration.highFrequencyInterfaceMode = mode;
        return *this;
    }

    DacChannelConfigurationBuilder &DacChannelConfigurationBuilder::setChannelMode(const uint8_t mode) {
        if (mode > 7)
            return *this;
        this->configuration.mode = mode;
        return *this;
    }

    DacChannelConfigurationBuilder &DacChannelConfigurationBuilder::setSampleAndHoldTime(const uint8_t sampleTime, const uint8_t holdTime, const uint8_t refreshTime) {
        this->configuration.sampleTime = sampleTime;
        this->configuration.holdTime = holdTime;
        this->configuration.refreshTime = refreshTime;
        return *this;
    }

    DacChannelConfiguration DacChannelConfigurationBuilder::build() const {
        return this->configuration;
    }

}


