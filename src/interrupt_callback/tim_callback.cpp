/* Includes ------------------------------------------------------------------*/
#include "../inc/interrupt_callback/tim_callback.hpp"

#include "main.h"
#include "tim.h"
#include "../../function_timer/function_timer.h"
#include "stm32hal_cpp.hpp"

/* Exported types ------------------------------------------------------------*/
using namespace cya;
extern peripheral::Uart debug_uart;
extern peripheral::tim::Base debug_us_tim;

extern peripheral::tim::Base adc_50khz_tim;
extern uint16_t adc_values[2];
extern constexpr uint16_t v_buffer_size = 1024;
extern float voltage[2][v_buffer_size];
extern uint16_t v_index;
extern uint8_t v_buffer;

extern uint64_t s_period;   //  单位 1us
extern float s_freq;        //  单位 1hz
extern float s_vp;          //  单位 1v

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/
#define SIGN_VP (3.3f)
#define SIGN_SYMBOL_THR     (0.08)//0.5

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

    //  100KHZ - 10us - 10.24ms获取一组1024数组，即有大约10ms用来处理每组1024数据
    if(htim == &htim2)
    {
        static uint64_t s_half_period = 0;
        static float s_half_period_vp = 0;

        float v_abs = adc_values[0] / 4095.0f * SIGN_VP ;
        float v_symbol = adc_values[1] / 4095.0f;
        int8_t data_symbol = ( v_symbol > SIGN_SYMBOL_THR ) ? 1 : -1;
        float v_real = v_abs * v_symbol;

        voltage[v_buffer][v_index++] = v_real;

        if( v_index >= v_buffer_size )
        {
            v_buffer = !v_buffer;
            v_index = 0;
        }

        static int8_t last_data_symbol = data_symbol;

        if( last_data_symbol != data_symbol )
        {
            s_period = 2 * s_half_period * 10;
            s_freq = 1000000.0f / s_period;
            s_vp = s_half_period_vp;

            s_half_period_vp = 0;
            s_half_period = 0;

            last_data_symbol = data_symbol;
        } else {
            if( v_abs > s_half_period_vp )
                s_half_period_vp = v_abs;
            ++s_half_period;    //  以10us为单位计数
        }

        //  84MHZ主频下平均耗时 1us 完成上述操作
        //  不建议在该函数内使用串口，因为使用串口会导致额外耗时大约800~900us
        //  debug_uart.printf("%f\n",v_abs * data_symbol);
    }
}


