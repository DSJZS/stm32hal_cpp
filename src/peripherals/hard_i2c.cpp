#include "main.h"
#include "../../inc/peripherals/hard_i2c.hpp"

namespace cya::peripheral{

Hard_I2C::Hard_I2C( I2C_HandleTypeDef *ptr_hi2c )
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

HAL_StatusTypeDef Hard_I2C::mem_write( uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
    if( this->ptr_hi2c_ )
        HAL_I2C_Mem_Write( this->ptr_hi2c_, DevAddress, MemAddress, MemAddSize, pData, Size, Timeout);
    return HAL_ERROR;
}

HAL_StatusTypeDef Hard_I2C::mem_read( uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
    if( this->ptr_hi2c_ )
        HAL_I2C_Mem_Read( this->ptr_hi2c_, DevAddress, MemAddress, MemAddSize, pData, Size, Timeout);
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

HAL_StatusTypeDef Hard_I2C::mem_write_it( uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size)
{
    if( this->ptr_hi2c_ )
        HAL_I2C_Mem_Write_IT( this->ptr_hi2c_, DevAddress, MemAddress, MemAddSize, pData, Size);
    return HAL_ERROR;
}

HAL_StatusTypeDef Hard_I2C::mem_read_it( uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size)
{
    if( this->ptr_hi2c_ )
        HAL_I2C_Mem_Read_IT( this->ptr_hi2c_, DevAddress, MemAddress, MemAddSize, pData, Size);
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

HAL_StatusTypeDef Hard_I2C::mem_write_dma( uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size)
{
    if( this->ptr_hi2c_ )
        HAL_I2C_Mem_Write_DMA( this->ptr_hi2c_, DevAddress, MemAddress, MemAddSize, pData, Size);
    return HAL_ERROR;
}

HAL_StatusTypeDef Hard_I2C::mem_read_dma( uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size)
{
    if( this->ptr_hi2c_ )
        HAL_I2C_Mem_Read_DMA( this->ptr_hi2c_, DevAddress, MemAddress, MemAddSize, pData, Size);
    return HAL_ERROR;
}

HAL_StatusTypeDef Hard_I2C::write_block( uint8_t dev_addr, uint8_t reg_addr,uint8_t data_len, uint8_t const* data_buf, uint16_t mem_address_size)
{
    return this->mem_write( dev_addr << 1, reg_addr, mem_address_size, (uint8_t*)data_buf, data_len);
}

HAL_StatusTypeDef Hard_I2C::write_it( uint8_t dev_addr, uint8_t reg_addr,uint8_t data_len, uint8_t const* data_buf, uint16_t mem_address_size)
{
    return this->mem_write_it( dev_addr << 1, reg_addr, mem_address_size, (uint8_t*)data_buf, data_len);
}

HAL_StatusTypeDef Hard_I2C::write_dma( uint8_t dev_addr, uint8_t reg_addr,uint8_t data_len, uint8_t const* data_buf, uint16_t mem_address_size)
{
    return this->mem_write_dma( dev_addr << 1, reg_addr, mem_address_size, (uint8_t*)data_buf, data_len);
}

HAL_StatusTypeDef Hard_I2C::read_block( uint8_t dev_addr, uint8_t reg_addr,uint8_t data_len, uint8_t* data_buf, uint16_t mem_address_size)
{
    return this->mem_read( dev_addr << 1, reg_addr, mem_address_size, data_buf, data_len);
}

HAL_StatusTypeDef Hard_I2C::read_it( uint8_t dev_addr, uint8_t reg_addr,uint8_t data_len, uint8_t* data_buf, uint16_t mem_address_size)
{
    return this->mem_read_it( dev_addr << 1, reg_addr, mem_address_size, data_buf, data_len);
}

HAL_StatusTypeDef Hard_I2C::read_dma( uint8_t dev_addr, uint8_t reg_addr,uint8_t data_len, uint8_t* data_buf, uint16_t mem_address_size)
{
    return this->mem_read_dma( dev_addr << 1, reg_addr, mem_address_size, data_buf, data_len);
}

void Hard_I2C::init(void)
{
    if( this->ptr_hi2c_ == nullptr )
        return;
}

uint8_t Hard_I2C::write( uint8_t dev_addr, uint8_t reg_addr, uint8_t data_len, uint8_t const* data_buf)
{
    if( this->ptr_hi2c_ == nullptr )
        return I2C_STATE_::I2C_BUS_ERROR_;
    HAL_StatusTypeDef ret = this->write_block( dev_addr, reg_addr, data_len, data_buf);
    if( ret != HAL_OK )
        return I2C_STATE_::I2C_BUS_ERROR_;
    return 0x00;
}

uint8_t Hard_I2C::read( uint8_t dev_addr, uint8_t reg_addr, uint8_t data_len, uint8_t* data_buf)
{
    if( this->ptr_hi2c_ == nullptr )
        return I2C_STATE_::I2C_BUS_ERROR_;
    HAL_StatusTypeDef ret = this->read_block( dev_addr, reg_addr, data_len, data_buf);
    if( ret != HAL_OK )
        return I2C_STATE_::I2C_BUS_ERROR_;
    return 0x00;
}

}
