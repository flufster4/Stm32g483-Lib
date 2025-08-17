//
// Created by Markian on 8/7/2025.
//

#pragma once
#include <cstdint>

namespace stm32::system::cordic {

    struct CordicRegisters {
        volatile uint32_t CSR, WDATA, RDATA;
    };

    enum class CordicFunction : uint8_t {
        COSINE = 0,
        SINE = 1,
        PHASE = 2,
        MODULUS = 3,
        ARCTANGENT = 4,
        HYPERBOLIC_COSINE = 5,
        HYPERBOLIC_SINE = 6,
        ARCTANH = 7,
        NATURAL_LOG = 8,
        SQUARE_ROOT = 9
    };

    struct CordicResult {
        uint32_t result1, result2;
    };

    struct CordicConfiguration {
        CordicFunction function = CordicFunction::COSINE;
        uint8_t iterations = 4; //1-15 Inclusive
        uint8_t scaleFactor = 1; //1-7 Inclusive
        bool enableReadyInterrupt = false, enableDmaReadRequest = false, enableDmaWriteRequest = false, two32bitResults = false,
            two32bitArguments = false, sixteenBitOutput = false, sixteenBitArguments = false;
    };

    class CordicConfigurationBuilder {
        CordicConfiguration configuration;
        bool twoResult = false, twoArguments = false;

    public:
        CordicConfigurationBuilder() = default;
        explicit CordicConfigurationBuilder(const CordicConfiguration& configuration) : configuration(configuration) {}

        CordicConfigurationBuilder& setFunction(CordicFunction function);
        CordicConfigurationBuilder& setNumberOfIterations(uint8_t iterations);
        CordicConfigurationBuilder& setScaleFactor(uint8_t scaleFactor);
        CordicConfigurationBuilder& enableReadyInterrupt(bool enable = true);
        CordicConfigurationBuilder& enableDma(bool readRequest, bool writeRequest);
        CordicConfigurationBuilder& setDataCount(bool twoResults, bool twoArguments);
        CordicConfigurationBuilder& setDataWidth(bool sixteenBitResults, bool sixteenBitArguments);

        [[nodiscard]] CordicConfiguration build() const;
    };

    class Cordic {
        CordicRegisters* cordicRegisters;

    public:
        explicit Cordic(const uint32_t baseAddress = 0x4002'0C00) : cordicRegisters(reinterpret_cast<CordicRegisters*>(baseAddress)) {}

        void configure(CordicConfiguration& configuration) const;
        [[nodiscard]] CordicConfiguration getConfiguration() const;

        void setArguments(uint16_t arg1, uint16_t arg2) const;
        void setArguments(uint32_t arg1, uint32_t arg2) const;
        [[nodiscard]] CordicResult getResults() const;
    };
}
