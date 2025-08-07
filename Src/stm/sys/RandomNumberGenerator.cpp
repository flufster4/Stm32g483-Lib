//
// Created by Markian on 8/6/2025.
//

#include "../../../Inc/stm/sys/Rng.h"

#define EXTRACT_BITS(var, pos, mask) ((var & (mask << pos)) >> pos)

namespace stm32::system::rng {

    void RandomNumberGenerator::enableInterrupts(const bool enable) const {
        rngRegisters->CR &= ~(1 << 3);
        rngRegisters->CR |= (enable << 3);
    }

    void RandomNumberGenerator::enableClockErrorDetection(const bool enable) const {
        rngRegisters->CR &= ~(1 << 5);
        rngRegisters->CR |= (!enable << 5);
    }

    void RandomNumberGenerator::enableNumberGeneration(const bool enable) const {
        rngRegisters->CR &= ~(1 << 2);
        rngRegisters->CR |= (enable << 2);
    }

    Result<uint32_t> RandomNumberGenerator::getValue() const {
        if (!(rngRegisters->SR & 1))
            return Result<uint32_t>::fail("Not ready");
        if (rngRegisters->SR & (1 << 1))
            return Result<uint32_t>::fail("RNG clock too slow");
        if (rngRegisters->SR & (1 << 2))
            return Result<uint32_t>::fail("Seed error");

        return Result<uint32_t>::ok(rngRegisters->DR);
    }

    RngStatus RandomNumberGenerator::getStatus() const {
        return RngStatus{
            static_cast<bool>(EXTRACT_BITS(rngRegisters->SR, 0, 1)),
            static_cast<bool>(EXTRACT_BITS(rngRegisters->SR, 1, 1)),
            static_cast<bool>(EXTRACT_BITS(rngRegisters->SR, 2, 1)),
            static_cast<bool>(EXTRACT_BITS(rngRegisters->SR, 5, 1)),
            static_cast<bool>(EXTRACT_BITS(rngRegisters->SR, 6, 1))
        };
    }

}