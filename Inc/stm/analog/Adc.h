/*
* adc.h
 *
 *  Created on: Jul 12, 2025
 *      Author: markian
 */

#pragma once
#include <array>
#include <cstdint>

namespace stm32::analog::adc {
    struct AdcRegisters {
       volatile uint32_t ISR, IER, CR, CFGR, CFGR2, SMPR1, SMPR2, r0, TR1, TR2, TR3, r1, SQR1, SQR2, SQR3, SQR4,
        DR, r2[2], JSQR, r3[4], OFR1, OFR2, OFR3, OFR4, r4[4], JDR1, JDR2, JDR3, JDR4, r5[5], AWD2CR, AWD3CR, r6,
        DIFSEL, CALDFACT, r7[2], GCOMP;
    };

    struct AdcCommonRegisters {
        volatile uint8_t CSR, r0, CCR, CDR;
    };

    struct AdcStatus {
        bool ready, eosmp, eoconv, eoseq, overrun, jeoconv, jeoseq, watchdog1, watchdog2, watchdog3, jqovf;
    };

    struct AdcConfiguration {

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

        [[nodiscard]] AdcStatus getStatus() const;
    };
}
