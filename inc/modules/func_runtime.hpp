#pragma once

#include <stdint.h>
#include "../peripherals/uart.hpp"
#include "../peripherals/tim.hpp"

namespace cya::stm32::module{

/* 函数耗时定时器
 * 用于测量一个函数耗费了多少时间
 *
 * 用法：
 *      需要提供一个串口、us计数的定时器(建议使用基本定时器)
 *      __func_name__ 参数建议使用 __PRETTY_FUNCTION__
 *          如果编译器不支持则使用 __func__ 等
 *      将类对象放在测量代码块的第一行定义
 * 输出：
 *      每次输出测量函数名，函数的最大耗时，最小耗时，本轮耗时
 * 注意：尽量每次只测量一个函数的耗时，
 *      如果一次性测量多个函数，则最大耗时与最小耗时不可信
 *      只有每个函数的本轮耗时值可信，需要外部串口助手辅助测量每个函数最大值与最小值
 */

class func_runtime{
private:
    const char* func_name_;
    peripheral::tim::Base* debug_timer_ms_;
    peripheral::uart::General* debug_uart_;
    uint32_t start_time_;
    uint32_t end_time_;
    static uint32_t s_max_loss_time_;
    static uint32_t s_min_loss_time_;
public:
    func_runtime(const char* __func_name__, peripheral::tim::Base* __debug_timer_ms__, peripheral::uart::General* __debug_uart__);
    ~func_runtime();
};

}
