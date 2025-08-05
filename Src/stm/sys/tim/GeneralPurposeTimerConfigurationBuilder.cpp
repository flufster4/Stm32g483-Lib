//
// Created by Markian on 8/1/2025.
//

#include "../../../../Inc/stm/sys/Tim.h"

namespace stm32::system::tim {

    GeneralPurposeTimerConfigurationBuilder &GeneralPurposeTimerConfigurationBuilder::enableOnlyCounterUpdates(const bool enable) {
        configuration.onlyCounterUpdates = enable;
        return *this;
    }

    GeneralPurposeTimerConfigurationBuilder &GeneralPurposeTimerConfigurationBuilder::enableOnePulseMode(const bool enable) {
        configuration.onePulseMode = enable;
        return *this;
    }

    GeneralPurposeTimerConfigurationBuilder &GeneralPurposeTimerConfigurationBuilder::enableDowncountingMode(const bool enable) {
        configuration.downcountingMode = enable;
        return *this;
    }

    GeneralPurposeTimerConfigurationBuilder &GeneralPurposeTimerConfigurationBuilder::setCenterAlignedMode(const GeneralPurposeTimerCenterAlignedMode mode) {
        configuration.centerAlignedMode = mode;
        return *this;
    }

    GeneralPurposeTimerConfigurationBuilder &GeneralPurposeTimerConfigurationBuilder::enableARRbuffering(const bool enable) {
        configuration.bufferedARR = enable;
        return *this;
    }

    GeneralPurposeTimerConfigurationBuilder &GeneralPurposeTimerConfigurationBuilder::setFilterPrescaler(const GeneralPurposeTimerFilterPrescaler prescaler) {
        configuration.filterPrescaler = prescaler;
        return *this;
    }

    GeneralPurposeTimerConfigurationBuilder &GeneralPurposeTimerConfigurationBuilder::enableRemapping(const bool enable) {
        configuration.enableRemapping = enable;
        return *this;
    }

    GeneralPurposeTimerConfigurationBuilder &GeneralPurposeTimerConfigurationBuilder::enableDithering(const bool enable) {
        configuration.enableDithering = enable;
        return *this;
    }

    GeneralPurposeTimerConfigurationBuilder &GeneralPurposeTimerConfigurationBuilder::enableCCdmaRequestOnUpdate(const bool enable) {
        configuration.disableCCdmaRequest = enable;
        return *this;
    }

    GeneralPurposeTimerConfiguration GeneralPurposeTimerConfigurationBuilder::build() const {
        return configuration;
    }

    GeneralPurposeTimerConfigurationBuilder &GeneralPurposeTimerConfigurationBuilder::enableCaptureCompareInterrupts(const bool cc1, const bool cc2, const bool cc3, const bool cc4) {
        configuration.enableCC1interrupt = cc1;
        configuration.enableCC2interrupt = cc2;
        configuration.enableCC3interrupt = cc3;
        configuration.enableCC4interrupt = cc4;
        return *this;
    }

    GeneralPurposeTimerConfigurationBuilder &GeneralPurposeTimerConfigurationBuilder::enableCaptureCompareDmaRequests(const bool cc1, const bool cc2, const bool cc3, const bool cc4) {
        configuration.enableCC1dmaRequest = cc1;
        configuration.enableCC2dmaRequest = cc2;
        configuration.enableCC3dmaRequest = cc3;
        configuration.enableCC4dmaRequest = cc4;
        return *this;
    }

    GeneralPurposeTimerConfigurationBuilder &GeneralPurposeTimerConfigurationBuilder::enableInterrupts(const bool update, const bool trigger, const bool index, const bool directionChange, const bool indexError, const bool transitionError) {
        configuration.enableUpdateInterrupt = update;
        configuration.enableTriggerInterrupt = trigger;
        configuration.enableIndexInterrupt = index;
        configuration.enableDirectionChangeInterrupt = directionChange;
        configuration.enableIndexErrorInterrupt = indexError;
        configuration.enableTransitionErrorInterrupt = transitionError;
        return *this;
    }

    GeneralPurposeTimerConfigurationBuilder &GeneralPurposeTimerConfigurationBuilder::enableDmaRequests(const bool update, const bool trigger) {
        configuration.enableUpdateDMArequest = update;
        configuration.enableTriggerDMArequest = trigger;
        return *this;
    }

}