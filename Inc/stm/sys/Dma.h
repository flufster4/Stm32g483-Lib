//
// Created by Markian on 7/28/2025.
//

#pragma once
#include <cstdint>

namespace stm32::system::dma {

     struct DmaRegisters {
        volatile uint32_t ISR, IFCR, CCR1, CNDTR1, CPAR1, CMAR1, r0, CCR2, CNDTR2, CPAR2, CMAR2, r1, CCR3, CNDTR3, CPAR3,
         CMAR3, r2, CCR4, CNDTR4, CPAR4, CMAR4, r3, CCR5, CNDTR5, CPAR5, CMAR5, r4, CCR6, CNDTR6, CPAR6, CMAR6, r5, CCR7,
         CNDTR7, CPAR7, CMAR7, r6, CCR8, CNDTR8, CPAR8, CMAR8;
    };

     struct DmaMuxRegisters {
         volatile uint32_t C0CR, C1CR, C2CR, C3CR, C4CR, C5CR, C6CR, C7CR, C8CR, C9CR, C10CR, C11CR, C12CR, C13CR, C14CR,
         C15CR, r0[16], CSR, CCFR, r1[30], RG0CR, RG1CR, RG2CR, RG3CR, r2[12], RGSR, RGCFR, r3[173];
    };

    enum class DmaMuxDmaInput : uint8_t {
        NONE,
        G0,
        G1,
        G2,
        G3,
        ADC1,
        DAC1_CH1,
        DAC1_CH2,
        TIM6_UP,
        TIM7_UP,
        SPI1_RX,
        SPI1_TX,
        SPI2_RX,
        SPI2_TX,
        SPI3_RX,
        SPI3_TX,
        I2C1_RX,
        I2C1_TX,
        I2C2_RX,
        I2C2_TX,
        I2C3_RX,
        I2C3_TX,
        I2C4_RX,
        I2C4_TX,
        USART1_RX,
        USART1_TX,
        USART2_RX,
        USART2_TX,
        USART3_RX,
        USART3_TX,
        USART4_RX,
        USART4_TX,
        USART5_RX,
        USART5_TX,
        LPUART1_RX,
        LPUART1_TX,
        ADC2,
        ADC3,
        ADC4,
        ADC5,
        QUADSPI,
        DAC2_CH1,
        TIM1_CH1,
        TIM1_CH2,
        TIM1_CH3,
        TIM1_CH4,
        TIM1_UP,
        TIM1_TRIG,
        TIM1_COM,
        TIM8_CH1,
        TIM8_CH2,
        TIM8_CH3,
        TIM8_CH4,
        TIM8_UP,
        TIM8_TRIG,
        TIM8_COM,
        TIM2_CH1,
        TIM2_CH2,
        TIM2_CH3,
        TIM2_CH4,
        TIM2_UP,
        TIM3_CH1,
        TIM3_CH2,
        TIM3_CH3,
        TIM3_CH4,
        TIM3_UP,
        TIM3_TRIG,
        TIM4_CH1,
        TIM4_CH2,
        TIM4_CH3,
        TIM4_CH4,
        TIM4_UP,
        TIM5_CH1,
        TIM5_CH2,
        TIM5_CH3,
        TIM5_CH4,
        TIM5_UP,
        TIM5_TRIG,
        TIM15_CH1,
        TIM15_UP,
        TIM15_TRIG,
        TIM15_COM,
        TIM16_CH1,
        TIM16_UP,
        TIM17_CH1,
        TIM17_UP,
        TIM20_CH1,
        TIM20_CH2,
        TIM20_CH3,
        TIM20_CH4,
        TIM20_UP,
        AES_IN,
        AES_OUT,
        TIM20_TRIG,
        TIM20_COM,
        HRTIM_MASTER,
        HRTIM_TIMA,
        HRTIM_TIMB,
        HRTIM_TIMC,
        HRTIM_TIMD,
        HRTIM_TIME,
        HRTIM_TIMF,
        DAC3_CH1,
        DAC3_CH2,
        DAC4_CH1,
        DAC4_CH2,
        SPI4_RX,
        SPI4_TX,
        SAI1_A,
        SAI1_B,
        FMAC_READ,
        FMAC_WRITE,
        CORDIC_READ,
        CORDIC_WRITE,
        UCPD1_RX,
        UCPD1_TX
    };

    enum class DmaChannelPriority : uint8_t {
        LOW = 1,
        MEDIUM = 2,
        HIGH = 3,
        VERY_HIGH = 4
    };

    enum class DmaDataSize : uint8_t {
        EIGHT_BIT = 0,
        SIXTEEN_BIT = 1,
        THIRTY_TWO_BIT = 2
    };

    enum class DmaMuxSynchronizationPolarity : uint8_t {
        NO_EVENT = 0,
        RISING_EDGE = 1,
        FALLING_EDGE = 2,
        BOTH = 3
    };

    enum class DmaMuxSynchronizationInput : uint8_t {
        EXTI_LINE0 = 0,
        EXTI_LINE1 = 1,
        EXTI_LINE2 = 2,
        EXTI_LINE3 = 3,
        EXTI_LINE4 = 4,
        EXTI_LINE5 = 5,
        EXTI_LINE6 = 6,
        EXTI_LINE7 = 7,
        EXTI_LINE8 = 8,
        EXTI_LINE9 = 9,
        EXTI_LINE10 = 10,
        EXTI_LINE11 = 11,
        EXTI_LINE12 = 12,
        EXTI_LINE13 = 13,
        EXTI_LINE14 = 14,
        EXTI_LINE15 = 15,
        DMAMUX1_CH0_EVENT = 16,
        DMAMUX1_CH1_EVENT = 17,
        DMAMUX1_CH2_EVENT = 18,
        DMAMUX1_CH3_EVENT = 19,
        LPTIM1_OUT = 20
    };

    struct DmaChannelStatus {
        bool global, transferComplete, halfTransfer, transferError;
    };

    struct DmaMuxChannelConfiguration {
        DmaMuxDmaInput dmaRequest = DmaMuxDmaInput::NONE;
        bool synchronizationOverrunInterrupt = false, enableEventGeneration = false, enableSynchronization = false;
        DmaMuxSynchronizationPolarity synchronizationPolarity = DmaMuxSynchronizationPolarity::NO_EVENT;
        uint8_t numberOfRequestsToForward = 0;
        DmaMuxSynchronizationInput synchronizationInput = DmaMuxSynchronizationInput::EXTI_LINE0;
    };

    struct DmaMuxGeneratorChannelConfiguration {
        DmaMuxDmaInput signal = DmaMuxDmaInput::NONE;
        bool enableTriggerOverrunInterrupt = false;
        DmaMuxSynchronizationPolarity triggerPolarity = DmaMuxSynchronizationPolarity::NO_EVENT;
        uint8_t numberOfRequests = 0;
    };

    struct DmaChannelConfiguration {
        bool transferCompleteInterrupt = false, halfTransferInterrupt = false, transferErrorInterrupt = false,
            fromMemory = false, circularMode = false, peripheralIncrement = false, memoryIncrement = false;
        DmaDataSize peripheralSize = DmaDataSize::SIXTEEN_BIT, memorySize = DmaDataSize::SIXTEEN_BIT;
        DmaChannelPriority priority = DmaChannelPriority::LOW;
        bool memoryToMemoryMode = false;
        uint16_t numberOfData = 1;
        uint32_t peripheralAddress = 0, memoryAddress = 0;
    };

    class DmaMuxChannelConfigurationBuilder {
        DmaMuxChannelConfiguration configuration;

    public:
        DmaMuxChannelConfigurationBuilder() = default;
        explicit DmaMuxChannelConfigurationBuilder(const DmaMuxChannelConfiguration& configuration) : configuration(configuration) {}

        DmaMuxChannelConfigurationBuilder& setDmaRequest(DmaMuxDmaInput request);
        DmaMuxChannelConfigurationBuilder& enableSynchronizationOverrunInterrupt(bool enable = true);
        DmaMuxChannelConfigurationBuilder& enableEventGeneration(bool enable = true);
        DmaMuxChannelConfigurationBuilder& enableSynchronization(bool enable = true);
        DmaMuxChannelConfigurationBuilder& setSynchronizationPolarity(DmaMuxSynchronizationPolarity polarity);
        DmaMuxChannelConfigurationBuilder& setNumberOfRequests(uint8_t number);
        DmaMuxChannelConfigurationBuilder& setSynchronizationInput(DmaMuxSynchronizationInput input);

        [[nodiscard]] DmaMuxChannelConfiguration build() const;
    };

    class DmaMuxGeneratorChannelConfigurationBuilder {
        DmaMuxGeneratorChannelConfiguration configuration;

    public:
        DmaMuxGeneratorChannelConfigurationBuilder() = default;
        explicit DmaMuxGeneratorChannelConfigurationBuilder(const DmaMuxGeneratorChannelConfiguration& configuration) : configuration(configuration) {}

        DmaMuxGeneratorChannelConfigurationBuilder& setSignal(DmaMuxDmaInput signal);
        DmaMuxGeneratorChannelConfigurationBuilder& enableTriggerOverrunInterrupt(bool enable = true);
        DmaMuxGeneratorChannelConfigurationBuilder& setTriggerPolarity(DmaMuxSynchronizationPolarity polarity);
        DmaMuxGeneratorChannelConfigurationBuilder& setNumberOfRequests(uint8_t number);

        [[nodiscard]] DmaMuxGeneratorChannelConfiguration build() const;
    };

    class DmaChannelConfigurationBuilder {
        DmaChannelConfiguration configuration;

    public:
        DmaChannelConfigurationBuilder() = default;
        explicit DmaChannelConfigurationBuilder(const DmaChannelConfiguration& configuration) : configuration(configuration) {}

        DmaChannelConfigurationBuilder& enableInterupts(bool transferComplete, bool halfTransfer, bool transferError);
        DmaChannelConfigurationBuilder& setDataDirection(bool fromMemory);
        DmaChannelConfigurationBuilder& enableCircularMode(bool enable = true);
        DmaChannelConfigurationBuilder& enableIncrementMode(bool peripheralIncrement, bool memoryIncrement);
        DmaChannelConfigurationBuilder& setDataSize(DmaDataSize peripheralSize, DmaDataSize memorySize);
        DmaChannelConfigurationBuilder& setPriority(DmaChannelPriority priority);
        DmaChannelConfigurationBuilder& enableMemoryToMemoryMode(bool enable = true);
        DmaChannelConfigurationBuilder& setNumberOfData(uint16_t amount);
        DmaChannelConfigurationBuilder& setDataAddress(uint32_t peripheralAddress, uint32_t memoryAddress);

        [[nodiscard]] DmaChannelConfiguration build() const;
    };

    class DmaMux {
        DmaMuxRegisters* dmaMuxRegisters;

    public:
        explicit DmaMux(const uint32_t baseAddress) : dmaMuxRegisters(reinterpret_cast<DmaMuxRegisters*>(baseAddress)) {}

        void configureChannel(const DmaMuxChannelConfiguration& configuration, uint8_t channel) const;
        void configureGeneratorChannel(const DmaMuxGeneratorChannelConfiguration& configuration, uint8_t channel) const;

        [[nodiscard]] bool isChannelSynchronizationOverrun(uint8_t channel) const;
        [[nodiscard]] bool isGeneratorChannelTriggerOverrun(uint8_t channel) const;
        void clearChannelSynchronizationOverrun(uint8_t channel) const;
        void clearGeneratorChannelTriggerOverrun(uint8_t channel) const;

        void enableGeneratorChannel(uint8_t channel) const;
        void disableGeneratorChannel(uint8_t channel) const;
    };

    class Dma {
        DmaRegisters* dmaRegisters;

    public:
        explicit Dma(const uint32_t baseAddress) : dmaRegisters(reinterpret_cast<DmaRegisters*>(baseAddress)) {}

        [[nodiscard]] DmaChannelStatus getStatus(uint8_t channel) const;
        void clearInterruptFlags(const DmaChannelStatus& flags, uint8_t channel) const;
        void configureChannel(const DmaChannelConfiguration& configuration, uint8_t channel) const;
        void enableChannel(uint8_t channel) const;
        void disableChannel(uint8_t channel) const;
    };

}
