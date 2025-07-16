#pragma once

#include "../peripherals/gpio.hpp"
#include "../peripherals/tim.hpp"

namespace cya::module{

class Hc_Sr04{
private:
    const peripheral::gpio::Pin trig_;
    const peripheral::tim::IC ic_direct_;   //  上升沿检测
    const peripheral::tim::IC ic_indirect_; //  下降沿检测
public:
    Hc_Sr04( const peripheral::gpio::Pin& trig, const peripheral::tim::IC& ic_direct, const peripheral::tim::IC& ic_indirect);

    void init(void);
    uint16_t get_distance(void);
};

}