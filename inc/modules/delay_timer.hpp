#pragma once

#include <stdint.h>
#include "../peripherals/tim.hpp"

namespace cya::hal::module{

//  需要提供预分频后时钟为 1MHZ 的定时器
void delay_init(  peripheral::tim::Base* p_timer );

void delay_us(uint32_t us);
void delay_ms(uint32_t ms);
void delay_s(uint32_t s);

}
