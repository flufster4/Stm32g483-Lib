//
// Created by Markian on 8/6/2025.
//

#pragma once
#include <cstdint>

#include "../Result.h"

namespace stm32::system::rng {

    struct RngRegisters {
        volatile uint32_t CR, SR, DR;
    };

    struct RngStatus {
        bool dataReader, clockError, seedError, clockErrorInterrupt, seedErrorInterrupt;
    };

    class RandomNumberGenerator {
        RngRegisters* rngRegisters;

    public:
        explicit RandomNumberGenerator(const uint32_t baseAddress = 0x5006'0800) : rngRegisters(reinterpret_cast<RngRegisters*>(baseAddress)) {}

        void enableInterrupts(bool enable = true) const;
        void enableClockErrorDetection(bool enable = true) const;
        void enableNumberGeneration(bool enable = true) const;

        [[nodiscard]] Result<uint32_t> getValue() const;
        [[nodiscard]] RngStatus getStatus() const;
    };
}
