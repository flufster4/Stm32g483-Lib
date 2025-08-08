//
// Created by Oleg Vrublevsky on 8/8/25.
//

#include "../../../Inc/stm/sys/VRefBuf.h"

namespace stm32::system::vrefbuf {

    void VRefBuf::configure(const VRefBufVoltage voltage, const bool highImpedanceMode) const {
        registers->CSR &= ~((1 << 1) | (0x3 << 4));
        registers->CSR |= (highImpedanceMode << 1) | (static_cast<uint32_t>(voltage) << 4);
    }

    void VRefBuf::setTrimmingValue(const uint8_t value) const {
        const uint8_t boundValue = (value > 0x3F) ? 0x3F : value;
        registers->CCR &= ~0x3F;
        registers->CCR |= boundValue;
    }

    void VRefBuf::enable(const bool enable) const {
        registers->CSR &= ~1;
        registers->CSR |= enable;
    }

    uint8_t VRefBuf::getTrimmingValue() const {
        return registers->CCR & 0x3F;
    }

    bool VRefBuf::isReady() const {
        return registers->CSR & (1 << 3);
    }

}