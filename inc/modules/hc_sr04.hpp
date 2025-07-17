#pragma once

#include "../peripherals/gpio.hpp"
#include "../peripherals/tim.hpp"

namespace cya::module{

class Hc_Sr04{
private:
    const peripheral::gpio::Pin trig_;
    const peripheral::tim::IC ic_direct_;   //  上升沿检测
    const peripheral::tim::IC ic_indirect_; //  下降沿检测

    float up_edge_;
    float down_edge_;
public:
    Hc_Sr04( const peripheral::gpio::Pin& trig, const peripheral::tim::IC& ic_direct, const peripheral::tim::IC& ic_indirect);
    TIM_HandleTypeDef* handle(void);

    void init(void);

    uint32_t get_up_edge_cnt(void);
    uint32_t get_down_edge_cnt(void);

    //  返回值单位为 m
    float get_distance( uint32_t timeout );
};

}