//
// Created by Markian on 7/29/2025.
//

#pragma once
#include <cstdint>

namespace stm32::system::tim {

    struct GeneralPurposeTimerRegisters {
        volatile uint32_t CR1, CR2, SMCR, DIER, SR, EGR, CCMR1, CCMR2, CCER, CNT, PSC, ARR, r0, CCR1, CCR2, CCR3, CCR4,
            r1[5], ECR, TISEL, AF1, AF2, r2[221], DCR, DMAR;
    };

    struct AdvancedControlTimerRegisters {
        volatile uint32_t CR1, CR2, SMCR, DIER, SR, EGR, CCMR1, CCMR2, CCER, CNT, PSC, ARR, RCR, CCR1, CCR2, CCR3, CCR4,
            BDTR, CCR5, CCR6, CCMR3, DTR2, ECR, TISEL, AF1, AF2, r2[221], DCR, DMAR;
    };

    struct Timer15Registers {
        volatile uint32_t CR1, CR2, SMCR, DIER, SR, EGR, CCMR1, CCER, CNT, PSC, ARR, RCR, CCR1, CCR2, r0[3], BDTR, r1[3],
            DTR2, r2, TISEL, AF1, AF2, r3[221], DCR, DMAR;
    };

    struct Timer16and17Registers {
        volatile uint32_t CR1, CR2, r0, DIER, SR, EGR, CCMR1, r1, CCER, CNT, PSC, ARR, RCR, CCR1, r2[3], BDTR, r3[3],
            DTR2, r4, TISEL, AF1, AF2, OR1, r5[221], DCR, DMAR;
    };

    struct BasicTimerRegisters {
        volatile uint32_t CR1, CR2, r0, DIER, SR, EGR, r1[3], CNT, PSC, ARR;
    };

    struct LowPowerTimerRegisters {
        volatile uint32_t ISR, ICR, IER, CFGR, CR, CMP, ARR, CNT, OR;
    };

    enum class BasicTimerMasterMode : uint8_t {
        RESET = 0,
        ENABLE = 1,
        UPDATE = 2
    };

    struct BasicTimerConfiguration {
        bool onlyCounterUpdates = false, onePulseMode = false, bufferARR = true, enableRemaping = false,
            enableDithering = false;
        BasicTimerMasterMode masterMode = BasicTimerMasterMode::RESET;
        bool enableUpdateInterrupt = false, enableUpdateDmaRequest = false;
    };

    class BasicTimerConfigurationBuilder {
        BasicTimerConfiguration configuration;

    public:
        BasicTimerConfigurationBuilder() = default;
        explicit BasicTimerConfigurationBuilder(const BasicTimerConfiguration& configuration) : configuration(configuration) {}

        BasicTimerConfigurationBuilder& enableOnlyCounterUpdates(bool enable = true);
        BasicTimerConfigurationBuilder& enableOnePulseMode(bool enable = true);
        BasicTimerConfigurationBuilder& enableARRbuffering(bool enable = true);
        BasicTimerConfigurationBuilder& enableRemapping(bool enable = true);
        BasicTimerConfigurationBuilder& enableDithering(bool enable = true);
        BasicTimerConfigurationBuilder& setMasterMode(BasicTimerMasterMode mode);
        BasicTimerConfigurationBuilder& enableUpdateInterrupt(bool enable = true);
        BasicTimerConfigurationBuilder& enableUpdateDmaRequest(bool enable = true);

        [[nodiscard]] BasicTimerConfiguration build() const;
    };

    class BasicTimer {
        BasicTimerRegisters* timerRegisters;

    public:
        explicit BasicTimer(const uint32_t baseAddress) : timerRegisters(reinterpret_cast<BasicTimerRegisters*>(baseAddress)) {}

        void configure(const BasicTimerConfiguration& configuration) const;
        [[nodiscard]] BasicTimerConfiguration getConfiguration() const;

        void setCounter(uint16_t count) const;
        void setClockPrescaler(uint16_t prescaler) const;
        void setAutoReloadValue(uint32_t value) const;

        [[nodiscard]] uint16_t getCount() const;

        void enableUpdates() const;
        void disableUpdates() const;
        void update() const;
        void startCounter() const;
        void stopCounter() const;

        [[nodiscard]] bool isUpdateInterruptFlagSet() const;
    };
}
