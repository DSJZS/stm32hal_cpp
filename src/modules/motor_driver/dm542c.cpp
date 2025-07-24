#include "../../../inc/modules/motor_driver/dm542c.hpp"
#include "../../../inc/peripherals/gpio.hpp"
#include "../../../inc/peripherals/tim.hpp"

namespace cya::stm32::module::motor_driver{

Dm542c::Dm542c( Dm542c::ConnectType ct, uint16_t microsteps, uint32_t ck_cnt_freq, uint32_t min_out_freq, uint32_t max_out_freq,
        const peripheral::gpio::Pin& EN, const peripheral::gpio::Pin& DIR)
    : ct_(ct), microsteps_(microsteps), ck_cnt_freq_(ck_cnt_freq), min_out_freq_(min_out_freq), max_out_freq_(max_out_freq), 
    EN_(EN), DIR_(DIR)
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
            this->DIR_.reset();
        else
            this->DIR_.set();

    } else if( this->ct_ ==  Dm542c::ConnectType::CA ) {
        if( dire == Dm542c::DireType::CW )
            this->DIR_.set();
        else
            this->DIR_.reset();
    }
}

/********************************************************************************************* */

Dm542c_Pin::Dm542c_Pin(Dm542c::ConnectType ct, uint16_t microsteps, uint32_t ck_cnt_freq, uint32_t min_out_freq, uint32_t max_out_freq,
        const peripheral::gpio::Pin& EN, const peripheral::gpio::Pin& DIR, const peripheral::gpio::Pin& PULSE)
    : Dm542c( ct, microsteps, ck_cnt_freq, min_out_freq, max_out_freq,EN, DIR), PULSE_(PULSE)
{
    this->init();
}

void Dm542c_Pin::init(void)
{
    this->set_enable(1);
    this->set_dire(Dm542c::DireType::CW);
    this->PULSE_.reset();
}



/********************************************************************************************* */


Dm542c_Pwm::Dm542c_Pwm(Dm542c::ConnectType ct, uint16_t microsteps, uint32_t ck_cnt_freq, uint32_t min_out_freq, uint32_t max_out_freq,
        const peripheral::gpio::Pin& EN, const peripheral::gpio::Pin& DIR,
        const peripheral::tim::Pwm_Channel& PULSE,const peripheral::tim::Pwm_Channel& GATE)
    : Dm542c( ct, microsteps, ck_cnt_freq, min_out_freq, max_out_freq, EN, DIR), PULSE_(PULSE), GATE_(GATE)
{
    this->init();
}

Dm542c_Pwm::Dm542c_Pwm(Dm542c::ConnectType ct, uint16_t microsteps, uint32_t ck_cnt_freq, uint32_t min_out_freq, uint32_t max_out_freq,
        const peripheral::gpio::Pin& EN, const peripheral::gpio::Pin& DIR,
        const peripheral::tim::Pwm_Channel& PULSE)
    : Dm542c( ct, microsteps, ck_cnt_freq, min_out_freq, max_out_freq, EN, DIR), PULSE_(PULSE), GATE_(nullptr,0)
{
    this->init();
}

void Dm542c_Pwm::init(void)
{
    this->set_enable(1);
    this->set_dire(Dm542c::DireType::CW);
    this->PULSE_.stop();
    this->GATE_.stop();
}

//  uint16_t 对应 16位CCR
void Dm542c_Pwm::set_step(uint16_t step) const
{
    this->set_enable(1);
    
    this->PULSE_.stop();
    this->GATE_.stop();

    this->PULSE_.set_cnt(0);
    this->GATE_.set_cnt(0);
    this->GATE_.set_ccr(step);

    this->set_enable(0);

    this->PULSE_.start();
    this->GATE_.start();
}

void Dm542c_Pwm::disable_gate(void) const
{
    // if( this->GATE_.isValid() )
    this->GATE_.stop();
    this->GATE_.set_duty(1);    //  关闭门控, 底层自动判断GATE_是否初始化
    this->GATE_.set_cnt(0);
    this->GATE_.start();
}

void Dm542c_Pwm::set_rotation_speed(float base_speed, bool pulse_enable) const
{
    this->set_enable(1);

    if ( base_speed > 0 )
    {
        this->set_dire( Dm542c::DireType::CW );
    }
    else if( base_speed < 0 )
    {
        this->set_dire( Dm542c::DireType::CCW );
        base_speed = -base_speed;
    }
    else
    {
        this->set_enable(1);
        return;
    }

    this->set_enable(0);

    uint16_t freq = this->min_out_freq_ + ( this->max_out_freq_ - this->min_out_freq_ ) * base_speed;
    uint16_t s_value = ( this->ck_cnt_freq_ ) / freq - 1;

    this->PULSE_.stop();
    this->PULSE_.set_arr( s_value );
    this->PULSE_.set_ccr( s_value >> 1 );   //  x >> 1 = x / 2

    if( pulse_enable )
        this->PULSE_.start();
}

void Dm542c_Pwm::set_speed(float base_speed) const
{
    this->disable_gate();
    this->set_rotation_speed( base_speed, true);
}

//  step = angle / ( 360 / microsteps )
//  angle == 0 则关闭门控控制
void Dm542c_Pwm::set_angle(float angle, float base_speed) const
{
    if( this->GATE_.isValid() )
    {
        this->set_rotation_speed(base_speed, false);  //  该函数此时不开启脉冲输出，等待门控设置完成
        if( angle == 0 )                //  如果没有指定的角度，关闭门控
            this->disable_gate();
        else
            this->set_step( (uint16_t)( angle * this->microsteps_ / 360.0f )  );
        this->PULSE_.start();           //  由于 set_rotation_speed 没打开脉冲输出，这里打开
    } else {
        this->set_speed(base_speed);
    }
}

bool Dm542c_Pwm::is_rotation_complete(void) const
{
    if( this->GATE_.isValid() == false )
        return false;
    
    if( this->GATE_.get_cnt() >= this->GATE_.get_ccr() ) // PWM mode 1
        return true;
    else
        return false;
}

}