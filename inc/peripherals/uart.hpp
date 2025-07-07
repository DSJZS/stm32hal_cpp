#pragma once

#include "main.h"

namespace cya::peripheral{

class Uart_Base{
protected:
    UART_HandleTypeDef* ptr_huart_;
    static constexpr uint8_t kPrintBuffLen = 255;

public:
    Uart_Base(UART_HandleTypeDef* ptr_huart);

    UART_HandleTypeDef* handle(void) const;
};

class Uart_Block : public Uart_Base{
public:
    Uart_Block( UART_HandleTypeDef* ptr_huart );
    Uart_Block( const Uart_Block& other );
    Uart_Block( Uart_Block&& other );

    HAL_StatusTypeDef transmit( const uint8_t *pData,
            uint16_t Size, uint32_t Timeout = HAL_MAX_DELAY) const;
    HAL_StatusTypeDef receive( uint8_t *pData,
                    uint16_t Size, uint32_t Timeout = HAL_MAX_DELAY) const;
    HAL_StatusTypeDef receive_toIdle( uint8_t *pData,
                        uint16_t Size, uint16_t *RxLen, uint32_t Timeout = HAL_MAX_DELAY) const;
    HAL_StatusTypeDef printf(const char* format, ...) const;
};

class Uart_It : public Uart_Base{
public:
    Uart_It( UART_HandleTypeDef* ptr_huart );
    Uart_It( const Uart_It& other );
    Uart_It( Uart_It&& other );

    HAL_StatusTypeDef transmit( const uint8_t *pData, uint16_t Size) const;
    HAL_StatusTypeDef receive( uint8_t *pData, uint16_t Size) const;
    HAL_StatusTypeDef receive_toIdle( uint8_t *pData, uint16_t Size) const;
    HAL_StatusTypeDef printf(const char* format, ...) const;
};

class Uart_Dma : public Uart_Base{
private:
    DMA_HandleTypeDef* ptr_dma_rx_;
    DMA_HandleTypeDef* ptr_dma_tx_;
public:
    Uart_Dma(UART_HandleTypeDef* ptr_huart, DMA_HandleTypeDef* ptr_dma_rx = nullptr, DMA_HandleTypeDef* ptr_dma_tx = nullptr);
    Uart_Dma( const Uart_Dma& other );
    Uart_Dma( Uart_Dma&& other );

    HAL_StatusTypeDef transmit( const uint8_t *pData, uint16_t Size) const;
    HAL_StatusTypeDef receive( uint8_t *pData, uint16_t Size) const;
    HAL_StatusTypeDef receive_toIdle( uint8_t *pData, uint16_t Size, bool half_trans = false) const;
    HAL_StatusTypeDef printf(const char* format, ...) const;
};

/*  通用串口 */

class Uart_General{
private:
    UART_HandleTypeDef* ptr_huart_;
    DMA_HandleTypeDef* ptr_dma_rx_;
    DMA_HandleTypeDef* ptr_dma_tx_;

    static constexpr uint8_t kPrintBuffLen = 255;
public:
    Uart_General(UART_HandleTypeDef* ptr_huart, DMA_HandleTypeDef* ptr_dma_rx = nullptr, DMA_HandleTypeDef* ptr_dma_tx = nullptr);
    Uart_General(const Uart_General& other);
    Uart_General( Uart_General&& other);

    UART_HandleTypeDef* handle(void) const;

    HAL_StatusTypeDef transmit( const uint8_t *pData,
            uint16_t Size, uint32_t Timeout = HAL_MAX_DELAY) const;

    HAL_StatusTypeDef transmit_it( const uint8_t *pData, uint16_t Size) const;

    HAL_StatusTypeDef transmit_dma( const uint8_t *pData, uint16_t Size) const;

    HAL_StatusTypeDef receive( uint8_t *pData,
                    uint16_t Size, uint32_t Timeout = HAL_MAX_DELAY) const;

    HAL_StatusTypeDef receive_it( uint8_t *pData, uint16_t Size) const;

    HAL_StatusTypeDef receive_dma( uint8_t *pData, uint16_t Size) const;

    HAL_StatusTypeDef receive_toIdle( uint8_t *pData,
                        uint16_t Size, uint16_t *RxLen, uint32_t Timeout = HAL_MAX_DELAY) const;

    HAL_StatusTypeDef receive_toIdle_it( uint8_t *pData, uint16_t Size) const;

    HAL_StatusTypeDef receive_toIdle_dma( uint8_t *pData, uint16_t Size, bool half_trans = false) const;

    HAL_StatusTypeDef printf(const char* format, ...) const;

    HAL_StatusTypeDef printf_it(const char* format, ...) const;

    HAL_StatusTypeDef printf_dma(const char* format, ...) const;
};

/**/

}
