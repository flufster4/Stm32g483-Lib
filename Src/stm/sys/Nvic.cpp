//
// Created by Markian on 8/9/2025.
//

#include "../../../Inc/stm/sys/Nvic.h"
#include "../../../Inc/stm/Bit.h"

namespace arm::nvic {

    void Nvic::enableIrq(const Irq irq, const bool enable) const {
        const auto irqNum = static_cast<uint8_t>(irq);
        if (enable)
            registers->ISER[irqNum / 32] |= (1 << (irqNum % 32));
        else
            registers->ICER[irqNum / 32] |= (1 << (irqNum % 32));
    }

    void Nvic::setPendingIrq(const Irq irq, const bool set) const {
        const auto irqNum = static_cast<uint8_t>(irq);
        if (set)
            registers->ISPR[irqNum / 32] |= (1 << (irqNum % 32));
        else
            registers->ICPR[irqNum / 32] |= (1 << (irqNum % 32));
    }

    void Nvic::setIrqPriority(const Irq irq, const uint8_t priority) const {
        const auto irqNum = static_cast<uint8_t>(irq);
        const uint8_t boundPriority = (priority > 15) ? 15 : priority;
        registers->IPR[irqNum] = boundPriority << 4;
    }

    bool Nvic::isIrqEnabled(Irq irq) const {
        const auto irqNum = static_cast<uint8_t>(irq);
        return EXTRACT_BITS(registers->ISER[irqNum / 32], irqNum & 32, 1);
    }

    bool Nvic::isIrqPending(Irq irq) const {
        const auto irqNum = static_cast<uint8_t>(irq);
        return EXTRACT_BITS(registers->ISPR[irqNum / 32], irqNum & 32, 1);
    }

    uint8_t Nvic::getIrqPriority(Irq irq) const {
        return EXTRACT_BITS(registers->IPR[static_cast<uint8_t>(irq)], 4, MASK<4>);
    }

}
