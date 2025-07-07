/* Includes ------------------------------------------------------------------*/
#include "../inc/interrupt_callback/uart_callback.hpp"

#include "main.h"
#include "stm32hal_cpp.hpp"
/* Exported types ------------------------------------------------------------*/
extern cya::peripheral::uart::General debug_uart;
extern uint8_t debug_data[256];
/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
    if( huart == debug_uart.handle() )
    {
        debug_uart.receive_toIdle_dma( debug_data, sizeof(debug_data));
    }
}

//  串口错误
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
   if( huart == debug_uart.handle() )
   {
       debug_uart.receive_toIdle_dma( debug_data, sizeof(debug_data));
   }
}
