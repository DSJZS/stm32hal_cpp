/* Includes ------------------------------------------------------------------*/
#include "../inc/interrupt_callback/uart_callback.hpp"

#include "main.h"
/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{

}
//  串口错误
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
//    if( huart == debug_uart.get_ptr_huart() )
//    {
//        debug_uart.receive_toIdle_dma( debug_data, sizeof(debug_data), &hdma_usart1_rx );
//    }
//    else if ( huart == sensor_uart.get_ptr_huart() )
//    {
//        sensor_uart.receive_toIdle_dma( sensor_data, sizeof(sensor_data), &hdma_usart2_rx);
//    }
}
