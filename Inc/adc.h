/*
 * adc.h
 *
 *  Created on: May 30, 2025
 *      Author: markian
 */

#ifndef ADC_H
#define ADC_H

    #include "util.h"

    typedef struct {
        reg32_t ISR;
        reg32_t IER;
        reg32_t CR;
        reg32_t CFGR;
        reg32_t CFGR2;
        reg32_t SMPR1;
        reg32_t SMPR2;
        reg32_t r0;
        reg32_t TR1;
        reg32_t TR2;
        reg32_t TR3;
        reg32_t r1;
        reg32_t SQR1;
        reg32_t SQR2;
        reg32_t SQR3;
        reg32_t SQR4;
        reg32_t DR;
        reg32_t r2[2];
        reg32_t JSQR;
        reg32_t r3[4];
        reg32_t OFR1;
        reg32_t OFR2;
        reg32_t OFR3;
        reg32_t OFR4;
        reg32_t r4[4];
        reg32_t JDR1;
        reg32_t JDR2;
        reg32_t JDR3;
        reg32_t JDR4;
        reg32_t r5[5];
        reg32_t AWD2CR;
        reg32_t AWD3CR;
        reg32_t r6;
        reg32_t DIFSEL;
        reg32_t CALDFACT;
        reg32_t r7[2];
        reg32_t GCOMP;
    } ADC_Register_TypeDef;

    typedef struct {
        reg32_t CSR;
        reg32_t r0;
        reg32_t CCR;
        reg32_t CDR;
    } ADC_Common_Register_TypeDef;

    typedef enum {
        CYCLES2_5,
        CYCLES6_5,
        CYCLES12_5,
        CYCLES24_5,
        CYCLES47_5,
        CYCLES92_5,
        CYCLES247_5,
        CYCLES640_5
    } ADC_Sampling_Time;

    typedef enum {
        ADC_DMA_ONESHOT,
        ADC_DMA_CIRCULAR
    } ADC_DMA_Configuration;

    typedef enum {
        ADC_RESOLUTION_12BIT,
        ADC_RESOLUTION_10BIT,
        ADC_RESOLUTION_8BIT,
        ADC_RESOLUTION_6BIT,
    } ADC_Data_Resolution;

    typedef enum {
        ADC_HW_TRIGGER_DISABLED,
        ADC_HW_TRIGGER_RISING_EDGE,
        ADC_HW_TRIGGER_FALLING_EDGE,
        ADC_HW_TRIGGER_BOTH_EDGE,
    } ADC_HW_Trigger;

    typedef struct {
        _Bool dma;
        ADC_DMA_Configuration dma_config;
        ADC_Data_Resolution resolution;
        char external_trigger;
        ADC_HW_Trigger external_trigger_type;
        _Bool preserve_overrun;
        _Bool continuous;
        _Bool delayed_conversion;
        _Bool left_aligned;
        _Bool discontinuous;
        char discontinuous_channels;
        _Bool discontinuous_injected_channels;
        _Bool all_channel_watchdog;
        _Bool enable_watchdog;
        _Bool enable_watchdog_injected_channels;
        _Bool automatic_injected_group_conversion;
        char analog_watchdog_channel;
        _Bool enable_injected_queue;
    } ADC_Configuration;

    void set_adc(ADC_Register_TypeDef* adc_register, bool state);

    void set_adc_voltage_regulator(ADC_Register_TypeDef* adc_register, bool state);

    void calibrate_adc(ADC_Register_TypeDef* adc_register, bool differential, uint16_t* o_factors);

    void set_adc_sampling_time(ADC_Register_TypeDef* adc_register, ADC_Sampling_Time time, int8_t channel, bool plus_one_cycle);

    unsigned int read_adc(ADC_Register_TypeDef* adc_register);

    ADC_Configuration default_adc_configuration(void);

    void configure_adc(ADC_Register_TypeDef* adc_register, const ADC_Configuration* config);
#endif //ADC_H
