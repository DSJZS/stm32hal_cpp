#pragma once

#include "../interfaces/i2c_interface.hpp"
#include "../peripherals/gpio.hpp"

namespace cya::protocol{

class Soft_I2C : public interface::I2C_Interface{
private:
    peripheral::gpio::Pin sda_;
    peripheral::gpio::Pin scl_;
    
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
    Soft_I2C( const peripheral::gpio::Pin& sda, const peripheral::gpio::Pin& scl,
            uint8_t level_trans_interval = 28, uint8_t number_of_retry_ = 4);
    virtual void init(void) override;
    virtual int write( uint8_t dev_addr, uint8_t reg_addr,
            uint8_t data_len, uint8_t const* data_buf) override;
    virtual int read( uint8_t dev_addr, uint8_t reg_addr,
            uint8_t data_len, uint8_t* data_buf) override;
};

}
