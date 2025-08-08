//
// Created by Oleg Vrublevsky on 8/8/25.
//

#pragma once
#include <cstdint>

namespace stm32::system::vrefbuf {

    struct VRefBufRegisters {
        volatile uint32_t CSR, CCR;
    };

    enum class VRefBufVoltage : uint8_t {
        VOLTAGE_2_048 = 0,
        VOLTAGE_2_5 = 1,
        VOLTAGE2_9 = 2
    };

    class VRefBuf {
        VRefBufRegisters* registers;

    public:
        explicit VRefBuf(const uint32_t baseAddress = 0x4001'0030) : registers(reinterpret_cast<VRefBufRegisters*>(baseAddress)) {}

        void configure(VRefBufVoltage voltage, bool highImpedanceMode) const;
        [[deprecated("Trimming value is factory calibrated.")]] void setTrimmingValue(uint8_t value) const;
        void enable(bool enable) const;

        [[nodiscard]] uint8_t getTrimmingValue() const;
        [[nodiscard]] bool isReady() const;
    };
}
