//
// Created by Markian on 8/7/2025.
//

#include "../../../Inc/stm/sys/Crc.h"

namespace stm32::system::crc {

    CrcPolynomialBuilder &CrcPolynomialBuilder::term(const uint8_t term) {
        const uint8_t maxTerm = [&] {
            switch (width) {
                case CrcPolynomialSize::SEVEN_BIT: return 6;
                case CrcPolynomialSize::EIGHT_BIT: return 7;
                case CrcPolynomialSize::SIXTEEN_BIT: return 15;
                case CrcPolynomialSize::THIRTY_TWO_BIT: return 31;
            }
            return 32;
        }();
        if (term > maxTerm)
            return *this;

        polynomial |= (1 << term);

        return *this;
    }

    uint32_t CrcPolynomialBuilder::build() const {
        return polynomial | 1;
    }

}