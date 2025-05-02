#pragma once

#include "main.h"
#include "i2c.hpp"
#include "../drivers/gpio.hpp"

namespace cya::halcpp::interface{

class Soft_I2C : public I2C{
private:
    enum I2C_STATE_{
        I2C_BUS_BUSY_ = 0,
        I2C_BUS_ERROR_,
        I2C_BUS_READY_
    };

    driver::gpio::Pin sda_;
    driver::gpio::Pin scl_;
    uint8_t level_trans_interval_;
    uint8_t number_of_retry_;
    void soft_delay(uint32_t dly);
    void soft_nop(void);
    uint8_t send_start(void);
    void send_stop(void);
    void send_ack(void);
    void send_nAck(void);
    uint8_t wait_ack(void);
    uint8_t send_byte(uint8_t data);
    uint8_t receive_byte_withNAck(void);
    uint8_t receive_byte_withAck(void);
    uint8_t soft_write( uint8_t dev_addr, uint8_t reg_addr,
            uint8_t data_len, uint8_t const* data_buf);
    uint8_t soft_read( uint8_t dev_addr, uint8_t reg_addr,
                uint8_t data_len, uint8_t* data_buf);
public:
    Soft_I2C( const driver::gpio::Pin& sda, const driver::gpio::Pin& scl,
            uint8_t level_trans_interval = 28, uint8_t number_of_retry_ = 4);
    virtual void init(void) override;
    virtual int write( uint8_t dev_addr, uint8_t reg_addr,
            uint8_t data_len, uint8_t const* data_buf) override;
    virtual int read( uint8_t dev_addr, uint8_t reg_addr,
            uint8_t data_len, uint8_t* data_buf) override;
};

}
