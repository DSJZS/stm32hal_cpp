#include "main.h"
#include "../../inc/modules/delay_us_timer.hpp"

namespace cya::module{

delay_us_timer::delay_us_timer(peripheral::tim::Base* debug_timer_us)
    : debug_timer_us_(debug_timer_us)
{}

delay_us_timer::~delay_us_timer()
{}

TIM_HandleTypeDef* delay_us_timer::handle(void)
{
    return this->debug_timer_us_->handle();
}

void delay_us_timer::delay_us(uint16_t us)
{
    if( us == 0 )
        return;
    
    this->is_delaying = us;
    this->debug_timer_us_->set_cnt( 0 );
    this->debug_timer_us_->start_it();
    while( this->is_delaying );
    this->debug_timer_us_->stop_it();
}

}
