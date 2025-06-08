#pragma once

#include <stdint.h>

namespace cya::interface{

class I2C_Interface{
public:
    enum I2C_TRANS_DIR_{
        I2C_DIR_TRANSMITTER_ = 0x00,
        I2C_DIR_RECEIVER_ = 0x01
    };
    virtual void init(void) = 0;
    virtual int write( uint8_t dev_addr, uint8_t reg_addr,
        uint8_t data_len, uint8_t const* data_buf) = 0;
    virtual int read( uint8_t dev_addr, uint8_t reg_addr,
            uint8_t data_len, uint8_t* data_buf) = 0;
};

}
