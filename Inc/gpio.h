/*
 * gpio.h
 *
 *  Created on: May 29, 2025
 *      Author: markian
 */


#ifndef GPIO_H_
#define GPIO_H_

    #include "util.h"

    typedef struct {
        reg32_t MODER;
        reg32_t OTYPER;
        reg32_t OSPEEDR;
        reg32_t PUPDR;
        reg32_t IDR;
        reg32_t ODR;
        reg32_t BSRR;
        reg32_t LCKR;
        reg32_t AFRL;
        reg32_t AFRH;
        reg32_t BRR;
    } GPIO_Register_TypeDef;

    typedef enum {
        GPIO_SPEED_LOW,
        GPIO_SPEED_MEDIUM,
        GPIO_SPEED_HIGH,
        GPIO_SPEED_VERY_HIGH
    } GPIO_PIN_SPEED;

    typedef enum {
        GPIO_MODE_INPUT,
        GPIO_MODE_OUTPUT,
        GPIO_MODE_ALTERNATE,
        GPIO_MODE_ANALOG
    } GPIO_PIN_MODE;

    typedef enum {
        GPIO_TYPE_PUSH_PULL,
        GPIO_TYPE_OPEN_DRAIN
    } GPIO_PIN_TYPE;

    typedef enum {
        GPIO_PULL_NO_PULL,
        GPIO_PULL_PULL_UP,
        GPIO_PULL_PULL_DOWN,
    } GPIO_PIN_PULL;

    void configure_gpio(GPIO_Register_TypeDef* gpio_register, int32_t pin, GPIO_PIN_MODE mode, GPIO_PIN_SPEED speed, GPIO_PIN_PULL pull, GPIO_PIN_TYPE type);

    void set_gpio_pin(GPIO_Register_TypeDef* gpio_register, int32_t pin, bool state);

    uint32_t read_gpio_pin(GPIO_Register_TypeDef* gpio_register, int32_t pin);

    void toggle_gpio_pin(GPIO_Register_TypeDef* gpio_register, int32_t pin);

#endif /* GPIO_H_ */
