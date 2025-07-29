//
// Created by Markian on 7/28/2025.
//

#include "../../../Inc/stm/sys/Dma.h"

namespace stm32::system::dma {

    DmaChannelConfigurationBuilder &DmaChannelConfigurationBuilder::enableInterupts(const bool transferComplete, const bool halfTransfer, const bool transferError) {
        configuration.transferCompleteInterrupt = transferComplete;
        configuration.halfTransferInterrupt = halfTransfer;
        configuration.transferErrorInterrupt = transferError;
        return *this;
    }

    DmaChannelConfigurationBuilder &DmaChannelConfigurationBuilder::setDataDirection(const bool fromMemory) {
        configuration.fromMemory = fromMemory;
        return *this;
    }

    DmaChannelConfigurationBuilder &DmaChannelConfigurationBuilder::enableCircularMode(const bool enable) {
        configuration.circularMode = enable;
        return *this;
    }

    DmaChannelConfigurationBuilder &DmaChannelConfigurationBuilder::enableIncrementMode(const bool peripheralIncrement, const bool memoryIncrement) {
        configuration.peripheralIncrement = peripheralIncrement;
        configuration.memoryIncrement = memoryIncrement;
        return *this;
    }

    DmaChannelConfigurationBuilder &DmaChannelConfigurationBuilder::setDataSize(const DmaDataSize peripheralSize, const DmaDataSize memorySize) {
        configuration.peripheralSize = peripheralSize;
        configuration.memorySize = memorySize;
        return *this;
    }

    DmaChannelConfigurationBuilder &DmaChannelConfigurationBuilder::setPriority(const DmaChannelPriority priority) {
        configuration.priority = priority;
        return *this;
    }

    DmaChannelConfigurationBuilder &DmaChannelConfigurationBuilder::enableMemoryToMemoryMode(const bool enable) {
        configuration.memoryToMemoryMode = enable;
        return *this;
    }

    DmaChannelConfigurationBuilder &DmaChannelConfigurationBuilder::setNumberOfData(const uint16_t amount) {
        configuration.numberOfData = amount;
        return *this;
    }

    DmaChannelConfigurationBuilder &DmaChannelConfigurationBuilder::setDataAddress(const uint32_t peripheralAddress, const uint32_t memoryAddress) {
        configuration.peripheralAddress = peripheralAddress;
        configuration.memoryAddress = memoryAddress;
        return *this;
    }

    DmaChannelConfiguration DmaChannelConfigurationBuilder::build() const {
        return configuration;
    }

}