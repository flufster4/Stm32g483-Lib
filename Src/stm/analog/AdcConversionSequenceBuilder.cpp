//
// Created by Markian on 7/26/2025.
//

#include "../../../Inc/stm/analog/Adc.h"

namespace stm32::analog::adc {

    AdcConversionSequenceBuilder AdcConversionSequenceBuilder::from(AdcConversionSequence& sequence) {
        return {sequence.sequenceLength, sequence.conversions};
    }

    AdcConversionSequenceBuilder& AdcConversionSequenceBuilder::then(const uint8_t nextConversion) {
        if (sequenceLength >= conversions.size())
            return *this;
        conversions[sequenceLength++] = nextConversion;
        return *this;
    }

    AdcConversionSequenceBuilder &AdcConversionSequenceBuilder::withConversionAtPosition(const uint8_t conversion, const uint8_t position) {
        if (position > conversions.size())
            return *this;
        if (sequenceLength < position)
            sequenceLength = position;

        conversions[position] = conversion;
        return *this;
    }


    AdcConversionSequence AdcConversionSequenceBuilder::build() const {
        return {sequenceLength, conversions};
    }

    size_t AdcConversionSequenceBuilder::getSequenceLength() const {
        return sequenceLength;
    }

    const std::array<uint8_t, 16>& AdcConversionSequenceBuilder::getConversions() const {
        return conversions;
    }


}