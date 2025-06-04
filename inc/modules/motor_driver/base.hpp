#pragma once

#include "main.h"

namespace cya::module::motor_driver{

class Base{
public:
    virtual void init(void) = 0;
    virtual void forward(void) const = 0;
    virtual void back(void) const = 0;

    //  按照百分比设定速度与方向，为 -1 ~ +1
    //  正则正转，反则反转，绝对值越大转的越快
    virtual int16_t set_speed(float base_speed = 0.0f) const = 0;

    virtual void bark(void) const = 0;
    virtual void stop(void) const = 0;
};

}
