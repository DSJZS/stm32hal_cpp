#include "main.h"
#include "../../inc/modules/hc_sr04.hpp"
#include "../../inc/modules/delay_timer.hpp"
#include <cmath>

namespace cya::module{

Hc_Sr04::Hc_Sr04( const peripheral::gpio::Pin& trig, const peripheral::tim::IC& ic_direct, const peripheral::tim::IC& ic_indirect)
    : trig_(trig), ic_direct_(ic_direct), ic_indirect_(ic_indirect)
{
    this->init();
}

TIM_HandleTypeDef* Hc_Sr04::handle(void)
{
    return ic_direct_.handle();
}

void Hc_Sr04::init(void)
{
    this->trig_.reset();

    TIM_HandleTypeDef* htim = ic_direct_.handle();
    HAL_TIM_Base_Start( htim );
    this->ic_direct_.start();
    this->ic_indirect_.start_it();
}

uint32_t Hc_Sr04::get_up_edge_cnt(void)
{
    this->up_edge_ = this->ic_direct_.get_ccr();
    return this->up_edge_;
}

uint32_t Hc_Sr04::get_down_edge_cnt(void)
{
    this->down_edge_ = this->ic_indirect_.get_ccr();
    return this->down_edge_;
}

//  返回值单位为 m
//  timeout 每加一，约等于在 SYSCLK == 168MHz 的情况下增加最大超时 1.1us
float Hc_Sr04::get_distance( uint32_t timeout )
{
    this->up_edge_ = 0;
    this->down_edge_ = 0;

    this->trig_.set();
    //  延时 40~50 us
    delay_us(45);
    this->trig_.reset();
    this->ic_direct_.set_cnt(0);

    while( !(this->up_edge_) || !(this->down_edge_) )
    {
        if( timeout != 0xFFFFFFFFU )
        {
            --timeout;
            if( !timeout )
                return std::numeric_limits<float>::infinity();
        }
    }

    //  n(us)  *  0.00034m/us = distance(m)
    return ( ( this->down_edge_ - this->up_edge_ ) * 0.00034 ) / 2;
}



}