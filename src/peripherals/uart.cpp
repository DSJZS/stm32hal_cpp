#include "main.h"
#include "../../inc/peripherals/uart.hpp"
#include <stdio.h>
#include <stdarg.h>
#include <cstring>

namespace cya::peripheral{

/* ***************************block*************************** */

Uart_Base::Uart_Base(UART_HandleTypeDef* ptr_huart)
    : ptr_huart_(ptr_huart)
{}

Uart_Block::Uart_Block(UART_HandleTypeDef* ptr_huart)
    : Uart_Base(ptr_huart)
{}

Uart_Block::Uart_Block( const Uart_Block& other )
    : Uart_Base(other.ptr_huart_)
{}

Uart_Block::Uart_Block( Uart_Block&& other)
    : Uart_Base(other.ptr_huart_)
{
    other.ptr_huart_ = nullptr;
}

HAL_StatusTypeDef Uart_Block::transmit( const uint8_t *pData, uint16_t Size, uint32_t Timeout) const
{
    if( this->ptr_huart_ )
        return HAL_UART_Transmit(this->ptr_huart_,pData,Size,Timeout);
    return HAL_ERROR;
}

HAL_StatusTypeDef Uart_Block::receive( uint8_t *pData, uint16_t Size, uint32_t Timeout) const
{
    if( this->ptr_huart_ )
        return HAL_UART_Receive(this->ptr_huart_, pData, Size, Timeout);
    return HAL_ERROR;
}

HAL_StatusTypeDef Uart_Block::receive_toIdle( uint8_t *pData, uint16_t Size, uint16_t *RxLen, uint32_t Timeout) const
{
    if( this->ptr_huart_ )
        return HAL_UARTEx_ReceiveToIdle(this->ptr_huart_, pData, Size, RxLen, Timeout);
    return HAL_ERROR;
}

HAL_StatusTypeDef Uart_Block::printf(const char* format, ...) const
{
    if( this->ptr_huart_ )
    {
        char tmp_string[Uart_Base::kPrintBuffLen] = {0};
        va_list arg;
        va_start( arg, format);
        vsprintf( tmp_string, format, arg);
        va_end(arg);
        return this->transmit( (uint8_t*)tmp_string, strlen(tmp_string));
    }
    return HAL_ERROR;
}

/* ***************************block*************************** */

/* ****************************it***************************** */

Uart_It::Uart_It(UART_HandleTypeDef* ptr_huart)
    : Uart_Base(ptr_huart)
{}

Uart_It::Uart_It( const Uart_It& other )
    : Uart_Base(other.ptr_huart_)
{}

Uart_It::Uart_It( Uart_It&& other)
    : Uart_Base(other.ptr_huart_)
{
    other.ptr_huart_ = nullptr;
}

HAL_StatusTypeDef Uart_It::transmit( const uint8_t *pData, uint16_t Size) const
{
    if( this->ptr_huart_ )
        return HAL_UART_Transmit_IT(this->ptr_huart_,pData,Size);
    return HAL_ERROR;
}

HAL_StatusTypeDef Uart_It::receive( uint8_t *pData, uint16_t Size) const
{
    if( this->ptr_huart_ )
        return HAL_UART_Receive_IT(this->ptr_huart_, pData, Size);
    return HAL_ERROR;
}

HAL_StatusTypeDef Uart_It::receive_toIdle( uint8_t *pData, uint16_t Size) const
{
    if( this->ptr_huart_ )
        return HAL_UARTEx_ReceiveToIdle_IT(this->ptr_huart_, pData, Size);
    return HAL_ERROR;
}

HAL_StatusTypeDef Uart_It::printf(const char* format, ...) const
{
    if( this->ptr_huart_ )
    {
        char tmp_string[Uart_Base::kPrintBuffLen] = {0};
        va_list arg;
        va_start( arg, format);
        vsprintf( tmp_string, format, arg);
        va_end(arg);
        return this->transmit( (uint8_t*)tmp_string, strlen(tmp_string));
    }
    return HAL_ERROR;
}

/* ****************************it***************************** */

/* ****************************dma**************************** */

Uart_Dma::Uart_Dma(UART_HandleTypeDef* ptr_huart, DMA_HandleTypeDef* ptr_dma_rx, DMA_HandleTypeDef* ptr_dma_tx)
    : Uart_Base(ptr_huart), ptr_dma_rx_(ptr_dma_rx), ptr_dma_tx_(ptr_dma_tx)
{}

Uart_Dma::Uart_Dma( const Uart_Dma& other )
    : Uart_Base(other.ptr_huart_), ptr_dma_rx_(other.ptr_dma_rx_), ptr_dma_tx_(other.ptr_dma_tx_)
{}

Uart_Dma::Uart_Dma( Uart_Dma&& other)
    : Uart_Base(other.ptr_huart_), ptr_dma_rx_(other.ptr_dma_rx_), ptr_dma_tx_(other.ptr_dma_tx_)
{
    other.ptr_huart_ = nullptr;
    other.ptr_dma_rx_ = nullptr;
    other.ptr_dma_tx_ = nullptr;
}

HAL_StatusTypeDef Uart_Dma::transmit( const uint8_t *pData, uint16_t Size) const
{
    if( this->ptr_huart_ )
        return HAL_UART_Transmit_DMA(this->ptr_huart_,pData,Size);
    return HAL_ERROR;
}

HAL_StatusTypeDef Uart_Dma::receive( uint8_t *pData, uint16_t Size) const
{
    if( this->ptr_huart_ )
        return HAL_UART_Receive_DMA(this->ptr_huart_, pData, Size);
    return HAL_ERROR;
}

HAL_StatusTypeDef Uart_Dma::receive_toIdle( uint8_t *pData, uint16_t Size, bool half_trans) const
{
    if( this->ptr_huart_ )
    {
        HAL_StatusTypeDef ret = HAL_OK;
        ret = HAL_UARTEx_ReceiveToIdle_DMA(this->ptr_huart_, pData, Size);
        if( ( this->ptr_dma_rx_ != nullptr ) && ( !half_trans ) )
            __HAL_DMA_DISABLE_IT( this->ptr_dma_rx_, DMA_IT_HT);    //  关闭DMA过半传输中断
        return ret;
    }
    return HAL_ERROR;
}

HAL_StatusTypeDef Uart_Dma::printf(const char* format, ...) const
{
    if( this->ptr_huart_ )
    {
        char tmp_string[Uart_Base::kPrintBuffLen] = {0};
        va_list arg;
        va_start( arg, format);
        vsprintf( tmp_string, format, arg);
        va_end(arg);
        return this->transmit( (uint8_t*)tmp_string, strlen(tmp_string));
    }
    return HAL_ERROR;
}

/* ****************************dma**************************** */



/*  通用串口 */

Uart_General::Uart_General(UART_HandleTypeDef* ptr_huart, DMA_HandleTypeDef* ptr_dma_rx, DMA_HandleTypeDef* ptr_dma_tx)
    : ptr_huart_(ptr_huart), ptr_dma_rx_(ptr_dma_rx), ptr_dma_tx_(ptr_dma_tx)
{}

Uart_General::Uart_General(const Uart_General& other)
    : ptr_huart_(other.ptr_huart_), ptr_dma_rx_(other.ptr_dma_rx_), ptr_dma_tx_(other.ptr_dma_tx_)
{}

Uart_General::Uart_General( Uart_General&& other)
    : ptr_huart_(other.ptr_huart_), ptr_dma_rx_(other.ptr_dma_rx_), ptr_dma_tx_(other.ptr_dma_tx_)
{
    other.ptr_huart_ = nullptr;
    other.ptr_dma_rx_ = nullptr;
    other.ptr_dma_tx_ = nullptr;
}

UART_HandleTypeDef* Uart_General::handle(void) const
{
    return this->ptr_huart_;
}

HAL_StatusTypeDef Uart_General::receive( uint8_t *pData,
        uint16_t Size, uint32_t Timeout) const
{
    if( this->ptr_huart_ )
        return HAL_UART_Receive(this->ptr_huart_, pData, Size, Timeout);
    return HAL_ERROR;
}

HAL_StatusTypeDef Uart_General::transmit( const uint8_t *pData,
        uint16_t Size, uint32_t Timeout) const
{
    if( this->ptr_huart_ )
        return HAL_UART_Transmit(this->ptr_huart_,pData,Size,Timeout);
    return HAL_ERROR;
}

HAL_StatusTypeDef Uart_General::receive_it( uint8_t *pData, uint16_t Size) const
{
    if( this->ptr_huart_ )
        return HAL_UART_Receive_IT(this->ptr_huart_, pData, Size);
    return HAL_ERROR;
}

HAL_StatusTypeDef Uart_General::transmit_it( const uint8_t *pData, uint16_t Size) const
{
    if( this->ptr_huart_ )
        return HAL_UART_Transmit_IT(this->ptr_huart_,pData,Size);
    return HAL_ERROR;
}

HAL_StatusTypeDef Uart_General::receive_dma( uint8_t *pData, uint16_t Size) const
{
    if( this->ptr_huart_ )
        return HAL_UART_Receive_DMA(this->ptr_huart_, pData, Size);
    return HAL_ERROR;
}

HAL_StatusTypeDef Uart_General::transmit_dma( const uint8_t *pData, uint16_t Size) const
{
    if( this->ptr_huart_ )
        return HAL_UART_Transmit_DMA(this->ptr_huart_,pData,Size);
    return HAL_ERROR;
}

HAL_StatusTypeDef Uart_General::receive_toIdle( uint8_t *pData,
        uint16_t Size, uint16_t* RxLen, uint32_t Timeout) const
{
    if( this->ptr_huart_ )
        return HAL_UARTEx_ReceiveToIdle(this->ptr_huart_, pData, Size, RxLen, Timeout);
    return HAL_ERROR;
}

HAL_StatusTypeDef Uart_General::receive_toIdle_it( uint8_t *pData, uint16_t Size) const
{
    if( this->ptr_huart_ )
        return HAL_UARTEx_ReceiveToIdle_IT(this->ptr_huart_, pData, Size);
    return HAL_ERROR;
}

HAL_StatusTypeDef Uart_General::receive_toIdle_dma( uint8_t *pData, uint16_t Size, bool half_trans) const
{
    if( this->ptr_huart_ )
    {
        HAL_StatusTypeDef ret = HAL_OK;
        ret = HAL_UARTEx_ReceiveToIdle_DMA(this->ptr_huart_, pData, Size);
        if( ( this->ptr_dma_rx_ != nullptr ) && ( !half_trans ) )
            __HAL_DMA_DISABLE_IT( this->ptr_dma_rx_, DMA_IT_HT);    //  关闭DMA过半传输中断
        return ret;
    }
    return HAL_ERROR;
}

HAL_StatusTypeDef Uart_General::printf(const char* format, ...) const
{
    if( this->ptr_huart_ )
    {
        char tmp_string[Uart_General::kPrintBuffLen] = {0};
        va_list arg;
        va_start( arg, format);
        vsprintf( tmp_string, format, arg);
        va_end(arg);
        return this->transmit( (uint8_t*)tmp_string, strlen(tmp_string));
    }
    return HAL_ERROR;
}

HAL_StatusTypeDef Uart_General::printf_it(const char* format, ...) const
{
    if( this->ptr_huart_ )
    {
        char tmp_string[Uart_General::kPrintBuffLen] = {0};
        va_list arg;
        va_start( arg, format);
        vsprintf( tmp_string, format, arg);
        va_end(arg);
        return this->transmit_it( (uint8_t*)tmp_string, strlen(tmp_string));
    }
    return HAL_ERROR;
}

HAL_StatusTypeDef Uart_General::printf_dma(const char* format, ...) const
{
    if( this->ptr_huart_ )
    {
        char tmp_string[Uart_General::kPrintBuffLen] = {0};
        va_list arg;
        va_start( arg, format);
        vsprintf( tmp_string, format, arg);
        va_end(arg);
        return this->transmit_dma( (uint8_t*)tmp_string, strlen(tmp_string));
    }
    return HAL_ERROR;
}

/**/

}
