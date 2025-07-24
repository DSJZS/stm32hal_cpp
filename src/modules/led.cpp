#include "main.h"
#include "../../inc/modules/led.hpp"

namespace cya::stm32::module{

Led::Led(peripheral::gpio::Pin& pin, Led::ActiveLevel level)
    : pin_(pin), level_(level)
{
    this->off();
}

Led::Led(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, Led::ActiveLevel level)
    : pin_( GPIOx, GPIO_Pin), level_(level)
{
    this->off();
}

Led::~Led()
{
    this->off();
}

void Led::on(void)
{
    if( this->level_ == ActiveLevel::HIGH )
        this->pin_.set();
    else
        this->pin_.reset();
}

void Led::off(void)
{
    if( this->level_ == ActiveLevel::HIGH )
        this->pin_.reset();
    else
        this->pin_.set();
}

void Led::toggle(void)
{
    this->pin_.toggle();
}

Led::State Led::state(void)
{
    uint8_t pin_state = this->pin_.read();
    if( ( this->level_ == ActiveLevel::HIGH ) && ( pin_state != 0 ) )
        return Led::State::ON;
    else if( ( this->level_ == ActiveLevel::LOW ) && ( pin_state == 0 ) )
        return Led::State::ON;
    else
        return Led::State::OFF;
}

}