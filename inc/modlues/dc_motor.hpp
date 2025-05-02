#pragma once

#include "main.h"
#include "motor.hpp"
#include "../drivers/gpio.hpp"
#include "../drivers/tim.hpp"

namespace cya::halcpp::modlues{

class DC_Motor : public Motor{
private:
    const driver::gpio::Pin IN_1_;
    const driver::gpio::Pin IN_2_;
    const driver::tim::Pwm_Channel PWM_;
public:
    DC_Motor();
    DC_Motor(const DC_Motor& other);
    DC_Motor(const driver::gpio::Pin& IN_1, const driver::gpio::Pin& IN_2,
                const driver::tim::Pwm_Channel& PWM);
    virtual void init(void) override;
    virtual void forward(void) const override;
    virtual void back(void) const override;
    virtual int16_t set_speed(float base_speed = 0.0f) const override;
    virtual void bark(void) const override;
    virtual void stop(void) const override;
};

}
