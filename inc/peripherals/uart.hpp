#pragma once

#include "main.h"

namespace cya::halcpp::peripheral{

class Uart{
private:
    UART_HandleTypeDef* ptr_huart_;

    static constexpr uint8_t kPrintBuffLen = 255;
public:
    Uart(UART_HandleTypeDef* ptr_huart);

    Uart(const Uart& other_uart);

    UART_HandleTypeDef* get_ptr_huart(void) const;

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

    HAL_StatusTypeDef receive_toIdle_dma( uint8_t *pData, uint16_t Size,
            DMA_HandleTypeDef* ptr_hdma_usart_rx = NULL) const;

    HAL_StatusTypeDef printf(const char* format, ...) const;

    HAL_StatusTypeDef printf_it(const char* format, ...) const;

    HAL_StatusTypeDef printf_dma(const char* format, ...) const;
};

}
