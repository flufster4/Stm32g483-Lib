/*
 * gpio.cpp
 *
 *  Created on: Jul 9, 2025
 *      Author: markian
 */
#include "../../../Inc/stm/digital/Gpio.h"

namespace stm32::digital::gpio {

    void Gpio::configureGpio(const uint8_t pin, GpioPinConfiguration &configuration) const {
        if (pin > 15)
            return;

        gpioRegisters->MODER &= ~(0b11 << pin * 2);
        gpioRegisters->MODER |= static_cast<uint8_t>(configuration.mode) << pin * 2;

        gpioRegisters->OTYPER &= ~(1 << pin);
        gpioRegisters->OTYPER |= static_cast<uint8_t>(configuration.type) << pin;

        gpioRegisters->OSPEEDR &= ~(0b11 << pin * 2);
        gpioRegisters->OSPEEDR |= static_cast<uint8_t>(configuration.speed) << pin * 2;

        gpioRegisters->PUPDR &= ~(0b11 << pin * 2);
        gpioRegisters->PUPDR |= static_cast<uint8_t>(configuration.pull) << pin * 2;
    }

    void Gpio::setGpioAlternativeFunction(const uint8_t pin, const PinAlternativeFunction function) const {
        volatile uint32_t* afr = (pin > 7) ? &gpioRegisters->AFRH : &gpioRegisters->AFRL;
        const uint8_t shift = (pin % 8) * 4;

        *afr &= ~(0xF << shift);
        *afr |= (static_cast<uint8_t>(function) << shift);
    }


    void Gpio::writeGpio(const uint8_t pin, const bool on) const {
        if (pin > 15)
            return;

        if (on)
            gpioRegisters->BSRR |= 1 << pin;
        else
            gpioRegisters->BSRR |= 1 << 16 << pin;
    }

    void Gpio::toggleGpio(const uint8_t pin) const {
        if (pin > 15)
            return;
        gpioRegisters->ODR ^= 1 << pin;
    }

    bool Gpio::readGpio(const uint8_t pin) const {
        if (pin > 15)
            return false;
        return gpioRegisters->IDR & 1 << pin;
    }

}
