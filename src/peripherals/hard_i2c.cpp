#include "main.h"
#include "../../inc/peripherals/hard_i2c.hpp"

namespace cya::peripheral{

Hard_I2C::Hard_I2C( I2C_HandleTypeDef *hi2c )
    : hi2c_(hi2c)
{}

Hard_I2C::Hard_I2C( const Hard_I2C& other)
    : hi2c_(other.hi2c_)
{}

Hard_I2C::Hard_I2C( Hard_I2C&& other)
    : hi2c_(other.hi2c_)
{
    other.hi2c_ = nullptr;
}

void Hard_I2C::init(void)
{
    if( this->hi2c_ == nullptr )
        return;
}

int Hard_I2C::write( uint8_t dev_addr, uint8_t reg_addr,
    uint8_t data_len, uint8_t const* data_buf)
{
    if( this->hi2c_ == nullptr )
        return I2C_STATE_::I2C_BUS_ERROR_;
}
int Hard_I2C::read( uint8_t dev_addr, uint8_t reg_addr,
    uint8_t data_len, uint8_t* data_buf)
{
    if( this->hi2c_ == nullptr )
        return I2C_STATE_::I2C_BUS_ERROR_;
}

}
