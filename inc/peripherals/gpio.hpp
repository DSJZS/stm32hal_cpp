#pragma once

#include "main.h"

namespace cya::peripheral::gpio{

class Pin{
private:
    GPIO_TypeDef* port_;
    uint16_t pin_;
public:
    Pin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
    void set(void) const;
    void reset(void) const;
    void toggle(void) const;
    GPIO_PinState read(void) const;
    void write(uint8_t pin_state) const;

    Pin& operator>>( uint8_t& state);
    Pin& operator<<( uint8_t& state);
};

class Port{
private:
    GPIO_TypeDef* port_;
public:
    Port(GPIO_TypeDef* GPIOx);
    void set(void) const;
    void reset(void) const;
    void toggle(void) const;
    uint16_t read(void) const;
    void write(uint16_t port_state) const;

    Port& operator>>( uint16_t& state);
    Port& operator<<( uint16_t& state);
};

}
