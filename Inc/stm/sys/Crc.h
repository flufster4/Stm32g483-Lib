//
// Created by Markian on 8/7/2025.
//

#pragma once
#include <cstdint>

namespace stm32::system::crc {

    struct CrcRegisters {
        volatile uint32_t DR, IDR, CR, INIT, POL;
    };

    enum class CrcPolynomialSize : uint8_t {
        THIRTY_TWO_BIT = 0,
        SIXTEEN_BIT = 1,
        EIGHT_BIT = 2,
        SEVEN_BIT = 3
    };

    enum class CrcBitReversalConfiguration : uint8_t {
        NONE = 0,
        BY_BYTE = 1,
        BY_HALF_WORD = 2,
        BY_WORD = 3
    };

    class CrcPolynomialBuilder {
        uint32_t polynomial = 0x4C11DB7;
        CrcPolynomialSize width;

    public:
        explicit CrcPolynomialBuilder(const CrcPolynomialSize width) : width(width) {}

        CrcPolynomialBuilder& term(uint8_t term);

        [[nodiscard]] uint32_t build() const;
    };

    class Crc {
        CrcRegisters* crcRegisters;

    public:
        explicit Crc(const uint32_t baseAddress = 0x4002'3000) : crcRegisters(reinterpret_cast<CrcRegisters*>(baseAddress)) {}

        void setData(uint32_t data) const;
        [[nodiscard]] uint32_t getCalculationResult() const;

        void setInitalValue(uint32_t value) const;
        void setPolynomial(uint32_t polynomial) const;

        void setPolynomialSize(CrcPolynomialSize size) const;
        void configureBitReversal(CrcBitReversalConfiguration configuration) const;
        void enableOutputBitReversal(bool enable) const;

        void reset() const;
    };
}
