/*
 * dma.c
 *
 *  Created on: Jun 3, 2025
 *      Author: markian
 */

#include "../../Inc/dma.h"

DMA_Channel_Config_TypeDef default_dma_channel_config(uint32_t* peripheral_address, uint32_t* memory_address) {
    DMA_Channel_Config_TypeDef config;
    config.mem_to_mem = false;
    config.priority = DMA_PRIORITY_LOW;
    config.memory_size = DMA_MEMORY_SIZE_32BIT;
    config.peripheral_size = DMA_MEMORY_SIZE_32BIT;
    config.memory_increment = false;
    config.peripheral_increment = false;
    config.circular_mode = false;
    config.transfer_direction = DMA_TRANSFER_DIRECTION_FROM_PERIPHERAL;
    config.transfer_error_interrupt = false;
    config.half_transfer_interrupt = false;
    config.complete_transfer_interrupt = false;
    config.memory_address = memory_address;
    config.peripheral_address = peripheral_address;
    config.number_of_data = 16;
    return config;
}

DMAMUX_Channel_Config_TypeDef default_dmamux_channel_config(void) {
    DMAMUX_Channel_Config_TypeDef config;
    config.sync_overrun_interrupt = false;
    config.enable_event_generation = false;
    config.enable_sync = false;
    config.number_of_requests = 1;
    config.request_event = DMAMUX_EVENT_NONE;
    config.sync_polarity = DMAMUX_SYNC_POLARITY_NONE;
    return config;
}

void configure_dmamux_channel(DMA_MUX_Register_TypeDef* dmamux_register, DMAMUX_Channel_Config_TypeDef* config, uint8_t channel) {
    reg8_t* dmamux_register_base = (reg8_t*)dmamux_register;
    reg32_t* ccr_reg = (reg32_t*)(dmamux_register_base + 0x04 * channel);
    *ccr_reg &= 0b1111111 | 0b11 << 8 | 0b1111111111111 << 16; //Clear previous configuration
    *ccr_reg |= config->number_of_requests - 1 << 19 |
        config->sync_polarity << 17 |
        config->enable_sync << 16 |
        config->enable_event_generation << 9 |
        config->sync_overrun_interrupt << 8 |
        config->request_event & 0b1111111; //Write new configuration
}

void configure_dma_channel(DMA_Register_TypeDef* dma_register, DMA_Channel_Config_TypeDef* config, uint8_t channel) {
    reg8_t* dma_register_base = (reg8_t*)dma_register;
    reg32_t* ccr_reg = (reg32_t*)(dma_register_base + 0x8 + 0x14 * (channel-1));
    reg32_t* cpar_reg = (reg32_t*)(dma_register_base + 0x10 + 0x14 * (channel-1));
    reg32_t* cmar_reg = (reg32_t*)(dma_register_base + 0x14 + 0x14 * (channel-1));
    reg32_t* cndtr_reg = (reg32_t*)(dma_register_base + 0x0C + 0x14 * (channel-1));

    *ccr_reg &= ~0x3FFF; //Clear previous configuration
    *ccr_reg |= config->mem_to_mem << 14 |
        config->priority << 12 |
        config->memory_size << 10 |
        config->peripheral_size << 8 |
        config->memory_increment << 7 |
        config->peripheral_increment << 6 |
        config->circular_mode << 5 |
        config->transfer_direction << 4 |
        config->transfer_error_interrupt << 3 |
        config->half_transfer_interrupt << 2 |
        config->complete_transfer_interrupt << 1; //Write new configuration

    *cndtr_reg &= ~0x7FFF;
    *cndtr_reg |= config->number_of_data & 0x7FFF;
    *cpar_reg = (reg32_t)config->peripheral_address;
    *cmar_reg = (reg32_t)config->memory_address;

}

void set_dma_channel(DMA_Register_TypeDef* dma_register, bool on, uint32_t channel) {
    reg8_t* dma_register_base = (reg8_t*)dma_register;
    reg32_t* channel_reg = (reg32_t*)(dma_register_base + 0x8 + 0x14*(channel-1)); //Calculate CCR address

    *channel_reg &= ~1; //Clear enable bit
    if (on)
        *channel_reg |= 1; //Enable channel
}