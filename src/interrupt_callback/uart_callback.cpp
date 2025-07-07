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

cya::protocol::Simple_Frame_Parser sfp('@');
cya::utils::Cyclic_Buffer_Receiver cyc_buffer( debug_data, 256);
uint8_t command[256] = {0};
cya::protocol::Parser_IO pio = { &cyc_buffer, command, 0, nullptr};

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if( huart == debug_uart.handle() )
    {
        debug_uart.receive_dma( debug_data, sizeof(debug_data));
    }
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
    if( huart == debug_uart.handle() )
    {
        cyc_buffer.write( debug_data, Size);
        if( sfp.get_command(&pio) )
        {
            __NOP();
        }
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
