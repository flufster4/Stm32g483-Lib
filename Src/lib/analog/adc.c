/*
 * adc.c
 *
 *  Created on: May 30, 2025
 *      Author: markian
 */

#include "../../../Inc/adc.h"

void set_adc(ADC_Register_TypeDef* adc_register, bool on) {

    if (on) {
        adc_register->CR |= 1;
        while (!(adc_register->ISR & 1)) {}
        return;
    }

    if (adc_register->CR & 1) {
        adc_register->CR |= 1 << 1;
        while (adc_register->CR & 1 << 1) {}
    }
}

void set_adc_voltage_regulator(ADC_Register_TypeDef* adc_register, bool on) {
    adc_register->CR &= ~(1 << 28);
    adc_register->CR |= on << 28;
    if (on)
        for (volatile int i = 0; i < 1000; i++) {} //Wait for regulator to stabalize
}

void calibrate_adc(ADC_Register_TypeDef* adc_register, bool differential, uint16_t* o_factors) {
    const int factor_mask = 0b1111111;

    if (o_factors[0] != 0) {
        adc_register->CALDFACT &= ~(factor_mask | factor_mask << 16);
        adc_register->CALDFACT |= factor_mask & o_factors[0];
        adc_register->CALDFACT |= (factor_mask & o_factors[1]) << 16;
        return;
    }

    if (differential)
        adc_register->CR |= 1 << 30;
    adc_register->CR |= 1 << 31;
    while (adc_register->CR & 1 << 31) {}

    o_factors[0] = adc_register->CALDFACT & factor_mask;
    o_factors[1] = adc_register->CALDFACT >> 16 & factor_mask;
}

void set_adc_sampling_time(ADC_Register_TypeDef* adc_register, ADC_Sampling_Time time, int8_t channel, bool plus_one_cycle) {
    const int time_mask = 0b111;

    adc_register->SMPR1 &= ~(1 << 31);
    if (plus_one_cycle)
        adc_register->SMPR1 |= 1 << 31;

    if (channel >= 10) {
        adc_register->SMPR2 &= ~(time_mask << channel * 3);
        adc_register->SMPR2 |= (time & time_mask) << channel * 3;
    }

    adc_register->SMPR1 &= ~(time_mask << channel * 3);
    adc_register->SMPR1 |= (time & time_mask) << channel * 3;
}

ADC_Configuration default_adc_configuration(void) {
    ADC_Configuration config;
    config.enable_injected_queue = 1;
    config.analog_watchdog_channel = 0;
    config.automatic_injected_group_conversion = 0;
    config.enable_watchdog_injected_channels = 0;
    config.enable_watchdog = 0;
    config.all_channel_watchdog = 1;
    config.discontinuous_injected_channels = 0;
    config.discontinuous_channels = 0;
    config.discontinuous = 0;
    config.left_aligned = 0;
    config.delayed_conversion = 0;
    config.continuous = 0;
    config.preserve_overrun = 1;
    config.external_trigger_type = ADC_HW_TRIGGER_DISABLED;
    config.external_trigger = 0;
    config.resolution = ADC_RESOLUTION_12BIT;
    config.dma_config = ADC_DMA_ONESHOT;
    config.dma = 0;
    return config;
}

void configure_adc(ADC_Register_TypeDef* adc_register, const ADC_Configuration* config) {
    adc_register->CFGR &= 1 << 2; //Clear all bits except 2 (reserved)
    adc_register->CFGR |= config->enable_injected_queue << 31 |
        (config->analog_watchdog_channel & 0b11111) << 26 |
        config->automatic_injected_group_conversion << 25 |
        config->enable_watchdog_injected_channels << 24 |
        config->enable_watchdog << 23 |
        !config->all_channel_watchdog << 22 |
        config->discontinuous_injected_channels << 20 |
        (config->discontinuous_channels & 0b111) << 17 |
        config->discontinuous << 16 |
        config->left_aligned << 15 |
        config->delayed_conversion << 14 |
        config->continuous << 13 |
        !config->preserve_overrun << 12 |
        (config->external_trigger_type & 0b11) << 10 |
        (config->external_trigger & 0b11111) << 5 |
        config->resolution << 3 |
        config->dma_config << 1 |
        config->dma; //Configure CFGR register
}