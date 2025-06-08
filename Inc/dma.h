/*
 * dma.h
 *
 *  Created on: Jun 3, 2025
 *      Author: markian
 */

#ifndef DMA_H
#define DMA_H

    #include "util.h"

    typedef struct {
        reg32_t ISR;
        reg32_t IFCR;
        reg32_t CCR1;
        reg32_t CNDTR1;
        reg32_t CPAR1;
        reg32_t CMAR1;
        reg32_t r0;
        reg32_t CCR2;
        reg32_t CNDTR2;
        reg32_t CPAR2;
        reg32_t CMAR2;
        reg32_t r1;
        reg32_t CCR3;
        reg32_t CNDTR3;
        reg32_t CPAR3;
        reg32_t CMAR3;
        reg32_t r2;
        reg32_t CCR4;
        reg32_t CNDTR4;
        reg32_t CPAR4;
        reg32_t CMAR4;
        reg32_t r3;
        reg32_t CCR5;
        reg32_t CNDTR5;
        reg32_t CPAR5;
        reg32_t CMAR5;
        reg32_t r4;
        reg32_t CCR6;
        reg32_t CNDTR6;
        reg32_t CPAR6;
        reg32_t CMAR6;
        reg32_t r5;
        reg32_t CCR7;
        reg32_t CNDTR7;
        reg32_t CPAR7;
        reg32_t CMAR7;
        reg32_t r6;
        reg32_t CCR8;
        reg32_t CNDTR8;
        reg32_t CPAR8;
        reg32_t CMAR8;
    } DMA_Register_TypeDef;

    typedef struct {
        reg32_t C0CR;
        reg32_t C1CR;
        reg32_t C2CR;
        reg32_t C3CR;
        reg32_t C4CR;
        reg32_t C5CR;
        reg32_t C6CR;
        reg32_t C7CR;
        reg32_t C8CR;
        reg32_t C9CR;
        reg32_t C10CR;
        reg32_t C11CR;
        reg32_t C12CR;
        reg32_t C13CR;
        reg32_t C14CR;
        reg32_t C15CR;
        reg32_t r0[16];
        reg32_t CSR;
        reg32_t CCFR;
        reg32_t r1[30];
        reg32_t RG0CR;
        reg32_t RG1CR;
        reg32_t RG2CR;
        reg32_t RG3CR;
        reg32_t r2[12];
        reg32_t RGSR;
        reg32_t RGCFR;
        reg32_t r3[173];
    } DMA_MUX_Register_TypeDef;

    typedef enum {
        DMAMUX_EVENT_NONE,
        DMAMUX_EVENT_G0,
        DMAMUX_EVENT_G1,
        DMAMUX_EVENT_G2,
        DMAMUX_EVENT_G3,
        DMAMUX_EVENT_ADC1,
        DMAMUX_EVENT_DAC1_CH1,
        DMAMUX_EVENT_DAC1_CH2,
        DMAMUX_EVENT_TIM6_UP,
        DMAMUX_EVENT_TIM7_UP,
        DMAMUX_EVENT_SPI1_RX,
        DMAMUX_EVENT_SPI1_TX,
        DMAMUX_EVENT_SPI2_RX,
        DMAMUX_EVENT_SPI2_TX,
        DMAMUX_EVENT_SPI3_RX,
        DMAMUX_EVENT_SPI3_TX,
        DMAMUX_EVENT_I2C1_RX,
        DMAMUX_EVENT_I2C1_TX,
        DMAMUX_EVENT_I2C2_RX,
        DMAMUX_EVENT_I2C2_TX,
        DMAMUX_EVENT_I2C3_RX,
        DMAMUX_EVENT_I2C3_TX,
        DMAMUX_EVENT_I2C4_RX,
        DMAMUX_EVENT_I2C4_TX,
        DMAMUX_EVENT_USART1_RX,
        DMAMUX_EVENT_USART1_TX,
        DMAMUX_EVENT_USART2_RX,
        DMAMUX_EVENT_USART2_TX,
        DMAMUX_EVENT_USART3_RX,
        DMAMUX_EVENT_USART3_TX,
        DMAMUX_EVENT_USART4_RX,
        DMAMUX_EVENT_USART4_TX,
        DMAMUX_EVENT_USART5_RX,
        DMAMUX_EVENT_USART5_TX,
        DMAMUX_EVENT_LPUART1_RX,
        DMAMUX_EVENT_LPUART1_TX,
        DMAMUX_EVENT_ADC2,
        DMAMUX_EVENT_ADC3,
        DMAMUX_EVENT_ADC4,
        DMAMUX_EVENT_ADC5,
        DMAMUX_EVENT_QUADSPI,
        DMAMUX_EVENT_DAC2_CH1,
        DMAMUX_EVENT_TIM1_CH1,
        DMAMUX_EVENT_TIM1_CH2,
        DMAMUX_EVENT_TIM1_CH3,
        DMAMUX_EVENT_TIM1_CH4,
        DMAMUX_EVENT_TIM1_UP,
        DMAMUX_EVENT_TIM1_TRIG,
        DMAMUX_EVENT_TIM1_COM,
        DMAMUX_EVENT_TIM8_CH1,
        DMAMUX_EVENT_TIM8_CH2,
        DMAMUX_EVENT_TIM8_CH3,
        DMAMUX_EVENT_TIM8_CH4,
        DMAMUX_EVENT_TIM8_UP,
        DMAMUX_EVENT_TIM8_TRIG,
        DMAMUX_EVENT_TIM8_COM,
        DMAMUX_EVENT_TIM2_CH1,
        DMAMUX_EVENT_TIM2_CH2,
        DMAMUX_EVENT_TIM2_CH3,
        DMAMUX_EVENT_TIM2_CH4,
        DMAMUX_EVENT_TIM2_UP,
        DMAMUX_EVENT_TIM3_CH1,
        DMAMUX_EVENT_TIM3_CH2,
        DMAMUX_EVENT_TIM3_CH3,
        DMAMUX_EVENT_TIM3_CH4,
        DMAMUX_EVENT_TIM3_UP,
        DMAMUX_EVENT_TIM3_TRIG,
        DMAMUX_EVENT_TIM4_CH1,
        DMAMUX_EVENT_TIM4_CH2,
        DMAMUX_EVENT_TIM4_CH3,
        DMAMUX_EVENT_TIM4_CH4,
        DMAMUX_EVENT_TIM4_UP,
        DMAMUX_EVENT_TIM5_CH1,
        DMAMUX_EVENT_TIM5_CH2,
        DMAMUX_EVENT_TIM5_CH3,
        DMAMUX_EVENT_TIM5_CH4,
        DMAMUX_EVENT_TIM5_UP,
        DMAMUX_EVENT_TIM5_TRIG,
        DMAMUX_EVENT_TIM15_CH1,
        DMAMUX_EVENT_TIM15_UP,
        DMAMUX_EVENT_TIM15_TRIG,
        DMAMUX_EVENT_TIM15_COM,
        DMAMUX_EVENT_TIM16_CH1,
        DMAMUX_EVENT_TIM16_UP,
        DMAMUX_EVENT_TIM17_CH1,
        DMAMUX_EVENT_TIM17_UP,
        DMAMUX_EVENT_TIM20_CH1,
        DMAMUX_EVENT_TIM20_CH2,
        DMAMUX_EVENT_TIM20_CH3,
        DMAMUX_EVENT_TIM20_CH4,
        DMAMUX_EVENT_TIM20_UP,
        DMAMUX_EVENT_AES_IN,
        DMAMUX_EVENT_AES_OUT,
        DMAMUX_EVENT_TIM20_TRIG,
        DMAMUX_EVENT_TIM20_COM,
        DMAMUX_EVENT_HRTIM_MASTER,
        DMAMUX_EVENT_HRTIM_TIMA,
        DMAMUX_EVENT_HRTIM_TIMB,
        DMAMUX_EVENT_HRTIM_TIMC,
        DMAMUX_EVENT_HRTIM_TIMD,
        DMAMUX_EVENT_HRTIM_TIME,
        DMAMUX_EVENT_HRTIM_TIMF,
        DMAMUX_EVENT_DAC3_CH1,
        DMAMUX_EVENT_DAC3_CH2,
        DMAMUX_EVENT_DAC4_CH1,
        DMAMUX_EVENT_DAC4_CH2,
        DMAMUX_EVENT_SPI4_RX,
        DMAMUX_EVENT_SPI4_TX,
        DMAMUX_EVENT_SAI1_A,
        DMAMUX_EVENT_SAI1_B,
        DMAMUX_EVENT_FMAC_READ,
        DMAMUX_EVENT_FMAC_WRITE,
        DMAMUX_EVENT_CORDIC_READ,
        DMAMUX_EVENT_CORDIC_WRITE,
        DMAMUX_EVENT_UCPD1_RX,
        DMAMUX_EVENT_UCPD1_TX
    } DMAMUX_Input_Event;

    typedef enum {
        DMA_PRIORITY_LOW,
        DMA_PRIORITY_MEDIUM,
        DMA_PRIORITY_HIGH,
        DMA_PRIORITY_VERY_HIGH,
    } DMA_Channel_Priority;

    typedef enum {
        DMA_MEMORY_SIZE_8BIT,
        DMA_MEMORY_SIZE_16BIT,
        DMA_MEMORY_SIZE_32BIT,
    } DMA_Memory_Size;

    typedef enum {
        DMA_TRANSFER_DIRECTION_FROM_PERIPHERAL,
        DMA_TRANSFER_DIRECTION_FROM_MEMORY,
    } DMA_Transfer_Direction;

    typedef enum {
        DMAMUX_SYNC_POLARITY_NONE,
        DMAMUX_SYNC_POLARITY_RISING_EDGE,
        DMAMUX_SYNC_POLARITY_FALLING_EDGE,
        DMAMUX_SYNC_POLARITY_BOTH_EDGE
    } DMAMUX_Sync_Polarity;

    typedef struct {
        bool mem_to_mem;
        DMA_Channel_Priority priority;
        DMA_Memory_Size memory_size;
        DMA_Memory_Size peripheral_size;
        bool memory_increment;
        bool peripheral_increment;
        bool circular_mode;
        DMA_Transfer_Direction transfer_direction;
        bool transfer_error_interrupt;
        bool half_transfer_interrupt;
        bool complete_transfer_interrupt;
        uint16_t number_of_data;
        uint32_t* peripheral_address;
        uint32_t* memory_address;
    } DMA_Channel_Config_TypeDef;

    typedef struct {
        DMAMUX_Input_Event request_event;
        bool sync_overrun_interrupt;
        bool enable_event_generation;
        bool enable_sync;
        DMAMUX_Sync_Polarity sync_polarity;
        uint16_t number_of_requests;

    } DMAMUX_Channel_Config_TypeDef;

    DMA_Channel_Config_TypeDef default_dma_channel_config(uint32_t* peripheral_address, uint32_t* memory_address);

    DMAMUX_Channel_Config_TypeDef default_dmamux_channel_config(void);

    void set_dma_channel(DMA_Register_TypeDef* dma_register, bool on, uint32_t channel);

    void configure_dma_channel(DMA_Register_TypeDef* dma_register, DMA_Channel_Config_TypeDef* config, uint8_t channel);

    void configure_dmamux_channel(DMA_MUX_Register_TypeDef* dmamux_register, DMAMUX_Channel_Config_TypeDef* config, uint8_t channel);
#endif //DMA_H
