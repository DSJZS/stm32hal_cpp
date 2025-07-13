/* Includes ------------------------------------------------------------------*/
#include "../inc/interrupt_callback/uart_callback.hpp"

#include "main.h"
#include "stm32hal_cpp.hpp"
#include <stdio.h>
#include "lwrb/lwrb.h"
/* Exported types ------------------------------------------------------------*/
using namespace cya::peripheral;
using namespace cya::module;
using namespace cya::utils;
using namespace cya::protocol;

extern uart::General debug_uart;
extern uint8_t debug_data[256];
extern lwrb_t debug_rb;

extern float error_x_angle;
extern float error_y_angle;
extern pid sx_pid;
extern pid sy_pid;

extern bool i_to_zero_flag;


/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */
Simple_Frame_Parser sfp('@');
uint8_t command[256] = {0};

enum Data_Type
{
    POINT_ERROR = 1,
    ACK = 2,
    CLEAR_I = 3
};

enum Ack_Type{
    NO = 0,
    YES = 1
};

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
        uint16_t command_size = 0;
        lwrb_write( &debug_rb, debug_data, Size);
        if( sfp.get_command( &debug_rb, command, &command_size) )
        {
            if( ( command[0] == Data_Type::POINT_ERROR ) && ( command_size == 9 ))
            {
                uint8_t big_to_small[4] = {0};  //  大小端数据转换
                big_to_small[0] = (command+1)[3];
                big_to_small[1] = (command+1)[2];
                big_to_small[2] = (command+1)[1];
                big_to_small[3] = (command+1)[0];
                error_x_angle = *( (float*)(big_to_small) );
                big_to_small[0] = (command+5)[3];
                big_to_small[1] = (command+5)[2];
                big_to_small[2] = (command+5)[1];
                big_to_small[3] = (command+5)[0];
                error_y_angle = *( (float*)(big_to_small) );
            } else if ( command[0] == Data_Type::ACK ) {
                __NOP();
            } else if( command[0] == Data_Type::CLEAR_I) {
                i_to_zero_flag = true;
            }
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
