#include "main.h"
#include "../../inc/peripherals/gpio.hpp"

namespace cya::peripheral::gpio{

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

void Pin::write(uint8_t pin_state) const
{
    if( this->port_ == NULL )
        return;
    if( pin_state != 0 )
        this->set();
    else
        this->reset();
}

Pin& Pin::operator>>( uint8_t state )
{
    state = this->read();
    return *this;
}

Pin& Pin::operator<<( uint8_t state)
{
    this->write(state);
    return *this;
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
    if( this->port_ )
        return (uint16_t)( this->port_->IDR );
    return 0;
}

void Port::write(uint16_t port_state) const
{
    if( this->port_ )
    {
        for( uint32_t i = (uint32_t)0x0001 ; i < (uint32_t)0xFFFF ; i <<= 1 )
        {
            if( port_state & i )
                HAL_GPIO_WritePin(this->port_, i, GPIO_PIN_SET);
            else
                HAL_GPIO_WritePin(this->port_, i, GPIO_PIN_RESET);
        }
    }
}

Port& Port::operator>>( uint16_t state)
{
    state = this->read();
    return *this;
}

Port& Port::operator<<( uint16_t state)
{
    this->write(state);
    return *this;
}

}
