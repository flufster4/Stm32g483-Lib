/*
 * dac.c
 *
 *  Created on: May 29, 2025
 *      Author: markian
 */

#include "../../../Inc/dac.h"

void set_dac(DAC_Register_TypeDef* DACx, DAC_CHANNEL channel, bool state) {

    //clear enable bit
    DACx->CR &= ~(1 << 16 | 1);
    if (!state) return;

    //set enable bit
    switch (channel) {
        case DMA_CHANNEL_1:
            DACx->CR |= 1;
            break;
        case DMA_CHANNEL_2:
            DACx->CR |= 1 << 16;
            break;
        case DMA_BOTH_CHANNELS:
            DACx->CR |= 1 << 16 | 1;
            break;
    }
}

void set_dac_software_trigger(DAC_Register_TypeDef* DACx, DAC_CHANNEL channel, bool state, bool b_state) {
    //bit setting magic
    switch (channel) {
        case DMA_CHANNEL_1:
            DACx->SWTRGR = state | b_state << 16;
            break;
        case DMA_CHANNEL_2:
            DACx->SWTRGR = (state | b_state << 16) << 1;
            break;
        case DMA_BOTH_CHANNELS:
            DACx->SWTRGR = (state | b_state << 16) << 1 | (state | b_state << 16);
    }
}

void set_dac_value(DAC_Register_TypeDef* DACx, DAC_CHANNEL channel, DAC_ALIGNMENT alignment, int32_t value) {
    switch (channel) {
        case DMA_CHANNEL_1:
            if (alignment == DAC_ALIGNMENT_RIGHT_12_BIT)
                DACx->DHR12R1 = value;
            else if (alignment == DAC_ALIGNMENT_LEFT_12_BIT)
                DACx->DHR12L1 = value;
            else
                DACx->DHR8R1 = value;
            break;
        case DMA_CHANNEL_2:
            if (alignment == DAC_ALIGNMENT_RIGHT_12_BIT)
                DACx->DHR12R2 = value;
            else if (alignment == DAC_ALIGNMENT_LEFT_12_BIT)
                DACx->DHR12L2 = value;
            else
                DACx->DHR8R2 = value;
            break;
        case DMA_BOTH_CHANNELS:
            if (alignment == DAC_ALIGNMENT_RIGHT_12_BIT)
                DACx->DHR12RD = value;
            else if (alignment == DAC_ALIGNMENT_LEFT_12_BIT)
                DACx->DHR12LD = value;
            else
                DACx->DHR8RD = value;
            break;
    }
}

unsigned int get_dac_value(DAC_Register_TypeDef* DACx, DAC_CHANNEL channel) {
    switch (channel) {
        case DMA_CHANNEL_1:
            return DACx->DOR1;
        case DMA_CHANNEL_2:
            return DACx->DOR2;
        case DMA_BOTH_CHANNELS:
        default:
            return 0;
    }
}

void set_dac_cal_offset(DAC_Register_TypeDef* DACx, int32_t offset_chnl_1, int32_t offset_chnl_2) {
    const int mask = 0b1111;
    DACx->CCR &= ~(mask | mask << 16);
    DACx->CCR |= offset_chnl_1 & mask;
    DACx->CCR |= (offset_chnl_2 & mask) << 16;
}
