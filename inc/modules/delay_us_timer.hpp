#pragma once

#include <stdint.h>
#include "../peripherals/tim.hpp"

namespace cya::module{

class delay_us_timer{
private:
    peripheral::tim::Base* debug_timer_us_;
public:
    uint16_t is_delaying;
    
    delay_us_timer(peripheral::tim::Base* debug_timer_us);
    ~delay_us_timer();
    
    TIM_HandleTypeDef* handle(void);
    void delay_us(uint16_t us);
};

}
