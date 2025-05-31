#ifndef __CORE_INTERRUPT_H__
#define __CORE_INTERRUPT_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

/*  严格遵守一进一出原则  */

/*  进入临界区函数  */
uint32_t enter_critical(void);
/*  退出临界区函数  */
void exit_critical(void);

#ifdef __cplusplus
}
#endif

#endif // __CORE_INTERRUPT_H__