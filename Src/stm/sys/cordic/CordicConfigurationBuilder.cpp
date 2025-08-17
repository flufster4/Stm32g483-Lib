//
// Created by Markian on 8/7/2025.
//

#include "../../../../Inc/stm/sys/Cordic.h"

namespace stm32::system::cordic {

    CordicConfigurationBuilder &CordicConfigurationBuilder::setFunction(const CordicFunction function) {
        configuration.function = function;
        return *this;
    }

    CordicConfigurationBuilder &CordicConfigurationBuilder::setNumberOfIterations(const uint8_t iterations) {
        const uint8_t boundIterations = (iterations > 15) ? 15 : ((iterations < 1) ? 1 : iterations);
        configuration.iterations = boundIterations;
        return *this;
    }

    CordicConfigurationBuilder &CordicConfigurationBuilder::setScaleFactor(const uint8_t scaleFactor) {
        const uint8_t boundScaleFactor = (scaleFactor > 7) ? 7 : ((scaleFactor < 1) ? 1 : scaleFactor);
        configuration.scaleFactor = boundScaleFactor;
        return *this;
    }

    CordicConfigurationBuilder &CordicConfigurationBuilder::enableReadyInterrupt(bool enable) {
        configuration.enableReadyInterrupt = enable;
        return *this;
    }

    CordicConfigurationBuilder &CordicConfigurationBuilder::enableDma(bool readRequest, bool writeRequest) {
        configuration.enableDmaReadRequest = readRequest;
        configuration.enableDmaWriteRequest = writeRequest;
        return *this;
    }


    CordicConfiguration CordicConfigurationBuilder::build() const {
        return configuration;
    }

}