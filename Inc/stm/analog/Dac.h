/*
 * dac.h
 *
 *  Created on: Jul 9, 2025
 *      Author: markian
 */

#pragma once
#include <cstdint>

namespace stm32::analog::dac {
     struct DacRegisters {
        volatile uint32_t CR, SWTRGR, DHR12R1, DHR12L1, DHR8R1, DHR12R2, DHR12L2, DHR8R2, DHR12RD, DHR12LD, DHR8RD,
         DOR1, DOR2, SR, CCR, MCR, SHSR1, SHSR2, SHHR, SHRR, r0[2], STR1, STR2, STMODR, r1[2];
    };

    struct DacStatus {
        bool ready, outputRegisterStatus, dmaUnderrun, calibrationOffsetStatus, busyWriting;
    };

    enum class Channel {
        CHANNEL1,
        CHANNEL2,
        DUAL
    };

    enum class DataAlignment {
        LEFT,
        RIGHT
    };

    enum class DataResolution {
        EIGHT_BIT,
        TWELVE_BIT
    };

    enum class WaveGeneration : uint8_t {
        DISBLED = 0,
        NOISE = 1,
        TRIANGLE = 2,
        SAWTOOTH = 3
    };

    enum class HighFrequencyInterfaceMode : uint8_t {
        DISABLED = 0,
        OVER80MHz = 1,
        OVER160MHz = 2
    };

    struct DacChannelConfiguration {
        bool enableTrigger = false;
        uint8_t triggerSelection = 0;
        WaveGeneration waveGeneration = WaveGeneration::DISBLED;
        uint8_t waveMaskSelection = 0;
        bool enableDma = false, enableDmaUnderrunInterrupt = false, enableSoftwareTrigger = false,
            enableDmaDoubleDataMode = false, enableSignedMode = false;
        uint8_t mode = 0;
        HighFrequencyInterfaceMode highFrequencyInterfaceMode = HighFrequencyInterfaceMode::DISABLED;
        uint8_t sampleTime = 0, holdTime = 1, refreshTime = 1;
    };

    class DacChannelConfigurationBuilder {
        DacChannelConfiguration configuration;

    public:
        DacChannelConfigurationBuilder() = default;
        explicit DacChannelConfigurationBuilder(const DacChannelConfiguration& configuration) : configuration(configuration) {}

        DacChannelConfigurationBuilder& enableTrigger(bool enable = true);
        DacChannelConfigurationBuilder& setTriggerSelection(uint8_t triggerSelection);
        DacChannelConfigurationBuilder& setWaveGeneration(WaveGeneration waveGeneration);
        DacChannelConfigurationBuilder& setWaveMaskSelection(uint8_t waveMaskSelection);
        DacChannelConfigurationBuilder& enableDma(bool enable = true);
        DacChannelConfigurationBuilder& enableDmaUnderrunInterrupt(bool enable = true);
        DacChannelConfigurationBuilder& enableSoftwareTrigger(bool enable = true);
        DacChannelConfigurationBuilder& enableDmaDoubleDataMode(bool enable = true);
        DacChannelConfigurationBuilder& enableSignedMode(bool enable = true);
        DacChannelConfigurationBuilder& setChannelMode(uint8_t mode);
        DacChannelConfigurationBuilder& setHighFrequencyInterfaceMode(HighFrequencyInterfaceMode mode);
        DacChannelConfigurationBuilder& setSampleAndHoldTime(uint8_t sampleTime, uint8_t holdTime, uint8_t refreshTime);

        [[nodiscard]] DacChannelConfiguration build() const;
    };

    class Dac {
        DacRegisters* dacRegisters;

    public:
        explicit Dac(const uint32_t dacBaseAddress) : dacRegisters(reinterpret_cast<DacRegisters*>(dacBaseAddress)) {}

        void enable(Channel channel) const;
        void disable(Channel channel) const;

        void configure(DacChannelConfiguration& configuration, Channel channel) const;

        void setOutputValue(uint16_t value, Channel channel, DataAlignment alignment = DataAlignment::RIGHT, DataResolution resolution = DataResolution::TWELVE_BIT) const;
        [[nodiscard]] uint16_t getOutputValue(Channel channel) const;

        [[nodiscard]] DacStatus getStatus(Channel channel) const;

        [[nodiscard]] constexpr static uint16_t voltageToValue(const uint16_t millivolts, const DataResolution dacResolution, const uint16_t vref = 3300) {
            const uint16_t maxCode = dacResolution == DataResolution::TWELVE_BIT ? 4095 : 255;
            return (static_cast<uint32_t>(millivolts) * maxCode + vref / 2) / vref;
        }
    };
}
