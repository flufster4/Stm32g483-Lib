/*
 * gpio.h
 *
 *  Created on: Jul 9, 2025
 *      Author: markian
 */

#pragma once
#include <array>
#include <cstdint>
#include <type_traits>

namespace stm32::digital::gpio {
    struct GpioRegisters {
        volatile uint32_t MODER, OTYPER, OSPEEDR, PUPDR, IDR, ODR, BSRR, LCKR, AFRL, AFRH, BRR;
    };

    enum class PinMode : uint8_t {
        Input,
        Output,
        Alternative,
        Analog
    };

    enum class PinType : uint8_t {
        PushPull,
        OpenDrain
    };

    enum class PinSpeed : uint8_t {
        Low,
        Medium,
        High,
        VeryHigh
    };

    enum class PinPull : uint8_t {
        None,
        PullUp,
        PullDown
    };

    struct GpioPinConfiguration {
        PinMode mode;
        PinType type;
        PinSpeed speed;
        PinPull pull;

        explicit constexpr GpioPinConfiguration(
            const PinMode mode = PinMode::Output,
            const PinType type = PinType::PushPull,
            const PinSpeed speed = PinSpeed::Low,
            const PinPull pull = PinPull::None
            ) : mode(mode), type(type), speed(speed), pull(pull) {}
    };

    class Gpio {
        GpioRegisters* gpioRegisters;

    public:
        explicit Gpio(const uint32_t gpioBaseAddress) : gpioRegisters(reinterpret_cast<GpioRegisters*>(gpioBaseAddress)) {}

        void configureGpio(uint8_t pin, GpioPinConfiguration &configuration) const;

        void writeGpio(uint8_t pin, bool on = true) const;

        void toggleGpio(uint8_t pin) const;

        [[nodiscard]] bool readGpio(uint8_t pin) const;

        template<typename... Args> requires ((!std::is_signed_v<Args> && sizeof(Args) == 1) && ...)
        bool lockPins(Args... pins) {
            const std::array<uint8_t, sizeof...(Args)> extracted_pins = {static_cast<uint8_t>(pins)...};

            for (const uint8_t pin : extracted_pins) {
                if (pin > 15)
                    continue;
                gpioRegisters->LCKR |= 1 << pin;
            }

            gpioRegisters->LCKR |= 1 << 16;
            gpioRegisters->LCKR &= ~(1 << 16);
            gpioRegisters->LCKR |= 1 << 16;

            if (gpioRegisters->LCKR & 1 << 16)
                return true;
            return false;
        }
    };
}
