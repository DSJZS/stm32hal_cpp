#include "../../../inc/modules/motor_driver/tb6612.hpp"
#include "../../../inc/peripherals/gpio.hpp"
#include "../../../inc/peripherals/tim.hpp"
#include "../../../inc/utils/float_is_equal.hpp"

namespace cya::module::motor_driver{

//  全局定义电机类时需要额外在程序中执行一遍 init()

Tb6612::Tb6612(const Tb6612& other)
    : IN_1_(other.IN_1_), IN_2_(other.IN_2_), PWM_(other.PWM_)
{
    this->init();
}

Tb6612::Tb6612(const peripheral::gpio::Pin& IN_1, const peripheral::gpio::Pin& IN_2,
                const peripheral::tim::Pwm_Channel& PWM)
    : IN_1_(IN_1), IN_2_(IN_2), PWM_(PWM)
{
    this->init();   
}

void Tb6612::forward(void) const
{
    this->IN_1_.set();
    this->IN_2_.reset();
}

void Tb6612::back(void) const
{
    this->IN_1_.reset();
    this->IN_2_.set();
}



void Tb6612::brake(void) const
{
    this->IN_1_.set();
    this->IN_2_.set();
}

void Tb6612::stop(void) const
{
    this->IN_1_.reset();
    this->IN_2_.reset();
}

void Tb6612::init(void)
{
    this->set_speed(0);
    this->PWM_.start();
}

void Tb6612::set_speed(float base_speed) const
{
    if( float_is_equal( base_speed, 0, 1e-3,1e-3) )
    {
        this->brake();
        return;
    }

    if ( base_speed > 0 )
    {
        this->forward();
    }
    else if( base_speed < 0 )
    {
        this->back();
        base_speed = -base_speed;
    }

    this->PWM_.set_duty(base_speed);
}

}