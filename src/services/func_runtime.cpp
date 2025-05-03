#include "main.h"
#include "../../inc/services/func_runtime.hpp"
#include "../../inc/drivers/uart.hpp"
#include "../../inc/drivers/tim.hpp"

namespace cya::halcpp::services{

uint32_t func_runtime::s_max_loss_time_ = 0;
uint32_t func_runtime::s_min_loss_time_ = 4294967295;

func_runtime::func_runtime(const char* __func_name__,
        const driver::Uart& __debug_uart__,
        const driver::tim::Base& __debug_timer_ms__)
    : func_name_(__func_name__),
      debug_uart_(__debug_uart__),debug_timer_ms_(__debug_timer_ms__),
      start_time_(0), end_time_(0)
{
    debug_timer_ms_.start();
    debug_timer_ms_.set_counter(0);
    this->start_time_ = debug_timer_ms_.get_counter();
}

func_runtime::~func_runtime(void)
{
    this->end_time_ = debug_timer_ms_.get_counter();

    uint32_t loss_timer = 0;
    loss_timer = this->end_time_ - this->start_time_;

    if( loss_timer > func_runtime::s_max_loss_time_ )
        func_runtime::s_max_loss_time_ = loss_timer;
    else if( loss_timer < func_runtime::s_min_loss_time_ )
        func_runtime::s_min_loss_time_ = loss_timer;

    this->debug_uart_.printf("%s - max:%u us,min:%u us,cur:%u us\n",
            this->func_name_,
            func_runtime::s_max_loss_time_,
            func_runtime::s_min_loss_time_,
            loss_timer);
}

}
