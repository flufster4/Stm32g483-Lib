/*
 * gpio.c
 *
 *  Created on: May 29, 2025
 *      Author: Markian
 */

#include "../../../Inc/gpio.h"

void configure_gpio(GPIO_Register_TypeDef* gpio_register, int32_t pin, GPIO_PIN_MODE mode, GPIO_PIN_SPEED speed, GPIO_PIN_PULL pull, GPIO_PIN_TYPE type) {

    //set pin mode
    gpio_register->MODER &= ~(0b11 << pin * 2);
    gpio_register->MODER |= mode << pin * 2;

    //set pin type
    gpio_register->OTYPER &= ~(1 << pin);
    gpio_register->OTYPER |= type << pin;

    //set pin speed
    gpio_register->OSPEEDR &= ~(0b11 << pin * 2);
    gpio_register->OSPEEDR |= speed << pin * 2;

    //set pin pull
    gpio_register->PUPDR &= ~(0b11 << pin * 2);
    gpio_register->PUPDR |= pull << pin * 2;
}

void set_gpio_pin(GPIO_Register_TypeDef* gpio_register, int32_t pin, bool state) {
    gpio_register->ODR &= ~(1 << pin);
    if (state)
        gpio_register->ODR |= 1 << pin;
}

uint32_t read_gpio_pin(GPIO_Register_TypeDef* gpio_register, int32_t pin) {
    return gpio_register->IDR & 1 << pin;
}

void toggle_gpio_pin(GPIO_Register_TypeDef* gpio_register, int32_t pin) {
    gpio_register->ODR ^= 1 << pin;
}
