/*
 * dac.h
 *
 *  Created on: May 29, 2025
 *      Author: markian
 */

#ifndef DAC_H
#define DAC_H

    #include "util.h"

    typedef struct {
        reg32_t CR;
        reg32_t SWTRGR;
        reg32_t DHR12R1;
        reg32_t DHR12L1;
        reg32_t DHR8R1;
        reg32_t DHR12R2;
        reg32_t DHR12L2;
        reg32_t DHR8R2;
        reg32_t DHR12RD;
        reg32_t DHR12LD;
        reg32_t DHR8RD;
        reg32_t DOR1;
        reg32_t DOR2;
        reg32_t SR;
        reg32_t CCR;
        reg32_t MCR;
        reg32_t SHSR1;
        reg32_t SHSR2;
        reg32_t SHHR;
        reg32_t SHRR;
        reg32_t r0[2];
        reg32_t STR1;
        reg32_t STR2;
        reg32_t STMODR;
        reg32_t r1[2];
    } DAC_Register_TypeDef;

    typedef enum {
        DISABLED,
        NOISE,
        TRIANGLE,
        SAWTOOTH
    } DAC_WAVE_GENERATION;

    typedef enum {
        DMA_CHANNEL_1,
        DMA_CHANNEL_2,
        DMA_BOTH_CHANNELS
    } DAC_CHANNEL;

    typedef enum {
        DAC_ALIGNMENT_RIGHT_12_BIT,
        DAC_ALIGNMENT_LEFT_12_BIT,
        DAC_ALIGNMENT_RIGHT_8_BIT
    } DAC_ALIGNMENT;

    typedef enum {
        DMA_STATUS_BUSY,
        DMA_STATUS_CAL_OFFSET,
        DMA_STATUS_DMA_UNDERRUN,
        DMA_STATUS_READY
    } DAC_STATUS;

    void set_dac(DAC_Register_TypeDef* DACx, DAC_CHANNEL channel, bool state);

    void set_dac_software_trigger(DAC_Register_TypeDef* DACx, DAC_CHANNEL channel, bool state, bool b_state);

    void set_dac_value(DAC_Register_TypeDef* DACx, DAC_CHANNEL channel, DAC_ALIGNMENT alignment, int32_t value);

    unsigned int get_dac_value(DAC_Register_TypeDef* DACx, DAC_CHANNEL channel);

    void set_dac_cal_offset(DAC_Register_TypeDef* DACx, int32_t offset_chnl_1, int32_t offset_chnl_2);

    void set_dac_mode(DAC_Register_TypeDef* DACx, DAC_CHANNEL channel, bool DMA_double_data, int32_t mode, int32_t freq);

    void configure_dac_sawtooth(DAC_Register_TypeDef* DACx, DAC_CHANNEL channel, int32_t increment_value, bool decrement, int32_t reset_value, int32_t trigger, int32_t reset_trigger);
#endif //DAC_H
