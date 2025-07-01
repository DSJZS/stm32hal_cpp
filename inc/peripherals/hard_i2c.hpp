#pragma once

#include "../interfaces/i2c_interface.hpp"
#include <stdint.h>

namespace cya::peripheral{

class Hard_I2C : public interface::I2C_Interface{
private:
    I2C_HandleTypeDef *hi2c_;
public:
    Hard_I2C( I2C_HandleTypeDef *hi2c );
    Hard_I2C( const Hard_I2C& other);
    Hard_I2C( Hard_I2C&& other);
    
    virtual void init(void) override;
    virtual int write( uint8_t dev_addr, uint8_t reg_addr,
            uint8_t data_len, uint8_t const* data_buf) override;
    virtual int read( uint8_t dev_addr, uint8_t reg_addr,
            uint8_t data_len, uint8_t* data_buf) override;
};

}