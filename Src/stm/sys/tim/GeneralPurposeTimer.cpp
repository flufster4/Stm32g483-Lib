//
// Created by Markian on 8/1/2025.
//

#include "../../../../Inc/stm/sys/GeneralPurposeTim.h"

#define EXTRACT_BITS(var, pos, mask) ((var & (mask << pos)) >> pos)

namespace stm32::system::tim {

    void GeneralPurposeTimer::configure(const GeneralPurposeTimerConfiguration& configuration) const {
        timerRegisters->CR1 &= ~((0x7F << 2) | (0x3 << 11));
        timerRegisters->CR1 |= (configuration.onlyCounterUpdates << 2) |
            (configuration.onePulseMode << 3) |
            (configuration.downcountingMode << 4) |
            (static_cast<uint8_t>(configuration.centerAlignedMode) << 5) |
            (configuration.bufferedARR << 7) |
            (static_cast<uint8_t>(configuration.filterPrescaler) << 8) |
            (configuration.enableRemapping << 11) |
            (configuration.enableDithering << 12);

        timerRegisters->DIER &= ~(0x1F | (1 << 6) | (0x1F << 8) | (1 << 14) | (0xF << 20));
        timerRegisters->DIER |= configuration.enableUpdateInterrupt |
            (configuration.enableCC1interrupt << 1) |
            (configuration.enableCC2interrupt << 2) |
            (configuration.enableCC3interrupt << 3) |
            (configuration.enableCC4interrupt << 4) |
            (configuration.enableTriggerInterrupt << 6) |
            (configuration.enableUpdateDMArequest << 8) |
            (configuration.enableCC1dmaRequest << 9) |
            (configuration.enableCC2dmaRequest << 10) |
            (configuration.enableCC3dmaRequest << 11) |
            (configuration.enableCC4dmaRequest << 12) |
            (configuration.enableTriggerDMArequest << 14) |
            (configuration.enableIndexInterrupt << 20) |
            (configuration.enableDirectionChangeInterrupt << 21) |
            (configuration.enableIndexErrorInterrupt << 22) |
            (configuration.enableTransitionErrorInterrupt << 23);
    }

    GeneralPurposeTimerConfiguration GeneralPurposeTimer::getConfiguration() const {
        return GeneralPurposeTimerConfiguration{
            static_cast<bool>(timerRegisters->CR1 & (1 << 2)),
            static_cast<bool>(timerRegisters->CR1 & (1 << 3)),
            static_cast<bool>(timerRegisters->CR1 & (1 << 4)),
            static_cast<GeneralPurposeTimerCenterAlignedMode>(timerRegisters->CR1 & (0x3 << 5)),
            static_cast<bool>(timerRegisters->CR1 & (1 << 7)),
            static_cast<GeneralPurposeTimerFilterPrescaler>(timerRegisters->CR1 & (0x3 << 8)),
            static_cast<bool>(timerRegisters->CR1 & (1 << 11)),
            static_cast<bool>(timerRegisters->CR1 & (1 << 12))
        };
    }

    void GeneralPurposeTimer::configureInputCaptureChannel(const GeneralPurposeTimerInputCaptureConfiguration &configuration, const GeneralPurposeTimerCaptureCompareChannel channel) const {
        volatile uint32_t* ccmr = &timerRegisters->CCMR1;
        uint8_t offset = 0;

        if (channel == GeneralPurposeTimerCaptureCompareChannel::CC3 || channel == GeneralPurposeTimerCaptureCompareChannel::CC4)
            ccmr = &timerRegisters->CCMR2;
        if (channel == GeneralPurposeTimerCaptureCompareChannel::CC2 || channel == GeneralPurposeTimerCaptureCompareChannel::CC4)
            offset = 8;

        *ccmr &= ~(0xFF << offset);
        *ccmr |= (static_cast<uint8_t>(configuration.ccSelection) << offset) |
            (static_cast<uint8_t>(configuration.prescaler) << (offset + 2)) |
            (static_cast<uint8_t>(configuration.filter) << (offset + 4));
    }

    void GeneralPurposeTimer::configureOutputCompareChannel(const GeneralPurposeTimerOutputCompareConfiguration &configuration, const GeneralPurposeTimerCaptureCompareChannel channel) const {
        volatile uint32_t* ccmr = &timerRegisters->CCMR1;
        uint8_t offset = 0;

        if (channel == GeneralPurposeTimerCaptureCompareChannel::CC3 || channel == GeneralPurposeTimerCaptureCompareChannel::CC4)
            ccmr = &timerRegisters->CCMR2;
        if (channel == GeneralPurposeTimerCaptureCompareChannel::CC2 || channel == GeneralPurposeTimerCaptureCompareChannel::CC4)
            offset = 8;

        *ccmr &= ~(0xFF << offset | (1 << (offset + 16)));
        *ccmr |= (static_cast<uint8_t>(configuration.ccSelection) << offset) |
            (configuration.fastEnable << (offset + 2)) |
            (configuration.preloadCCR << (offset + 3)) |
            (EXTRACT_BITS(static_cast<uint8_t>(configuration.mode), 0, 0x7) << (offset + 4)) |
            (configuration.clearEnable << (offset + 7)) |
            (EXTRACT_BITS(static_cast<uint8_t>(configuration.mode), 3, 1) << (offset + 16));
    }

    GeneralPurposeTimerInputCaptureConfiguration GeneralPurposeTimer::getInputCaptureChannelConfiguration(const GeneralPurposeTimerCaptureCompareChannel channel) const {
        const volatile uint32_t* ccmr = &timerRegisters->CCMR1;
        uint8_t offset = 0;

        if (channel == GeneralPurposeTimerCaptureCompareChannel::CC3 || channel == GeneralPurposeTimerCaptureCompareChannel::CC4)
            ccmr = &timerRegisters->CCMR2;
        if (channel == GeneralPurposeTimerCaptureCompareChannel::CC2 || channel == GeneralPurposeTimerCaptureCompareChannel::CC4)
            offset = 8;

        return GeneralPurposeTimerInputCaptureConfiguration{
            static_cast<GeneralPurposeTimerCaptureCompareSelection>(EXTRACT_BITS(*ccmr, offset, 0x3)),
            static_cast<GeneralPurposeTimerInputCapturePrescaler>(EXTRACT_BITS(*ccmr, offset + 2, 0x3)),
            static_cast<GeneralPurposeTimerInputCaptureFilter>(EXTRACT_BITS(*ccmr, offset + 4, 0xF)),
        };
    }

    GeneralPurposeTimerOutputCompareConfiguration GeneralPurposeTimer::getOutputCompareChannelConfiguration(GeneralPurposeTimerCaptureCompareChannel channel) const {
        const volatile uint32_t* ccmr = &timerRegisters->CCMR1;
        uint8_t offset = 0;

        if (channel == GeneralPurposeTimerCaptureCompareChannel::CC3 || channel == GeneralPurposeTimerCaptureCompareChannel::CC4)
            ccmr = &timerRegisters->CCMR2;
        if (channel == GeneralPurposeTimerCaptureCompareChannel::CC2 || channel == GeneralPurposeTimerCaptureCompareChannel::CC4)
            offset = 8;

        return GeneralPurposeTimerOutputCompareConfiguration{
            static_cast<GeneralPurposeTimerCaptureCompareSelection>(EXTRACT_BITS(*ccmr, offset, 0x3)),
            static_cast<bool>(EXTRACT_BITS(*ccmr, offset + 2, 1)),
            static_cast<bool>(EXTRACT_BITS(*ccmr, offset + 3, 1)),
            static_cast<GeneralPurposeTimerOutputCompareMode>(EXTRACT_BITS(*ccmr, offset + 4, 0x7) | (EXTRACT_BITS(*ccmr, offset + 16, 1) << 3)),
            static_cast<bool>(EXTRACT_BITS(*ccmr, offset + 7, 1))
        };
    }

    void GeneralPurposeTimer::enableCaptureCompareChannel(const GeneralPurposeTimerCaptureCompareChannel channel, const bool inputCapture, const bool activeLow) const {
        timerRegisters->CCER &= ~((1 << 1 | 1 << 3) << (static_cast<uint8_t>(channel) * 4));
        timerRegisters->CCER |= ((activeLow << 1) | (inputCapture << 3)) << (static_cast<uint8_t>(channel) * 4);
        timerRegisters->CCER |= 1 << (static_cast<uint8_t>(channel) *  4);
    }

    void GeneralPurposeTimer::disableCaptureCompareChannel(GeneralPurposeTimerCaptureCompareChannel channel) const {
        timerRegisters->CCER &= ~(1 << (static_cast<uint8_t>(channel) * 4));
    }

    void GeneralPurposeTimer::setOutputCompareValue(const GeneralPurposeTimerCaptureCompareChannel channel, const uint32_t value) const {
        volatile uint32_t* ccr = &timerRegisters->CCR1 + static_cast<uint8_t>(channel);
        *ccr &= isThirtyTwoBit ? ~0xFFFFFFFF : ~0xFFFFF;
        *ccr |= isThirtyTwoBit ? value : (value & 0xFFFFF);
    }

    uint32_t GeneralPurposeTimer::getInputCaptureValue(GeneralPurposeTimerCaptureCompareChannel channel) const {
        const volatile uint32_t* ccr = &timerRegisters->CCER + static_cast<uint8_t>(channel);
        return isThirtyTwoBit ? *ccr : (*ccr & 0xFFFFF);
    }

    void GeneralPurposeTimer::setClockPrescaler(const uint16_t prescaler) const {
        timerRegisters->PSC &= ~0xFFFF;
        timerRegisters->PSC |= prescaler;
    }

    void GeneralPurposeTimer::setAutoReloadValue(const uint32_t value) const {
        timerRegisters->ARR &= isThirtyTwoBit ? ~0xFFFFFFFF : ~0xFFFFF;
        timerRegisters->ARR |= isThirtyTwoBit ? value : (value & 0xFFFFF);
    }

    void GeneralPurposeTimer::enableUpdates() const {
        timerRegisters->CR1 &= ~(1 << 1);
    }

    void GeneralPurposeTimer::disableUpdates() const {
        timerRegisters->CR1 |= (1 << 1);
    }

    void GeneralPurposeTimer::update() const {
        timerRegisters->EGR |= 1;
    }

    void GeneralPurposeTimer::startCounter() const {
        timerRegisters->CR1 |= 1;
    }

    void GeneralPurposeTimer::stopCounter() const {
        timerRegisters->CR1 &= ~1;
    }

    uint32_t GeneralPurposeTimer::getCount() const {
        return isThirtyTwoBit ? (timerRegisters->CNT & ~(1 << 31)) : (timerRegisters->CNT & 0xFFFF);
    }

    GeneralPurposeTimerStatus GeneralPurposeTimer::getStatus() const {
        return GeneralPurposeTimerStatus{
            static_cast<bool>(EXTRACT_BITS(timerRegisters->SR, 0, 1)),
            static_cast<bool>(EXTRACT_BITS(timerRegisters->SR, 1, 1)),
            static_cast<bool>(EXTRACT_BITS(timerRegisters->SR, 2, 1)),
            static_cast<bool>(EXTRACT_BITS(timerRegisters->SR, 3, 1)),
            static_cast<bool>(EXTRACT_BITS(timerRegisters->SR, 4, 1)),
            static_cast<bool>(EXTRACT_BITS(timerRegisters->SR, 6, 1)),
            static_cast<bool>(EXTRACT_BITS(timerRegisters->SR, 9, 1)),
            static_cast<bool>(EXTRACT_BITS(timerRegisters->SR, 10, 1)),
            static_cast<bool>(EXTRACT_BITS(timerRegisters->SR, 11, 1)),
            static_cast<bool>(EXTRACT_BITS(timerRegisters->SR, 12, 1)),
            static_cast<bool>(EXTRACT_BITS(timerRegisters->SR, 20, 1)),
            static_cast<bool>(EXTRACT_BITS(timerRegisters->SR, 21, 1)),
            static_cast<bool>(EXTRACT_BITS(timerRegisters->SR, 22, 1)),
            static_cast<bool>(EXTRACT_BITS(timerRegisters->SR, 23, 1)),
        };
    }

}