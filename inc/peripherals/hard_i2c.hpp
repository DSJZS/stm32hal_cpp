#pragma once

#include "../interfaces/i2c_interface.hpp"
#include <stdint.h>

namespace cya::peripheral{

class Hard_I2C : public interface::I2C_Interface{
private:
    I2C_HandleTypeDef* ptr_hi2c_;
public:
    Hard_I2C( I2C_HandleTypeDef* ptr_hi2c);
    Hard_I2C( const Hard_I2C& other);
    Hard_I2C( Hard_I2C&& other);

    HAL_StatusTypeDef master_transmit( uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout = HAL_MAX_DELAY)
    HAL_StatusTypeDef master_receive( uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout = HAL_MAX_DELAY);
    HAL_StatusTypeDef slave_transmit( uint8_t *pData, uint16_t Size, uint32_t Timeout = HAL_MAX_DELAY);
    HAL_StatusTypeDef slave_receive( uint8_t *pData, uint16_t Size, uint32_t Timeout = HAL_MAX_DELAY);

    HAL_StatusTypeDef master_transmit_it( uint16_t DevAddress, uint8_t *pData, uint16_t Size);
    HAL_StatusTypeDef master_receive_it( uint16_t DevAddress, uint8_t *pData, uint16_t Size);
    HAL_StatusTypeDef slave_transmit_it( uint8_t *pData, uint16_t Size);
    HAL_StatusTypeDef slave_receive_it( uint8_t *pData, uint16_t Size);

    HAL_StatusTypeDef master_transmit_dma( uint16_t DevAddress, uint8_t *pData, uint16_t Size);
    HAL_StatusTypeDef master_receive_dma( uint16_t DevAddress, uint8_t *pData, uint16_t Size);
    HAL_StatusTypeDef slave_transmit_dma( uint8_t *pData, uint16_t Size);
    HAL_StatusTypeDef slave_receive_dma( uint8_t *pData, uint16_t Size);

    virtual void init(void) override;
    virtual uint8_t write( uint8_t dev_addr, uint8_t reg_addr,
            uint8_t data_len, uint8_t const* data_buf) override;
    virtual uint8_t read( uint8_t dev_addr, uint8_t reg_addr,
            uint8_t data_len, uint8_t* data_buf) override;
};

}