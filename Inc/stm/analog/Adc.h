/*
* adc.h
 *
 *  Created on: Jul 12, 2025
 *      Author: markian
 */

#pragma once
#include <array>
#include <cstdint>
#include <cstddef>

namespace stm32::analog::adc {
    struct AdcRegisters {
       volatile uint32_t ISR, IER, CR, CFGR, CFGR2, SMPR1, SMPR2, r0, TR1, TR2, TR3, r1, SQR1, SQR2, SQR3, SQR4,
        DR, r2[2], JSQR, r3[4], OFR1, OFR2, OFR3, OFR4, r4[4], JDR1, JDR2, JDR3, JDR4, r5[5], AWD2CR, AWD3CR, r6,
        DIFSEL, CALDFACT, r7[2], GCOMP;
    };

    struct AdcCommonRegisters {
        volatile uint8_t CSR, r0, CCR, CDR;
    };

    enum class AdcSamplingTime : uint8_t {
        CYCLES_2_5,
        CYCLES_6_5,
        CYCLES_12_5,
        CYCLES_24_5,
        CYCLES_47_5,
        CYCLES_92_5,
        CYCLES_247_5,
        CYCLES_640_5
    };

    enum class AdcDataResolution : uint8_t {
        TWELVE_BIT = 0,
        TEN_BIT = 1,
        EIGTH_BIT = 2,
        SIX_BIT = 3
    };

    enum class AdcTriggerEdge {
        DISABLED = 0,
        RISING_EDGE = 1,
        FALLING_EDGE = 2,
        BOTH = 3
    };

    enum class AdcOversamplingRatio : uint8_t {
        TWO = 0,
        FOUR = 1,
        EIGHT = 2,
        SIXTEEN = 3,
        THIRTY_TWO = 4,
        SIXTY_FOUR = 5,
        HUNDRED_TWENTY_EIGHT = 6,
        TWO_HUNDRED_FIFTY_SIX = 7
    };

    enum class AdcOversamplingShift : uint8_t {
        NONE = 0,
        ONE_BIT = 1,
        TWO_BIT = 2,
        THREE_BIT = 3,
        FOUR_BIT = 4,
        FIVE_BIT = 5,
        SIX_BIT = 6,
        SEVEN_BIT = 7,
        EIGHT_BIT = 8
    };

    struct AdcStatus {
        bool ready, eosmp, eoconv, eoseq, overrun, jeoconv, jeoseq, watchdog1, watchdog2, watchdog3, jqovf;
    };

    struct AdcCalibration {
        uint8_t S, D;
    };

    struct AdcConfiguration {
        bool enableDma = false, dmaCircularMode = false;
        AdcDataResolution dataResolution = AdcDataResolution::TWELVE_BIT;
        uint8_t rExternalTrigger = 0;
        AdcTriggerEdge rTriggerEdge = AdcTriggerEdge::DISABLED;
        bool overrunOverwrite = false, rContinuousConversion = false, delayedConversion = false, leftAligned = false,
            rDiscontinuousConversion = true;
        uint8_t discontinuousChannelCount = 0;
        bool jDiscontinuousConversion = true, watchdog1OnAllChannels = false, rEnableWatchdog1 = false, jEnableWatchdog1 = false,
            jAutomaticGroupConversion = false, enableInjectedQueue = false;
        uint8_t watchDog1ChannelSelection = 0;
        bool rEnableOversampling = false, jEnableOversampling = false;
        AdcOversamplingRatio oversamplingRatio = AdcOversamplingRatio::TWO;
        AdcOversamplingShift oversamplingShift = AdcOversamplingShift::NONE;
        bool rTriggeredOversampling = false, rOversamplingResumedMode = false, enableGainCompensation = false,
            enableBulbSampling = false, enableSamplingTimeCtrlTrigger = false;
    };

    class AdcConfigurationBuilder {
        AdcConfiguration configuration;

    public:
        AdcConfigurationBuilder() = default;
        explicit AdcConfigurationBuilder(const AdcConfiguration& configuration) : configuration(configuration) {}

        AdcConfigurationBuilder& enableDma(bool enable, bool circularMode);
        AdcConfigurationBuilder& setDataResolution(AdcDataResolution resolution);
        AdcConfigurationBuilder& setExternalTrigger(uint8_t trigger, AdcTriggerEdge edge);
        AdcConfigurationBuilder& enableOverrunOverwriteMode(bool enable = true);
        AdcConfigurationBuilder& enableContinuousConversionMode(bool enable = true);
        AdcConfigurationBuilder& enableDelayedConversionMode(bool enable = true);
        AdcConfigurationBuilder& enableLeftDataAlignment(bool enable = true);
        AdcConfigurationBuilder& enableDiscontinuousConversionMode(bool regularChannels, bool injectedChannels, uint8_t channelCount);
        AdcConfigurationBuilder& enableWatchdog(bool allChannels, bool regularChannels, bool injectedChannels, uint8_t channelSelection);
        AdcConfigurationBuilder& enableInjectedQueue(bool enable = true);
        AdcConfigurationBuilder& enableAutomaticInjectedGroupConversion(bool enable = true);
        AdcConfigurationBuilder& enableOversampling(bool regular, bool injected);
        AdcConfigurationBuilder& setOversamplingRation(AdcOversamplingRatio ratio);
        AdcConfigurationBuilder& setOversamplingShift(AdcOversamplingShift shift);
        AdcConfigurationBuilder& enableTriggeredOversampling(bool enable = true);
        AdcConfigurationBuilder& enableOversamplingResumedMode(bool enable = true);
        AdcConfigurationBuilder& enableGainCompensation(bool enable = true);
        AdcConfigurationBuilder& enableBulbSamplingMode(bool enable = true);
        AdcConfigurationBuilder& enableSamplingTimeCtrlTrigger(bool enable = true);

        [[nodiscard]] AdcConfiguration build() const;
    };

    struct AdcConversionSequence {
        size_t sequenceLength;
        std::array<uint8_t, 16> conversions;
    };

    class AdcConversionSequenceBuilder {
        size_t sequenceLength = 0;
        std::array<uint8_t, 16> conversions{};

        AdcConversionSequenceBuilder(const size_t sequenceLength, const std::array<uint8_t, 16> conversions) : sequenceLength(sequenceLength), conversions(conversions) {}

    public:
        explicit AdcConversionSequenceBuilder(const uint8_t firstConversion) : sequenceLength(1), conversions({firstConversion}) {}
        [[nodiscard]] static AdcConversionSequenceBuilder from(AdcConversionSequence& sequence);

        AdcConversionSequenceBuilder& then(uint8_t nextConversion);
        AdcConversionSequenceBuilder& withConversionAtPosition(uint8_t conversion, uint8_t position);
        [[nodiscard]] AdcConversionSequence build() const;

        [[nodiscard]] size_t getSequenceLength() const;
        [[nodiscard]] const std::array<uint8_t, 16>& getConversions() const;
    };

    class Adc {
        AdcRegisters* adcRegisters;

    public:
        explicit Adc(const uint32_t adcBaseAddress) : adcRegisters(reinterpret_cast<AdcRegisters*>(adcBaseAddress)) {}

        void disable() const;
        void enable() const;
        void setVoltageRegulator(bool enable = true) const;
        void setDeepPowerDown(bool enable = false) const;

        void startConversion() const;
        void stopConversion() const;
        void startInjectedConversion() const;
        void stopInjectedConversion() const;

        void configureAdc(const AdcConfiguration& config) const;
        void setConversionSequence(const AdcConversionSequence& sequence) const;
        void setSamplingTime(AdcSamplingTime samplingTime, uint8_t channel, bool additionalCycle = false) const;

        AdcCalibration calibrateAdc(bool differential = false) const;
        void calibrateAdc(const AdcCalibration& calibration) const;

        [[nodiscard]] uint16_t getValue() const;
        [[nodiscard]] AdcStatus getStatus() const;
    };
}
