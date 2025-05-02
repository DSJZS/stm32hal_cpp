#include "main.h"
#include "../../inc/drivers/gpio.hpp"

namespace cya::halcpp::driver::gpio{

Pin::Pin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
    : port_(GPIOx), pin_(GPIO_Pin)
{}

void Pin::set(void) const
{
    if( this->port_ )
        HAL_GPIO_WritePin(this->port_, this->pin_, GPIO_PIN_SET);
}

void Pin::reset(void) const
{
    if( this->port_ )
        HAL_GPIO_WritePin(this->port_, this->pin_, GPIO_PIN_RESET);
}

void Pin::toggle(void) const
{
    if( this->port_ )
        HAL_GPIO_TogglePin(this->port_, this->pin_);
}

GPIO_PinState Pin::read(void) const
{
    if( this->port_ )
        return HAL_GPIO_ReadPin(this->port_, this->pin_);
    return GPIO_PIN_RESET;
}

Port::Port(GPIO_TypeDef* GPIOx)
    : port_(GPIOx)
{}

void Port::set(void) const
{
    if( this->port_ )
            HAL_GPIO_WritePin(this->port_, GPIO_PIN_All, GPIO_PIN_SET);
}

void Port::reset(void) const
{
    if( this->port_ )
            HAL_GPIO_WritePin(this->port_, GPIO_PIN_All, GPIO_PIN_RESET);
}

void Port::toggle(void) const
{
    if( this->port_ )
            HAL_GPIO_TogglePin(this->port_, GPIO_PIN_All);
}

uint16_t Port::read(void) const
{
    return (uint16_t)( this->port_->IDR );
}

}
