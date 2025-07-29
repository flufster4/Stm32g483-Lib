//
// Created by Markian on 7/28/2025.
//

#include "../../../Inc/stm/analog/Adc.h"

namespace stm32::analog::adc {

    AdcConfigurationBuilder &AdcConfigurationBuilder::enableDma(const bool enable, const bool circularMode) {
        configuration.enableDma = enable;
        configuration.dmaCircularMode = circularMode;
        return *this;
    }

    AdcConfigurationBuilder &AdcConfigurationBuilder::setDataResolution(const AdcDataResolution resolution) {
        configuration.dataResolution = resolution;
        return *this;
    }

    AdcConfigurationBuilder &AdcConfigurationBuilder::setExternalTrigger(const uint8_t trigger, const AdcTriggerEdge edge) {
        configuration.rExternalTrigger = trigger;
        configuration.rTriggerEdge = edge;
        return *this;
    }

    AdcConfigurationBuilder &AdcConfigurationBuilder::enableOverrunOverwriteMode(const bool enable) {
        configuration.overrunOverwrite = enable;
        return *this;
    }

    AdcConfigurationBuilder &AdcConfigurationBuilder::enableContinuousConversionMode(const bool enable) {
        configuration.rContinuousConversion = enable;
        return *this;
    }

    AdcConfigurationBuilder &AdcConfigurationBuilder::enableDelayedConversionMode(const bool enable) {
        configuration.delayedConversion = enable;
        return *this;
    }

    AdcConfigurationBuilder &AdcConfigurationBuilder::enableLeftDataAlignment(const bool enable) {
        configuration.leftAligned = enable;
        return *this;
    }

    AdcConfigurationBuilder &AdcConfigurationBuilder::enableDiscontinuousConversionMode(const bool regularChannels, const bool injectedChannels, const uint8_t channelCount) {
        configuration.rDiscontinuousConversion = regularChannels;
        configuration.jDiscontinuousConversion = injectedChannels;
        configuration.discontinuousChannelCount = channelCount;
        return *this;
    }

    AdcConfigurationBuilder &AdcConfigurationBuilder::enableWatchdog(const bool allChannels, const bool regularChannels, const bool injectedChannels, const uint8_t channelSelection) {
        configuration.watchdog1OnAllChannels = allChannels;
        configuration.rEnableWatchdog1 = regularChannels;
        configuration.jEnableWatchdog1 = injectedChannels;
        configuration.watchDog1ChannelSelection = channelSelection;
        return *this;
    }

    AdcConfigurationBuilder &AdcConfigurationBuilder::enableInjectedQueue(const bool enable) {
        configuration.enableInjectedQueue = enable;
        return *this;
    }

    AdcConfigurationBuilder &AdcConfigurationBuilder::enableAutomaticInjectedGroupConversion(const bool enable) {
        configuration.jAutomaticGroupConversion = enable;
        return *this;
    }

    AdcConfigurationBuilder &AdcConfigurationBuilder::enableOversampling(const bool regular, const bool injected) {
        configuration.rEnableOversampling = regular;
        configuration.jEnableOversampling = injected;
        return *this;
    }

    AdcConfigurationBuilder &AdcConfigurationBuilder::setOversamplingRatio(const AdcOversamplingRatio ratio) {
        configuration.oversamplingRatio = ratio;
        return *this;
    }

    AdcConfigurationBuilder &AdcConfigurationBuilder::setOversamplingShift(const AdcOversamplingShift shift) {
        configuration.oversamplingShift = shift;
        return *this;
    }

    AdcConfigurationBuilder &AdcConfigurationBuilder::enableTriggeredOversampling(const bool enable) {
        configuration.rTriggeredOversampling = enable;
        return *this;
    }

    AdcConfigurationBuilder &AdcConfigurationBuilder::enableOversamplingResumedMode(const bool enable) {
        configuration.rOversamplingResumedMode = enable;
        return *this;
    }

    AdcConfigurationBuilder &AdcConfigurationBuilder::enableGainCompensation(const bool enable) {
        configuration.enableGainCompensation = enable;
        return *this;
    }

    AdcConfigurationBuilder &AdcConfigurationBuilder::enableBulbSamplingMode(const bool enable) {
        configuration.enableBulbSampling = enable;
        return *this;
    }

    AdcConfigurationBuilder &AdcConfigurationBuilder::enableSamplingTimeCtrlTrigger(const bool enable) {
        configuration.enableSamplingTimeCtrlTrigger = enable;
        return *this;
    }

    AdcConfiguration AdcConfigurationBuilder::build() const {
        return configuration;
    }

}
