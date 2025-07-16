#include "main.h"
#include "../../inc/modules/hc_sr04.hpp"

namespace cya::module{

Hc_Sr04::Hc_Sr04( const peripheral::gpio::Pin& trig, const peripheral::tim::IC& ic_direct, const peripheral::tim::IC& ic_indirect)
    : trig_(trig), ic_direct_(ic_direct), ic_indirect_(ic_indirect)
{
    this->init();
}

void Hc_Sr04::init(void)
{
    this->trig_.reset();

    TIM_HandleTypeDef* htim = ic_direct_.handle();
    HAL_TIM_Base_Start( htim );
    this->ic_direct_.start();
    this->ic_indirect_.start_it();
}

uint16_t Hc_Sr04::get_distance(void)
{
    this->trig_.set();
    //  延时 40~50 us

    this->trig_.reset();
    this->ic_direct_.set_cnt(0);
}

}