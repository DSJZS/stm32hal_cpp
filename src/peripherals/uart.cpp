#include "main.h"
#include "../../inc/peripherals/uart.hpp"
#include <stdio.h>
#include <stdarg.h>
#include <cstring>

namespace cya::halcpp::peripheral{

Uart::Uart(UART_HandleTypeDef* ptr_huart)
    : ptr_huart_(ptr_huart)
{}

Uart::Uart(const Uart& other_uart)
    : ptr_huart_(other_uart.ptr_huart_)
{}

UART_HandleTypeDef* Uart::get_ptr_huart(void) const
{
    return this->ptr_huart_;
}

HAL_StatusTypeDef Uart::transmit( const uint8_t *pData,
        uint16_t Size, uint32_t Timeout) const
{
    if( this->ptr_huart_ )
        return HAL_UART_Transmit(this->ptr_huart_,pData,Size,Timeout);
    return HAL_ERROR;
}

HAL_StatusTypeDef Uart::receive( uint8_t *pData,
        uint16_t Size, uint32_t Timeout) const
{
    if( this->ptr_huart_ )
        return HAL_UART_Receive(this->ptr_huart_, pData, Size, Timeout);
    return HAL_ERROR;
}

HAL_StatusTypeDef Uart::receive_it( uint8_t *pData, uint16_t Size) const
{
    if( this->ptr_huart_ )
        return HAL_UART_Receive_IT(this->ptr_huart_, pData, Size);
    return HAL_ERROR;
}

HAL_StatusTypeDef Uart::transmit_it( const uint8_t *pData, uint16_t Size) const
{
    if( this->ptr_huart_ )
        return HAL_UART_Transmit_IT(this->ptr_huart_,pData,Size);
    return HAL_ERROR;
}

HAL_StatusTypeDef Uart::receive_dma( uint8_t *pData, uint16_t Size) const
{
    if( this->ptr_huart_ )
        return HAL_UART_Receive_DMA(this->ptr_huart_, pData, Size);
    return HAL_ERROR;
}

HAL_StatusTypeDef Uart::transmit_dma( const uint8_t *pData, uint16_t Size) const
{
    if( this->ptr_huart_ )
        return HAL_UART_Transmit_DMA(this->ptr_huart_,pData,Size);
    return HAL_ERROR;
}

HAL_StatusTypeDef Uart::receive_toIdle( uint8_t *pData,
        uint16_t Size, uint16_t* RxLen, uint32_t Timeout) const
{
    if( this->ptr_huart_ )
        return HAL_UARTEx_ReceiveToIdle(this->ptr_huart_, pData, Size, RxLen, Timeout);
    return HAL_ERROR;
}

HAL_StatusTypeDef Uart::receive_toIdle_it( uint8_t *pData, uint16_t Size) const
{
    if( this->ptr_huart_ )
        return HAL_UARTEx_ReceiveToIdle_IT(this->ptr_huart_, pData, Size);
    return HAL_ERROR;
}

HAL_StatusTypeDef Uart::receive_toIdle_dma( uint8_t *pData, uint16_t Size,
        DMA_HandleTypeDef* ptr_hdma_usart_rx) const
{
    if( this->ptr_huart_ )
    {
        HAL_StatusTypeDef ret = HAL_OK;
        ret = HAL_UARTEx_ReceiveToIdle_DMA(this->ptr_huart_, pData, Size);
        if( ptr_hdma_usart_rx )
            __HAL_DMA_DISABLE_IT( ptr_hdma_usart_rx, DMA_IT_HT);    //  关闭DMA过半传输中断
        return ret;
    }
    return HAL_ERROR;
}

HAL_StatusTypeDef Uart::printf(const char* format, ...) const
{
    if( this->ptr_huart_ )
    {
        char tmp_string[Uart::kPrintBuffLen] = {0};
        va_list arg;
        va_start( arg, format);
        vsprintf( tmp_string, format, arg);
        va_end(arg);
        return this->transmit( (uint8_t*)tmp_string, strlen(tmp_string));
    }
    return HAL_ERROR;
}

HAL_StatusTypeDef Uart::printf_it(const char* format, ...) const
{
    if( this->ptr_huart_ )
    {
        char tmp_string[Uart::kPrintBuffLen] = {0};
        va_list arg;
        va_start( arg, format);
        vsprintf( tmp_string, format, arg);
        va_end(arg);
        return this->transmit_it( (uint8_t*)tmp_string, strlen(tmp_string));
    }
    return HAL_ERROR;
}

HAL_StatusTypeDef Uart::printf_dma(const char* format, ...) const
{
    if( this->ptr_huart_ )
    {
        char tmp_string[Uart::kPrintBuffLen] = {0};
        va_list arg;
        va_start( arg, format);
        vsprintf( tmp_string, format, arg);
        va_end(arg);
        return this->transmit_dma( (uint8_t*)tmp_string, strlen(tmp_string));
    }
    return HAL_ERROR;
}

}
