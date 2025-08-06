//
// Created by Markian on 8/6/2025.
//

#pragma once

#include <cstdint>

namespace stm32::system::tim {

    struct BasicTimerRegisters {
        volatile uint32_t CR1, CR2, r0, DIER, SR, EGR, r1[3], CNT, PSC, ARR;
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