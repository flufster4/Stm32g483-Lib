//
// Created by Markian on 8/8/2025.
//

#include "../../../../Inc/stm/sys/Cordic.h"
#include "../../../../Inc/stm/Bit.h"

namespace stm32::system::cordic {

    void Cordic::configure(const CordicConfiguration &configuration) const {
        cordicRegisters->CSR &= ~(MASK<11> | (MASK<7> << 16));
        cordicRegisters->CSR |= (static_cast<uint8_t>(configuration.function) << 0) |
                ((configuration.iterations & MASK<4>) << 4) |
                ((configuration.scaleFactor & MASK<3>) << 8) |
                (configuration.enableReadyInterrupt << 16) |
                (configuration.enableDmaReadRequest << 17) |
                (configuration.enableDmaWriteRequest << 18) |
                (configuration.two32bitResults << 19) |
                (configuration.two32bitArguments << 20) |
                (configuration.sixteenBitOutput << 21) |
                (configuration.sixteenBitArguments << 22);
    }

    CordicConfiguration Cordic::getConfiguration() const {
        return CordicConfiguration{
            static_cast<CordicFunction>(EXTRACT_BITS(cordicRegisters->CSR, 0, MASK<4>)),
            static_cast<uint8_t>(EXTRACT_BITS(cordicRegisters->CSR, 4, MASK<4>)),
            static_cast<uint8_t>(EXTRACT_BITS(cordicRegisters->CSR, 8, MASK<3>)),
            static_cast<bool>(EXTRACT_BITS(cordicRegisters->CSR, 16, 1)),
            static_cast<bool>(EXTRACT_BITS(cordicRegisters->CSR, 17, 1)),
            static_cast<bool>(EXTRACT_BITS(cordicRegisters->CSR, 18, 1)),
            static_cast<bool>(EXTRACT_BITS(cordicRegisters->CSR, 19, 1)),
            static_cast<bool>(EXTRACT_BITS(cordicRegisters->CSR, 20, 1)),
            static_cast<bool>(EXTRACT_BITS(cordicRegisters->CSR, 21, 1)),
            static_cast<bool>(EXTRACT_BITS(cordicRegisters->CSR, 22, 1)),
        };
    }

    void Cordic::setArguments(const uint16_t arg1, const uint16_t arg2) const {
        cordicRegisters->WDATA &= ~MASK<32>;
        cordicRegisters->WDATA |= arg1 | (arg2 << 16);
    }

    void Cordic::setArguments(const uint32_t arg1, const uint32_t arg2) const {
        cordicRegisters->WDATA &= ~MASK<32>;
        cordicRegisters->WDATA |= arg1;
        if (EXTRACT_BITS(cordicRegisters->CSR, 20, 1))
            cordicRegisters->WDATA |= arg2;
    }

    CordicResult Cordic::getResults() const {
        CordicResult result = {};

        if (EXTRACT_BITS(cordicRegisters->CSR, 21, 1)) {
            const auto rawResult = static_cast<int32_t>(cordicRegisters->RDATA);
            result.result1 = static_cast<int32_t>(rawResult & MASK<16>);
            result.result2 = static_cast<int32_t>(EXTRACT_BITS(rawResult, 16, MASK<16>));
            return result;
        }

        result.result1 = static_cast<int32_t>(cordicRegisters->RDATA);
        if (EXTRACT_BITS(cordicRegisters->CSR, 19, 1))
            result.result2 = static_cast<int32_t>(cordicRegisters->RDATA);

        return result;
    }

    bool Cordic::isReady() const {
        return static_cast<bool>(EXTRACT_BITS(cordicRegisters->CSR, 31, 1));
    }


}
