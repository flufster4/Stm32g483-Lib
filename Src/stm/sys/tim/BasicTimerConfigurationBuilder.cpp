//
// Created by Markian on 7/29/2025.
//

#include "../../../../Inc/stm/sys/Tim.h"

namespace stm32::system::tim {

    BasicTimerConfigurationBuilder &BasicTimerConfigurationBuilder::enableOnlyCounterUpdates(const bool enable) {
        configuration.onlyCounterUpdates = enable;
        return *this;
    }

    BasicTimerConfigurationBuilder &BasicTimerConfigurationBuilder::enableOnePulseMode(const bool enable) {
        configuration.onePulseMode = enable;
        return *this;
    }

    BasicTimerConfigurationBuilder &BasicTimerConfigurationBuilder::enableARRbuffering(const bool enable) {
        configuration.bufferARR = enable;
        return *this;
    }

    BasicTimerConfigurationBuilder &BasicTimerConfigurationBuilder::enableRemapping(const bool enable) {
        configuration.enableRemaping = enable;
        return *this;
    }

    BasicTimerConfigurationBuilder &BasicTimerConfigurationBuilder::enableDithering(const bool enable) {
        configuration.enableDithering = enable;
        return *this;
    }

    BasicTimerConfigurationBuilder &BasicTimerConfigurationBuilder::setMasterMode(BasicTimerMasterMode mode) {
        configuration.masterMode = mode;
        return *this;
    }

    BasicTimerConfigurationBuilder &BasicTimerConfigurationBuilder::enableUpdateInterrupt(const bool enable) {
        configuration.enableUpdateInterrupt = enable;
        return *this;
    }

    BasicTimerConfigurationBuilder &BasicTimerConfigurationBuilder::enableUpdateDmaRequest(const bool enable) {
        configuration.enableUpdateDmaRequest = enable;
        return *this;
    }

    BasicTimerConfiguration BasicTimerConfigurationBuilder::build() const {
        return configuration;
    }

}