#pragma once

#include "../interfaces/i2c_interface.hpp"
#include <stdint.h>

namespace cya::stm32::peripheral{

class Hard_I2C : public interface::I2C_Interface{
private:
    I2C_HandleTypeDef* ptr_hi2c_;
public:
    Hard_I2C( I2C_HandleTypeDef* ptr_hi2c);
    Hard_I2C( const Hard_I2C& other);
    Hard_I2C( Hard_I2C&& other);

    HAL_StatusTypeDef master_transmit( uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout = HAL_MAX_DELAY);
    HAL_StatusTypeDef master_receive( uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout = HAL_MAX_DELAY);
    HAL_StatusTypeDef slave_transmit( uint8_t *pData, uint16_t Size, uint32_t Timeout = HAL_MAX_DELAY);
    HAL_StatusTypeDef slave_receive( uint8_t *pData, uint16_t Size, uint32_t Timeout = HAL_MAX_DELAY);
    HAL_StatusTypeDef mem_write( uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout = HAL_MAX_DELAY);
    HAL_StatusTypeDef mem_read( uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout = HAL_MAX_DELAY);

    HAL_StatusTypeDef master_transmit_it( uint16_t DevAddress, uint8_t *pData, uint16_t Size);
    HAL_StatusTypeDef master_receive_it( uint16_t DevAddress, uint8_t *pData, uint16_t Size);
    HAL_StatusTypeDef slave_transmit_it( uint8_t *pData, uint16_t Size);
    HAL_StatusTypeDef slave_receive_it( uint8_t *pData, uint16_t Size);
    HAL_StatusTypeDef mem_write_it( uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size);
    HAL_StatusTypeDef mem_read_it( uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size);

    HAL_StatusTypeDef master_transmit_dma( uint16_t DevAddress, uint8_t *pData, uint16_t Size);
    HAL_StatusTypeDef master_receive_dma( uint16_t DevAddress, uint8_t *pData, uint16_t Size);
    HAL_StatusTypeDef slave_transmit_dma( uint8_t *pData, uint16_t Size);
    HAL_StatusTypeDef slave_receive_dma( uint8_t *pData, uint16_t Size);
    HAL_StatusTypeDef mem_write_dma( uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size);
    HAL_StatusTypeDef mem_read_dma( uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size);

    //  dev_addr 为 7位设备地址
    HAL_StatusTypeDef write_block( uint8_t dev_addr, uint8_t reg_addr,uint8_t data_len, uint8_t const* data_buf, uint16_t mem_address_size = I2C_MEMADD_SIZE_8BIT);
    HAL_StatusTypeDef write_it( uint8_t dev_addr, uint8_t reg_addr,uint8_t data_len, uint8_t const* data_buf, uint16_t mem_address_size = I2C_MEMADD_SIZE_8BIT);
    HAL_StatusTypeDef write_dma( uint8_t dev_addr, uint8_t reg_addr,uint8_t data_len, uint8_t const* data_buf, uint16_t mem_address_size = I2C_MEMADD_SIZE_8BIT);
    HAL_StatusTypeDef read_block( uint8_t dev_addr, uint8_t reg_addr,uint8_t data_len, uint8_t* data_buf, uint16_t mem_address_size = I2C_MEMADD_SIZE_8BIT);
    HAL_StatusTypeDef read_it( uint8_t dev_addr, uint8_t reg_addr,uint8_t data_len, uint8_t* data_buf, uint16_t mem_address_size = I2C_MEMADD_SIZE_8BIT);
    HAL_StatusTypeDef read_dma( uint8_t dev_addr, uint8_t reg_addr,uint8_t data_len, uint8_t* data_buf, uint16_t mem_address_size = I2C_MEMADD_SIZE_8BIT);

    virtual void init(void) override;
    virtual uint8_t write( uint8_t dev_addr, uint8_t reg_addr,uint8_t data_len, uint8_t const* data_buf) override;
    virtual uint8_t read( uint8_t dev_addr, uint8_t reg_addr,uint8_t data_len, uint8_t* data_buf) override;
};

}