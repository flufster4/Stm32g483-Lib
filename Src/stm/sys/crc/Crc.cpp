//
// Created by Markian on 8/7/2025.
//

#include "../../../../Inc/stm/sys/Crc.h"

namespace stm32::system::crc {

    void Crc::setData(const uint32_t data) const {
        crcRegisters->DR = data;
    }

    uint32_t Crc::getCalculationResult() const {
        return crcRegisters->DR;
    }

    void Crc::setInitalValue(const uint32_t value) const {
        crcRegisters->INIT = value;
    }

    void Crc::setPolynomial(const uint32_t polynomial) const {
        crcRegisters->POL = polynomial;
    }

    void Crc::setPolynomialSize(const CrcPolynomialSize size) const {
        crcRegisters->CR &= ~(0x3 << 3);
        crcRegisters->CR |= (static_cast<uint8_t>(size) << 3);
    }

    void Crc::configureBitReversal(const CrcBitReversalConfiguration configuration) const {
        crcRegisters->CR &= ~(0x3 << 5);
        crcRegisters->CR |= (static_cast<uint8_t>(configuration) << 5);
    }

    void Crc::enableOutputBitReversal(const bool enable) const {
        crcRegisters->CR &= ~(1 << 7);
        crcRegisters->CR |= (enable << 7);
    }

    void Crc::reset() const {
        crcRegisters->CR |= 1;
    }

}