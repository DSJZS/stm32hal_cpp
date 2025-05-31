#include "main.h"
#include "../../inc/modules/dc_motor.hpp"
#include "../../inc/peripherals/gpio.hpp"
#include "../../inc/peripherals/tim.hpp"

namespace cya::module{

DC_Motor::DC_Motor()
    : IN_1_(NULL,0), IN_2_(NULL,0), PWM_(NULL,0,0)
{
    //  空电机类，为了避免全局类无法正常初始化外设的问题
}

DC_Motor::DC_Motor(const DC_Motor& other)
    : IN_1_(other.IN_1_), IN_2_(other.IN_2_), PWM_(other.PWM_)
{
    this->init();
}

DC_Motor::DC_Motor(const peripheral::gpio::Pin& IN_1, const peripheral::gpio::Pin& IN_2,
                const peripheral::tim::Pwm_Channel& PWM)
    : IN_1_(IN_1), IN_2_(IN_2), PWM_(PWM)
{
    this->init();   //  全局定义电机类时需要额外在程序中执行一遍 Motor::init()
}

void DC_Motor::init(void)
{
    this->set_speed(0);
    this->PWM_.start();
}

void DC_Motor::forward(void) const
{
    this->IN_1_.set();
    this->IN_2_.reset();
}

void DC_Motor::back(void) const
{
    this->IN_1_.reset();
    this->IN_2_.set();
}

// base_speed ∈ ( -200 ~ 200 )
int16_t DC_Motor::set_speed(float base_speed) const
{
    if ( base_speed > 0 )
    {
        this->forward();
    }
    else if( base_speed < 0 )
    {
        this->back();
        base_speed = -base_speed;
    }
    else
    {
        this->bark();
    }

    this->PWM_.set_compare(base_speed);
    return base_speed;
}

void DC_Motor::bark(void) const
{
    this->IN_1_.set();
    this->IN_2_.set();
}

void DC_Motor::stop(void) const
{
    this->IN_1_.reset();
    this->IN_2_.reset();
}

}
