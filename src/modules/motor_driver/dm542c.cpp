#include "../../../inc/modules/motor_driver/dm542c.hpp"
#include "../../../inc/peripherals/gpio.hpp"
#include "../../../inc/peripherals/tim.hpp"

namespace cya::module::motor_driver{

Dm542c::Dm542c( Dm542c::ConnectType ct, const peripheral::gpio::Pin& EN, const peripheral::gpio::Pin& DIR )
    : ct_(ct), EN_(EN), DIR_(DIR)
{}

void Dm542c::set_enable(uint8_t enable) const
{
    if( this->ct_ ==  Dm542c::ConnectType::CC )
    {
        if( enable == 0 )
            this->EN_.reset();
        else
            this->EN_.set();

    } else if( this->ct_ ==  Dm542c::ConnectType::CA ) {
        if( enable == 0 )
            this->EN_.set();
        else
            this->EN_.reset();
    }
}

void Dm542c::set_dire( Dm542c::DireType dire) const
{
    if( this->ct_ ==  Dm542c::ConnectType::CC )
    {
        if( dire == Dm542c::DireType::CW )
            this->EN_.reset();
        else
            this->EN_.set();

    } else if( this->ct_ ==  Dm542c::ConnectType::CA ) {
        if( dire == Dm542c::DireType::CW )
            this->EN_.set();
        else
            this->EN_.reset();
    }
}

/********************************************************************************************* */

Dm542c_Pin::Dm542c_Pin(Dm542c::ConnectType ct,
    const peripheral::gpio::Pin& EN, const peripheral::gpio::Pin& DIR,
    const peripheral::gpio::Pin& PULSE)
    : Dm542c( ct, EN, DIR), PULSE_(PULSE)
{
    this->init();
}

void Dm542c_Pin::init(void)
{
    this->set_enable(0);
    this->set_dire(Dm542c::DireType::CW);
    this->PULSE_.reset();
}



/********************************************************************************************* */


Dm542c_Pwm::Dm542c_Pwm(Dm542c::ConnectType ct,
    const peripheral::gpio::Pin& EN, const peripheral::gpio::Pin& DIR,
    const peripheral::tim::Pwm_Channel& PULSE)
    : Dm542c( ct, EN, DIR), PULSE_(PULSE)
{
    this->init();
}

void Dm542c_Pwm::init(void)
{
    this->set_enable(0);
    this->set_dire(Dm542c::DireType::CW);
    this->PULSE_.stop();
}

}