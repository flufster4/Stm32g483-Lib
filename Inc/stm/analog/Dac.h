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

    struct Status {
        bool ready, outputRegisterStatus, dmaUnderrun, calibrationOffsetStatus, busyWriting;
    };

    enum class Channel {
        Channel1,
        Channel2,
        Dual
    };

    enum class DataAlignment {
        Left,
        Right
    };

    enum class DataResolution {
        EightBit,
        TwelveBit
    };

    enum class WaveGeneration : uint8_t {
        Disabled = 0,
        Noise = 1,
        Triangle = 2,
        Sawtooth = 3
    };

    enum class HighFrequencyInterfaceMode : uint8_t {
        Disabled = 0,
        Over80MHz = 1,
        Over160MHz = 2
    };

    struct ChannelConfiguration {
        bool enableTrigger = false;
        uint8_t triggerSelection = 0;
        WaveGeneration waveGeneration = WaveGeneration::Disabled;
        uint8_t waveMaskSelection = 0;
        bool enableDma = false, enableDmaUnderrunInterrupt = false, enableSoftwareTrigger = false,
            enableDmaDoubleDataMode = false, enableSignedMode = false;
        uint8_t mode = 0;
        HighFrequencyInterfaceMode highFrequencyInterfaceMode = HighFrequencyInterfaceMode::Disabled;
        uint8_t sampleTime = 0, holdTime = 1, refreshTime = 1;
    };

    class ChannelConfigurationBuilder {
        ChannelConfiguration configuration;

    public:
        ChannelConfigurationBuilder() = default;

        ChannelConfigurationBuilder& enableTrigger(bool enable = true);
        ChannelConfigurationBuilder& setTriggerSelection(uint8_t triggerSelection);
        ChannelConfigurationBuilder& setWaveGeneration(WaveGeneration waveGeneration);
        ChannelConfigurationBuilder& setWaveMaskSelection(uint8_t waveMaskSelection);
        ChannelConfigurationBuilder& enableDma(bool enable = true);
        ChannelConfigurationBuilder& enableDmaUnderrunInterrupt(bool enable = true);
        ChannelConfigurationBuilder& enableSoftwareTrigger(bool enable = true);
        ChannelConfigurationBuilder& enableDmaDoubleDataMode(bool enable = true);
        ChannelConfigurationBuilder& enableSignedMode(bool enable = true);
        ChannelConfigurationBuilder& setChannelMode(uint8_t mode);
        ChannelConfigurationBuilder& setHighFrequencyInterfaceMode(HighFrequencyInterfaceMode mode);
        ChannelConfigurationBuilder& setSampleAndHoldTime(uint8_t sampleTime, uint8_t holdTime, uint8_t refreshTime);

        [[nodiscard]] ChannelConfiguration build() const;
    };

    class Dac {
        DacRegisters* dacRegisters;

    public:
        explicit Dac(const uint32_t dacBaseAddress) : dacRegisters(reinterpret_cast<DacRegisters*>(dacBaseAddress)) {}

        void enable(Channel channel) const;
        void disable(Channel channel) const;

        void configure(ChannelConfiguration& configuration, Channel channel) const;

        void setOutputValue(uint16_t value, Channel channel, DataAlignment alignment = DataAlignment::Right, DataResolution resolution = DataResolution::TwelveBit) const;
        [[nodiscard]] uint16_t getOutputValue(Channel channel) const;

        [[nodiscard]] Status getStatus(Channel channel) const;

        [[nodiscard]] constexpr static uint16_t voltageToValue(uint16_t millivolts, DataResolution dacResolution, uint16_t vref = 3300) {
            const uint16_t maxCode = dacResolution == DataResolution::TwelveBit ? 4095 : 255;
            return (static_cast<uint32_t>(millivolts) * maxCode + vref / 2) / vref;
        }
    };
}
