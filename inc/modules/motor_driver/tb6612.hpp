#pragma once

#include "./base.hpp"
#include "../../peripherals/gpio.hpp"
#include "../../peripherals/tim.hpp"

namespace cya::hal::module::motor_driver{

class Tb6612 : public motor_driver::Base{
private:
    const peripheral::gpio::Pin IN_1_;
    const peripheral::gpio::Pin IN_2_;
    const peripheral::tim::Pwm_Channel PWM_;

    void forward(void) const;
    void back(void) const;
    void brake(void) const;
    void stop(void) const;
public:
    Tb6612(const Tb6612& other);
    Tb6612(const peripheral::gpio::Pin& IN_1, const peripheral::gpio::Pin& IN_2,
            const peripheral::tim::Pwm_Channel& PWM);

    virtual void init(void) override;
    virtual void set_speed(float base_speed = 0.0f) const override;
    
};

}
