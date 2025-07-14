#include "main.h"
#include "../../inc/peripherals/hard_i2c.hpp"

namespace cya::peripheral{

Hard_I2C::Hard_I2C( I2C_HandleTypeDef *hi2c )
    : ptr_hi2c_(ptr_hi2c)
{
    this->init();
}

Hard_I2C::Hard_I2C( const Hard_I2C& other)
    : ptr_hi2c_(other.ptr_hi2c_)
{}

Hard_I2C::Hard_I2C( Hard_I2C&& other)
    : ptr_hi2c_(other.ptr_hi2c_)
{
    other.ptr_hi2c_ = nullptr;
}

HAL_StatusTypeDef Hard_I2C::master_transmit( uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
    if( this->ptr_hi2c_ )
        HAL_I2C_Master_Transmit( this->ptr_hi2c_, DevAddress, pData, Size, Timeout);
    return HAL_ERROR;
}

HAL_StatusTypeDef Hard_I2C::master_receive( uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
    if( this->ptr_hi2c_ )
        HAL_I2C_Master_Receive( this->ptr_hi2c_, DevAddress, pData, Size, Timeout);
    return HAL_ERROR;
}

HAL_StatusTypeDef Hard_I2C::slave_transmit( uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
    if( this->ptr_hi2c_ )
        HAL_I2C_Slave_Transmit( this->ptr_hi2c_, pData, Size, Timeout);
    return HAL_ERROR;
}

HAL_StatusTypeDef Hard_I2C::slave_receive( uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
    if( this->ptr_hi2c_ )
        HAL_I2C_Slave_Receive( this->ptr_hi2c_, pData, Size, Timeout);
    return HAL_ERROR;
}

HAL_StatusTypeDef Hard_I2C::master_transmit_it( uint16_t DevAddress, uint8_t *pData, uint16_t Size)
{
    if( this->ptr_hi2c_ )
        HAL_I2C_Master_Transmit_IT( this->ptr_hi2c_, DevAddress, pData, Size);
    return HAL_ERROR;
}

HAL_StatusTypeDef Hard_I2C::master_receive_it( uint16_t DevAddress, uint8_t *pData, uint16_t Size)
{
    if( this->ptr_hi2c_ )
        HAL_I2C_Master_Receive_IT( this->ptr_hi2c_, DevAddress, pData, Size);
    return HAL_ERROR;
}

HAL_StatusTypeDef Hard_I2C::slave_transmit_it( uint8_t *pData, uint16_t Size)
{
    if( this->ptr_hi2c_ )
        HAL_I2C_Slave_Transmit_IT( this->ptr_hi2c_, pData, Size);
    return HAL_ERROR;
}

HAL_StatusTypeDef Hard_I2C::slave_receive_it( uint8_t *pData, uint16_t Size)
{
    if( this->ptr_hi2c_ )
        HAL_I2C_Slave_Receive_IT( this->ptr_hi2c_, pData, Size);
    return HAL_ERROR;
}

HAL_StatusTypeDef Hard_I2C::master_transmit_dma( uint16_t DevAddress, uint8_t *pData, uint16_t Size)
{
    if( this->ptr_hi2c_ )
        HAL_I2C_Master_Transmit_DMA( this->ptr_hi2c_, DevAddress, pData, Size);
    return HAL_ERROR;
}

HAL_StatusTypeDef Hard_I2C::master_receive_dma( uint16_t DevAddress, uint8_t *pData, uint16_t Size)
{
    if( this->ptr_hi2c_ )
        HAL_I2C_Master_Receive_DMA( this->ptr_hi2c_, DevAddress, pData, Size);
    return HAL_ERROR;
}

HAL_StatusTypeDef Hard_I2C::slave_transmit_dma( uint8_t *pData, uint16_t Size)
{
    if( this->ptr_hi2c_ )
        HAL_I2C_Slave_Receive_DMA( this->ptr_hi2c_, pData, Size);
    return HAL_ERROR;
}

HAL_StatusTypeDef Hard_I2C::slave_receive_dma( uint8_t *pData, uint16_t Size)
{
    if( this->ptr_hi2c_ )
        HAL_I2C_Slave_Receive_DMA( this->ptr_hi2c_, pData, Size);
    return HAL_ERROR;
}


void Hard_I2C::init(void)
{
    if( this->ptr_hi2c_ == nullptr )
        return;
}

uint8_t Hard_I2C::write( uint8_t dev_addr, uint8_t reg_addr,
    uint8_t data_len, uint8_t const* data_buf)
{
    if( this->ptr_hi2c_ == nullptr )
        return I2C_STATE_::I2C_BUS_ERROR_;
    HAL_I2C_Master_Transmit( this->ptr_hi2c_, dev_addr, data_buf, data_len, HAL_MAX_DELAY);
    return 0x00;
}

uint8_t Hard_I2C::read( uint8_t dev_addr, uint8_t reg_addr,
    uint8_t data_len, uint8_t* data_buf)
{
    if( this->ptr_hi2c_ == nullptr )
        return I2C_STATE_::I2C_BUS_ERROR_;
    HAL_I2C_Master_Receive( this->ptr_hi2c_, dev_addr, data_buf, data_len, HAL_MAX_DELAY);
    return 0x00;
}

}
