#pragma once

#include "main.h"

namespace cya::halcpp::peripheral::gpio{

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
};

}
