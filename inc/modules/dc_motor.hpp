#pragma once

#include "main.h"
#include "motor_base.hpp"
#include "../peripherals/gpio.hpp"
#include "../peripherals/tim.hpp"

namespace cya::module{

class DC_Motor : public Motor_Base{
private:
    const peripheral::gpio::Pin IN_1_;
    const peripheral::gpio::Pin IN_2_;
    const peripheral::tim::Pwm_Channel PWM_;
public:
    DC_Motor();
    DC_Motor(const DC_Motor& other);
    DC_Motor(const peripheral::gpio::Pin& IN_1, const peripheral::gpio::Pin& IN_2,
                const peripheral::tim::Pwm_Channel& PWM);
    virtual void init(void) override;
    virtual void forward(void) const override;
    virtual void back(void) const override;
    virtual int16_t set_speed(float base_speed = 0.0f) const override;
    virtual void bark(void) const override;
    virtual void stop(void) const override;
};

}
