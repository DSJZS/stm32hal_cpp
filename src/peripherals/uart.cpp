#include "main.h"
#include "../../inc/peripherals/uart.hpp"
#include <stdio.h>
#include <stdarg.h>
#include <cstring>

namespace cya::hal::peripheral::uart{

/* ***************************block*************************** */

Base::Base(UART_HandleTypeDef* ptr_huart)
    : ptr_huart_(ptr_huart)
{}

UART_HandleTypeDef* Base::handle(void) const
{
    return this->ptr_huart_;
}

Block::Block(UART_HandleTypeDef* ptr_huart)
    : Base(ptr_huart)
{}

Block::Block( const Block& other )
    : Base(other.ptr_huart_)
{}

Block::Block( Block&& other)
    : Base(other.ptr_huart_)
{
    other.ptr_huart_ = nullptr;
}

HAL_StatusTypeDef Block::transmit( const uint8_t *pData, uint16_t Size, uint32_t Timeout) const
{
    if( this->ptr_huart_ )
        return HAL_UART_Transmit(this->ptr_huart_,pData,Size,Timeout);
    return HAL_ERROR;
}

HAL_StatusTypeDef Block::receive( uint8_t *pData, uint16_t Size, uint32_t Timeout) const
{
    if( this->ptr_huart_ )
        return HAL_UART_Receive(this->ptr_huart_, pData, Size, Timeout);
    return HAL_ERROR;
}

HAL_StatusTypeDef Block::receive_toIdle( uint8_t *pData, uint16_t Size, uint16_t *RxLen, uint32_t Timeout) const
{
    if( this->ptr_huart_ )
        return HAL_UARTEx_ReceiveToIdle(this->ptr_huart_, pData, Size, RxLen, Timeout);
    return HAL_ERROR;
}

HAL_StatusTypeDef Block::printf(const char* format, ...) const
{
    if( this->ptr_huart_ )
    {
        char tmp_string[Base::kPrintBuffLen] = {0};
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

It::It(UART_HandleTypeDef* ptr_huart)
    : Base(ptr_huart)
{}

It::It( const It& other )
    : Base(other.ptr_huart_)
{}

It::It( It&& other)
    : Base(other.ptr_huart_)
{
    other.ptr_huart_ = nullptr;
}

HAL_StatusTypeDef It::transmit( const uint8_t *pData, uint16_t Size) const
{
    if( this->ptr_huart_ )
        return HAL_UART_Transmit_IT(this->ptr_huart_,pData,Size);
    return HAL_ERROR;
}

HAL_StatusTypeDef It::receive( uint8_t *pData, uint16_t Size) const
{
    if( this->ptr_huart_ )
        return HAL_UART_Receive_IT(this->ptr_huart_, pData, Size);
    return HAL_ERROR;
}

HAL_StatusTypeDef It::receive_toIdle( uint8_t *pData, uint16_t Size) const
{
    if( this->ptr_huart_ )
        return HAL_UARTEx_ReceiveToIdle_IT(this->ptr_huart_, pData, Size);
    return HAL_ERROR;
}

HAL_StatusTypeDef It::printf(const char* format, ...) const
{
    if( this->ptr_huart_ )
    {
        char tmp_string[Base::kPrintBuffLen] = {0};
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

Dma::Dma(UART_HandleTypeDef* ptr_huart)
    : Base(ptr_huart)
{}

Dma::Dma( const Dma& other )
    : Base(other.ptr_huart_)
{}

Dma::Dma( Dma&& other)
    : Base(other.ptr_huart_)
{
    other.ptr_huart_ = nullptr;
}

HAL_StatusTypeDef Dma::transmit( const uint8_t *pData, uint16_t Size) const
{
    if( this->ptr_huart_ )
        return HAL_UART_Transmit_DMA(this->ptr_huart_,pData,Size);
    return HAL_ERROR;
}

HAL_StatusTypeDef Dma::receive( uint8_t *pData, uint16_t Size) const
{
    if( this->ptr_huart_ )
        return HAL_UART_Receive_DMA(this->ptr_huart_, pData, Size);
    return HAL_ERROR;
}

HAL_StatusTypeDef Dma::receive_toIdle( uint8_t *pData, uint16_t Size) const
{
    if( this->ptr_huart_ )
    {
        HAL_StatusTypeDef ret = HAL_OK;
        ret = HAL_UARTEx_ReceiveToIdle_DMA(this->ptr_huart_, pData, Size);
        return ret;
    }
    return HAL_ERROR;
}

HAL_StatusTypeDef Dma::printf(const char* format, ...) const
{
    if( this->ptr_huart_ )
    {
        char tmp_string[Base::kPrintBuffLen] = {0};
        va_list arg;
        va_start( arg, format);
        vsprintf( tmp_string, format, arg);
        va_end(arg);
        return this->transmit( (uint8_t*)tmp_string, strlen(tmp_string));
    }
    return HAL_ERROR;
}

/* ****************************dma**************************** */



/* **************************General************************** */

General::General(UART_HandleTypeDef* ptr_huart)
    : Base(ptr_huart)
{}

General::General(const General& other)
    : Base(other.ptr_huart_)
{}

General::General( General&& other)
    : Base(other.ptr_huart_)
{
    other.ptr_huart_ = nullptr;
}

HAL_StatusTypeDef General::receive( uint8_t *pData,
        uint16_t Size, uint32_t Timeout) const
{
    if( this->ptr_huart_ )
        return HAL_UART_Receive(this->ptr_huart_, pData, Size, Timeout);
    return HAL_ERROR;
}

HAL_StatusTypeDef General::transmit( const uint8_t *pData,
        uint16_t Size, uint32_t Timeout) const
{
    if( this->ptr_huart_ )
        return HAL_UART_Transmit(this->ptr_huart_,pData,Size,Timeout);
    return HAL_ERROR;
}

HAL_StatusTypeDef General::receive_it( uint8_t *pData, uint16_t Size) const
{
    if( this->ptr_huart_ )
        return HAL_UART_Receive_IT(this->ptr_huart_, pData, Size);
    return HAL_ERROR;
}

HAL_StatusTypeDef General::transmit_it( const uint8_t *pData, uint16_t Size) const
{
    if( this->ptr_huart_ )
        return HAL_UART_Transmit_IT(this->ptr_huart_,pData,Size);
    return HAL_ERROR;
}

HAL_StatusTypeDef General::receive_dma( uint8_t *pData, uint16_t Size) const
{
    if( this->ptr_huart_ )
        return HAL_UART_Receive_DMA(this->ptr_huart_, pData, Size);
    return HAL_ERROR;
}

HAL_StatusTypeDef General::transmit_dma( const uint8_t *pData, uint16_t Size) const
{
    if( this->ptr_huart_ )
        return HAL_UART_Transmit_DMA(this->ptr_huart_,pData,Size);
    return HAL_ERROR;
}

HAL_StatusTypeDef General::receive_toIdle( uint8_t *pData,
        uint16_t Size, uint16_t* RxLen, uint32_t Timeout) const
{
    if( this->ptr_huart_ )
        return HAL_UARTEx_ReceiveToIdle(this->ptr_huart_, pData, Size, RxLen, Timeout);
    return HAL_ERROR;
}

HAL_StatusTypeDef General::receive_toIdle_it( uint8_t *pData, uint16_t Size) const
{
    if( this->ptr_huart_ )
        return HAL_UARTEx_ReceiveToIdle_IT(this->ptr_huart_, pData, Size);
    return HAL_ERROR;
}

HAL_StatusTypeDef General::receive_toIdle_dma( uint8_t *pData, uint16_t Size) const
{
    if( this->ptr_huart_ )
    {
        HAL_StatusTypeDef ret = HAL_OK;
        ret = HAL_UARTEx_ReceiveToIdle_DMA(this->ptr_huart_, pData, Size);
        return ret;
    }
    return HAL_ERROR;
}

HAL_StatusTypeDef General::printf(const char* format, ...) const
{
    if( this->ptr_huart_ )
    {
        char tmp_string[Base::kPrintBuffLen] = {0};
        va_list arg;
        va_start( arg, format);
        vsprintf( tmp_string, format, arg);
        va_end(arg);
        return this->transmit( (uint8_t*)tmp_string, strlen(tmp_string));
    }
    return HAL_ERROR;
}

HAL_StatusTypeDef General::printf_it(const char* format, ...) const
{
    if( this->ptr_huart_ )
    {
        char tmp_string[Base::kPrintBuffLen] = {0};
        va_list arg;
        va_start( arg, format);
        vsprintf( tmp_string, format, arg);
        va_end(arg);
        return this->transmit_it( (uint8_t*)tmp_string, strlen(tmp_string));
    }
    return HAL_ERROR;
}

HAL_StatusTypeDef General::printf_dma(const char* format, ...) const
{
    if( this->ptr_huart_ )
    {
        char tmp_string[Base::kPrintBuffLen] = {0};
        va_list arg;
        va_start( arg, format);
        vsprintf( tmp_string, format, arg);
        va_end(arg);
        return this->transmit_dma( (uint8_t*)tmp_string, strlen(tmp_string));
    }
    return HAL_ERROR;
}

/* **************************General************************** */

}
