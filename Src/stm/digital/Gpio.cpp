/*
 * gpio.cpp
 *
 *  Created on: Jul 9, 2025
 *      Author: markian
 */
#include "../../../Inc/stm/digital/Gpio.h"

namespace stm32::digital::gpio {

    void Gpio::configureGpio(const Pin pin, GpioPinConfiguration &configuration) const {
        const auto pin_number = static_cast<uint8_t>(pin);

        gpioRegisters->MODER &= ~(0b11 << pin_number * 2);
        gpioRegisters->MODER |= static_cast<uint8_t>(configuration.mode) << pin_number * 2;

        gpioRegisters->OTYPER &= ~(1 << pin_number);
        gpioRegisters->OTYPER |= static_cast<uint8_t>(configuration.type) << pin_number;

        gpioRegisters->OSPEEDR &= ~(0b11 << pin_number * 2);
        gpioRegisters->OSPEEDR |= static_cast<uint8_t>(configuration.speed) << pin_number * 2;

        gpioRegisters->PUPDR &= ~(0b11 << pin_number * 2);
        gpioRegisters->PUPDR |= static_cast<uint8_t>(configuration.pull) << pin_number * 2;
    }

    void Gpio::setGpioAlternativeFunction(const Pin pin, const PinAlternativeFunction function) const {
        const auto pin_number = static_cast<uint8_t>(pin);

        volatile uint32_t* afr = (pin_number > 7) ? &gpioRegisters->AFRH : &gpioRegisters->AFRL;
        *afr &= (0xF << (pin_number * 4));
        *afr |= static_cast<uint8_t>(function) << (pin_number * 4);
    }

    void Gpio::writeGpio(const Pin pin, const bool on) const {
        const auto pin_number = static_cast<uint8_t>(pin);

        if (on)
            gpioRegisters->BSRR |= 1 << pin_number;
        else
            gpioRegisters->BSRR |= 1 << 16 << pin_number;
    }

    void Gpio::toggleGpio(const Pin pin) const {
        const auto pin_number = static_cast<uint8_t>(pin);
        gpioRegisters->ODR ^= 1 << pin_number;
    }

    bool Gpio::readGpio(const Pin pin) const {
        const auto pin_number = static_cast<uint8_t>(pin);
        return gpioRegisters->IDR & 1 << pin_number;
    }

}
