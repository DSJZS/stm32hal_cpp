#pragma once
   
#include "./base.hpp"
#include "../../peripherals/gpio.hpp"
#include "../../peripherals/tim.hpp"

namespace cya::module::motor_driver{

//  默认 共阳极 接法
class Dm542c : public motor_driver::Base{
public:
    enum class ConnectType{
        CC,     //  共阴极
        CA,     //  共阳极
    };
    enum class DireType{
        CW,
        CCW,
    };
    Dm542c( Dm542c::ConnectType ct, const peripheral::gpio::Pin& EN, const peripheral::gpio::Pin& DIR );
protected:
    Dm542c::ConnectType ct_;
    const peripheral::gpio::Pin EN_;
    const peripheral::gpio::Pin DIR_;

    void set_enable( uint8_t enable) const;
    void set_dire( Dm542c::DireType dire) const;
};

class Dm542c_Pin : public Dm542c{
private:
    const peripheral::gpio::Pin PULSE_;
public:
    Dm542c_Pin( Dm542c::ConnectType ct,
        const peripheral::gpio::Pin& EN, const peripheral::gpio::Pin& DIR,
        const peripheral::gpio::Pin& PULSE);

    virtual void init(void) override;
    virtual void set_speed(float base_speed = 0.0f) const override;
};

class Dm542c_Pwm : public Dm542c{
private:
    const peripheral::tim::Pwm_Channel PULSE_;
public:
    Dm542c_Pwm(Dm542c::ConnectType ct,
        const peripheral::gpio::Pin& EN, const peripheral::gpio::Pin& DIR,
        const peripheral::tim::Pwm_Channel& PULSE);

    virtual void init(void) override;
    virtual void set_speed(float base_speed = 0.0f) const override;
};

}