/* Includes ------------------------------------------------------------------*/
#include "../inc/interrupt_callback/tim_callback.hpp"

#include "main.h"
#include "tim.h"
#include "../../function_timer/function_timer.h"
#include "stm32hal_cpp.hpp"

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */



void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    
// 如果 USE_FTIMER 定义并且为 1, 为函数定时器计数
#if defined (USE_FTIMER) && (USE_FTIMER == 1U)
    if(htim == ftimer_handle)
    {
        FTimer_Loop();
    }
#endif

}


