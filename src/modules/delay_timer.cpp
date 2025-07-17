#include "../../inc/modules/delay_timer.hpp"

namespace cya::module{

static peripheral::tim::Base* delay_timer_us;

void delay_init(  peripheral::tim::Base* timer_us )
{
    delay_timer_us = timer_us;
}

void delay_us(uint32_t us)
{
    if( us == 0 )
        return;
    
    uint32_t cnt = 0;

    delay_timer_us->set_cnt( 0 );
    delay_timer_us->set_arr( 0xffff );
    delay_timer_us->start();
    while(  us > cnt )
        cnt = delay_timer_us->get_cnt();
    delay_timer_us->stop();
}

void delay_ms(uint32_t ms)
{
    if( ms == 0 )
        return;
    
    while( ms-- )
        delay_us(1000);
}

void delay_s(uint32_t s)
{
    if( s == 0 )
        return;
    
    while( s-- )
        delay_ms(1000);
}

}
