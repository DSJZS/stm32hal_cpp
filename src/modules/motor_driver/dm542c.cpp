#include "../../../inc/modules/motor_driver/dm542c.hpp"
#include "../../../inc/peripherals/gpio.hpp"
#include "../../../inc/peripherals/tim.hpp"

namespace cya::module::motor_driver{

Dm542c::Dm542c( Dm542c::ConnectType ct, uint16_t microsteps, 
    const peripheral::gpio::Pin& EN, const peripheral::gpio::Pin& DIR )
    : ct_(ct), microsteps_(microsteps), EN_(EN), DIR_(DIR)
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

Dm542c_Pin::Dm542c_Pin(Dm542c::ConnectType ct, uint16_t microsteps,
    const peripheral::gpio::Pin& EN, const peripheral::gpio::Pin& DIR,
    const peripheral::gpio::Pin& PULSE)
    : Dm542c( ct, microsteps, EN, DIR), PULSE_(PULSE)
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


Dm542c_Pwm::Dm542c_Pwm(Dm542c::ConnectType ct, uint16_t microsteps,
    const peripheral::gpio::Pin& EN, const peripheral::gpio::Pin& DIR,
    const peripheral::tim::Pwm_Channel& PULSE,
    const peripheral::tim::Pwm_Channel& GATE)
    : Dm542c( ct, microsteps, EN, DIR), PULSE_(PULSE), GATE_(GATE)
{
    this->init();
}

void Dm542c_Pwm::init(void)
{
    this->set_enable(0);
    this->set_dire(Dm542c::DireType::CW);
    this->PULSE_.stop();
}

void Dm542c_Pwm::set_step(uint16_t step) const
{
    this->set_enable(0);
    
    this->PULSE_.stop();
    // this->GATE_.stop();

    this->PULSE_.set_cnt(0);
    this->GATE_.set_cnt(0);
    this->GATE_.set_compare(step);

    this->set_enable(1);

    this->PULSE_.start();
    // this->GATE_.start();
}

// step = angle / ( 1.8 / microsteps )
void Dm542c_Pwm::set_angle(float angle) const
{
    this->set_step( (uint16_t)( angle * this->microsteps_ / 1.8 )  );
}

}