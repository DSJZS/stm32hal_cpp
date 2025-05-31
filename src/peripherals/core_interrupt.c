#include "../../inc/peripherals/core_interrupt.h"
#include "main.h"

volatile static uint32_t regPrimask = 0;

uint32_t enter_critical(void)
{
    // 保存当前 PRIMASK 值
    regPrimask = __get_PRIMASK();
    // 关闭系统全局中断（其实就是将 PRIMASK 设为 1）
    __disable_irq();
 
    return regPrimask;
}
 
void exit_critical(void)
{
    // 恢复 PRIMASK
    __set_PRIMASK(regPrimask);
}