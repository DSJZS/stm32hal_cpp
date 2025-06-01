#include "../../inc/peripherals/core_interrupt.h"
#include "main.h"

uint32_t enter_critical(void)
{
    // 保存当前 PRIMASK 值
    uint32_t regPrimask = __get_PRIMASK();
    // 关闭系统全局中断（其实就是将 PRIMASK 设为 1）
    __disable_irq();
 
    return regPrimask;
}
 
void exit_critical(uint32_t primask)
{
    // 恢复 PRIMASK
    __set_PRIMASK(primask);
}