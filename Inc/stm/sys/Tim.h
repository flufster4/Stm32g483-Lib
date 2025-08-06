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

    enum class GeneralPurposeTimerFilterPrescaler : uint8_t {
        ONE = 0,
        TWO = 1,
        FOUR = 2
    };

    enum class GeneralPurposeTimerCenterAlignedMode : uint8_t {
        EDGE_ALIGNED = 0,
        CENTER_ALIGNED_ONE = 1,
        CENTER_ALIGNED_TWO = 2,
        CENTER_ALIGNED_THREE = 3
    };

    enum class GeneralPurposeTimerMasterMode : uint8_t {
        RESET = 0, //EGR UE bit used as trgo
        ENABLE = 1, //enabling counter used as trgo
        UPDATE = 2, //update used as trgo
        COMPARE_PULSE = 3, //capture and compare match used as trgo
        COMPARE_1 = 4, //tim_oc1refc is used as trgo
        COMPARE_2 = 5, //tim_oc2refc is used as trgo
        COMPARE_3 = 6, //tim_oc3refc is used as trgo
        COMPARE_4 = 7, //tim_oc4refc is used as trgo
        ENCODER_CLOCK = 8 //encode clock is used as trgo
    };

    enum class GeneralPurposeTimerCaptureCompareSelection : uint8_t {
        OUTPUT = 0,
        INPUT_1 = 1, //tim_ic1 is mapped on tim_ti1
        INPUT_2 = 2, //tim_ic1 is mapped on tim_ti2
        INPUT_3 = 3 //tim_ic1 is mapped on tim_trc
    };

    enum class GeneralPurposeTimerInputCapturePrescaler : uint8_t {
        NONE = 0,
        TWO = 1,
        FOUR = 2,
        EIGHT = 3
    };

    enum class GeneralPurposeTimerInputCaptureFilter : uint8_t {
        NONE = 0, // No filter, sampling at fDTS
        FTIM_KER_CK_N2 = 1, // fSAMPLING = ftim_ker_ck, N = 2
        FTIM_KER_CK_N4 = 2, // fSAMPLING = ftim_ker_ck, N = 4
        FTIM_KER_CK_N8 = 3, // fSAMPLING = ftim_ker_ck, N = 8
        FDTS_DIV2_N6  = 4, // fSAMPLING = fDTS/2, N = 6
        FDTS_DIV2_N8 = 5, // fSAMPLING = fDTS/2, N = 8
        FDTS_DIV4_N6 = 6, // fSAMPLING = fDTS/4, N = 6
        FDTS_DIV4_N8 = 7, // fSAMPLING = fDTS/4, N = 8
        FDTS_DIV8_N6 = 8, // fSAMPLING = fDTS/8, N = 6
        FDTS_DIV8_N8 = 9, // fSAMPLING = fDTS/8, N = 8
        FDTS_DIV16_N5 = 10, // fSAMPLING = fDTS/16, N = 5
        FDTS_DIV16_N6 = 11, // fSAMPLING = fDTS/16, N = 6
        FDTS_DIV16_N8 = 12, // fSAMPLING = fDTS/16, N = 8
        FDTS_DIV32_N5 = 13, // fSAMPLING = fDTS/32, N = 5
        FDTS_DIV32_N6 = 14, // fSAMPLING = fDTS/32, N = 6
        FDTS_DIV32_N8 = 15  // fSAMPLING = fDTS/32, N = 8
    };

    enum class GeneralPurposeTimerOutputCompareMode : uint8_t {
        FROZEN = 0, // No effect on outputs
        ACTIVE_ON_MATCH = 1, // Set active level on match
        INACTIVE_ON_MATCH = 2, // Set inactive level on match
        TOGGLE = 3, // Toggle output on match
        FORCE_INACTIVE = 4, // Force inactive level
        FORCE_ACTIVE = 5, // Force active level
        PWM_MODE_1 = 6, // PWM mode 1
        PWM_MODE_2 = 7, // PWM mode 2
        RETRIGGERABLE_OPM_MODE_1 = 8, // Retriggerable OPM mode 1
        RETRIGGERABLE_OPM_MODE_2 = 9, // Retriggerable OPM mode 2
        COMBINED_PWM_MODE_1 = 12, // Combined PWM mode 1 (OR with OC2)
        COMBINED_PWM_MODE_2 = 13, // Combined PWM mode 2 (AND with OC2)
        ASYMMETRIC_PWM_MODE_1 = 14, // Asymmetric PWM mode 1
        ASYMMETRIC_PWM_MODE_2 = 15 // Asymmetric PWM mode 2
    };

    enum class GeneralPurposeTimerCaptureCompareChannel : uint8_t {
        CC1 = 0,
        CC2 = 1,
        CC3 = 2,
        CC4 = 3
    };

    struct GeneralPurposeTimerConfiguration {
        bool onlyCounterUpdates = false, onePulseMode = false, downcountingMode = false;
        GeneralPurposeTimerCenterAlignedMode centerAlignedMode = GeneralPurposeTimerCenterAlignedMode::EDGE_ALIGNED;
        bool bufferedARR = false;
        GeneralPurposeTimerFilterPrescaler filterPrescaler = GeneralPurposeTimerFilterPrescaler::ONE;
        bool enableRemapping = false, enableDithering = false, disableCCdmaRequest = false;
        GeneralPurposeTimerMasterMode masterMode = GeneralPurposeTimerMasterMode::RESET;
        bool enableUpdateInterrupt = false, enableCC1interrupt = false, enableCC2interrupt = false, enableCC3interrupt = false,
            enableCC4interrupt = false, enableTriggerInterrupt = false, enableUpdateDMArequest = false, enableCC1dmaRequest = false,
            enableCC2dmaRequest = false, enableCC3dmaRequest = false, enableCC4dmaRequest = false, enableTriggerDMArequest = false,
            enableIndexInterrupt = false, enableDirectionChangeInterrupt = false, enableIndexErrorInterrupt = false, enableTransitionErrorInterrupt = false;
    };

    //TODO: Slave mode configuration

    struct GeneralPurposeTimerInputCaptureConfiguration {
        GeneralPurposeTimerCaptureCompareSelection ccSelection = GeneralPurposeTimerCaptureCompareSelection::OUTPUT;
        GeneralPurposeTimerInputCapturePrescaler prescaler = GeneralPurposeTimerInputCapturePrescaler::NONE;
        GeneralPurposeTimerInputCaptureFilter filter = GeneralPurposeTimerInputCaptureFilter::NONE;
    };

    struct GeneralPurposeTimerOutputCompareConfiguration {
        GeneralPurposeTimerCaptureCompareSelection ccSelection = GeneralPurposeTimerCaptureCompareSelection::OUTPUT;
        bool fastEnable = false, preloadCCR = false;
        GeneralPurposeTimerOutputCompareMode mode = GeneralPurposeTimerOutputCompareMode::FROZEN;
        bool clearEnable = false;
    };

    class GeneralPurposeTimerConfigurationBuilder {
        GeneralPurposeTimerConfiguration configuration;

    public:
        GeneralPurposeTimerConfigurationBuilder() = default;
        explicit GeneralPurposeTimerConfigurationBuilder(const GeneralPurposeTimerConfiguration& configuration) : configuration(configuration) {}

        GeneralPurposeTimerConfigurationBuilder& enableOnlyCounterUpdates(bool enable = true);
        GeneralPurposeTimerConfigurationBuilder& enableOnePulseMode(bool enable = true);
        GeneralPurposeTimerConfigurationBuilder& enableDowncountingMode(bool enable = true);
        GeneralPurposeTimerConfigurationBuilder& setCenterAlignedMode(GeneralPurposeTimerCenterAlignedMode mode);
        GeneralPurposeTimerConfigurationBuilder& enableARRbuffering(bool enable = true);
        GeneralPurposeTimerConfigurationBuilder& setFilterPrescaler(GeneralPurposeTimerFilterPrescaler prescaler);
        GeneralPurposeTimerConfigurationBuilder& enableRemapping(bool enable = true);
        GeneralPurposeTimerConfigurationBuilder& enableDithering(bool enable = true);
        GeneralPurposeTimerConfigurationBuilder& enableCCdmaRequestOnUpdate(bool enable = true);
        GeneralPurposeTimerConfigurationBuilder& enableCaptureCompareInterrupts(bool cc1, bool cc2, bool cc3, bool cc4);
        GeneralPurposeTimerConfigurationBuilder& enableCaptureCompareDmaRequests(bool cc1, bool cc2, bool cc3, bool cc4);
        GeneralPurposeTimerConfigurationBuilder& enableInterrupts(bool update, bool trigger, bool index, bool directionChange, bool indexError, bool transitionError);
        GeneralPurposeTimerConfigurationBuilder& enableDmaRequests(bool update, bool trigger);

        [[nodiscard]] GeneralPurposeTimerConfiguration build() const;
    };

    class GeneralPurposeTimer {
        GeneralPurposeTimerRegisters* timerRegisters;
        bool isThirtyTwoBit;

    public:
        explicit GeneralPurposeTimer(const uint32_t baseAddress, const bool isThirtyTwoBit = false) : timerRegisters(reinterpret_cast<GeneralPurposeTimerRegisters*>(baseAddress)), isThirtyTwoBit(isThirtyTwoBit) {}

        void configure(const GeneralPurposeTimerConfiguration& configuration) const;
        [[nodiscard]] GeneralPurposeTimerConfiguration getConfiguration() const;

        void configureInputCaptureChannel(const GeneralPurposeTimerInputCaptureConfiguration& configuration, GeneralPurposeTimerCaptureCompareChannel channel) const;
        void configureOutputCompareChannel(const GeneralPurposeTimerOutputCompareConfiguration& configuration, GeneralPurposeTimerCaptureCompareChannel channel) const;
        [[nodiscard]] GeneralPurposeTimerInputCaptureConfiguration getInputCaptureChannelConfiguration(GeneralPurposeTimerCaptureCompareChannel channel) const;
        [[nodiscard]] GeneralPurposeTimerOutputCompareConfiguration getOutputCompareChannelConfiguration(GeneralPurposeTimerCaptureCompareChannel channel) const;

        void setOutputCompareValue(GeneralPurposeTimerCaptureCompareChannel channel, uint32_t value) const;
        [[nodiscard]] uint32_t getInputCaptureValue(GeneralPurposeTimerCaptureCompareChannel channel) const;

        void enableCaptureCompareChannel(GeneralPurposeTimerCaptureCompareChannel channel, bool inputCapture, bool activeLow = false) const;
        void disableCaptureCompareChannel(GeneralPurposeTimerCaptureCompareChannel channel) const;

        void setClockPrescaler(uint16_t prescaler) const;
        void setAutoReloadValue(uint32_t value) const;

        [[nodiscard]] uint32_t getCount() const;

        void enableUpdates() const;
        void disableUpdates() const;
        void update() const;
        void startCounter() const;
        void stopCounter() const;
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
