#include "main.h"
#include "../../inc/protocols/soft_i2c.hpp"

namespace cya::hal::protocol{

Soft_I2C::Soft_I2C( const peripheral::gpio::Pin& sda, const peripheral::gpio::Pin& scl,
        uint8_t level_trans_interval, uint8_t number_of_retry )
    : sda_(sda), scl_(scl),
      level_trans_interval_(level_trans_interval), number_of_retry_(number_of_retry)
{
    this->init();
}

void Soft_I2C::init(void)
{
    this->sda_.set();
    this->scl_.set();
}

void Soft_I2C::soft_delay(uint32_t dly)
{
    while(dly--)
        __NOP();
}

void Soft_I2C::soft_nop(void)
{
    // dly = 28, ≈ 500ns(168MHZ)
    // 主要为了满足I2C的最短通讯时间限制
    this->soft_delay( this->level_trans_interval_ );
}

uint8_t Soft_I2C::send_start(void)
{
    this->sda_.set();
    this->soft_nop();

    this->scl_.set();
    this->soft_nop();

    if( !( this->sda_.read() ))
        return I2C_STATE_::I2C_BUS_BUSY_;

    this->sda_.reset();
    this->soft_nop();

    this->scl_.reset();
    this->soft_nop();

    if( this->sda_.read() )
        return I2C_STATE_::I2C_BUS_ERROR_;

    return I2C_STATE_::I2C_BUS_READY_;
}

void Soft_I2C::send_stop(void)
{
    this->sda_.reset();
    this->soft_nop();

    this->scl_.set();
    this->soft_nop();

    this->sda_.set();
    this->soft_nop();
}

void Soft_I2C::send_ack(void)
{
    this->sda_.reset();
    this->soft_nop();

    this->scl_.set();
    this->soft_nop();

    this->scl_.reset();
    this->soft_nop();
}

void Soft_I2C::send_nAck(void)
{

    this->sda_.set();
    this->soft_nop();

    this->scl_.set();
    this->soft_nop();

    this->scl_.reset();
    this->soft_nop();
}

uint8_t Soft_I2C::wait_ack(void)
{
    uint8_t ucErrTime = 0;

    this->sda_.set();
    this->soft_nop();

    this->scl_.set();
    this->soft_nop();

    while( this->sda_.read() )
    {
        ucErrTime++;
        if( ucErrTime > 250 )   //  ucErrTime 最大比较值为 254 ，此处 250 表示尽可能的等待
        {
            this->send_stop();
            return I2C_STATE_::I2C_BUS_ERROR_;
        }
    }

    this->scl_.reset();
    return 0x00;
}

uint8_t Soft_I2C::send_byte(uint8_t data)
{
    this->scl_.reset();

    for( int i = 0 ; i < 8 ; ++i )
    {
        if( data & 0x80 )
            this->sda_.set();
        else
            this->sda_.reset();
        data <<= 1;
        this->soft_nop();

        this->scl_.set();
        this->soft_nop();
        this->scl_.reset();
        this->soft_nop();
    }

    return this->wait_ack();
}

uint8_t Soft_I2C::receive_byte_withNAck(void)
{
    uint8_t data = 0;

    this->sda_.set();
    this->scl_.reset();

    for( int i = 0 ; i < 8 ; ++i )
    {
        this->scl_.set();
        this->soft_nop();
        data <<= 1;

        if( this->sda_.read() )
            data |= 0x01;

        this->scl_.reset();
        this->soft_nop();
    }
    this->send_nAck();
    return data;
}

uint8_t Soft_I2C::receive_byte_withAck(void)
{
    uint8_t data = 0;

    this->sda_.set();
    this->scl_.reset();

    for( int i = 0 ; i < 8 ; ++i )
    {
        this->scl_.set();
        this->soft_nop();
        data <<= 1;

        if( this->sda_.read() )
            data |= 0x01;

        this->scl_.reset();
        this->soft_nop();
    }
    this->send_ack();
    return data;
}

uint8_t Soft_I2C::soft_write( uint8_t dev_addr, uint8_t reg_addr,
        uint8_t data_len, uint8_t const* data_buf)
{
    uint8_t result = 0;

    this->send_start();
    result = this->send_byte( dev_addr << 1 | I2C_TRANS_DIR_::I2C_DIR_TRANSMITTER_);
    if( result != 0 )
        return result;

    result = this->send_byte( reg_addr );
    if( result != 0 )
        return result;

    for ( uint8_t i = 0 ; i < data_len ; i++ )
    {
        result = this->send_byte( data_buf[i]);
        if (result != 0)
            return result;
    }
    this->send_stop();
    return 0x00;
}

uint8_t Soft_I2C::soft_read( uint8_t dev_addr, uint8_t reg_addr,
            uint8_t data_len, uint8_t* data_buf)
{
    uint8_t result = 0;

    this->send_start();
    result = this->send_byte( dev_addr << 1 | I2C_TRANS_DIR_::I2C_DIR_TRANSMITTER_);
    if( result != 0 )
        return result;

    result = this->send_byte( reg_addr );
    if( result != 0 )
        return result;

    this->send_start();
    result = this->send_byte( dev_addr << 1 | I2C_TRANS_DIR_::I2C_DIR_RECEIVER_);
    if( result != 0 )
        return result;

    while( data_len-- )
    {
        if( data_len == 1 )
            *data_buf = this->receive_byte_withNAck();
        else
            *data_buf = this->receive_byte_withAck();
        ++data_buf;
    }
    this->send_stop();
    return 0x00;
}

uint8_t Soft_I2C::write( uint8_t dev_addr, uint8_t reg_addr,
            uint8_t data_len, uint8_t const* data_buf)
{
    uint8_t retries = 0, ret = 0;
    retries = this->number_of_retry_;

    while( retries-- )
    {
        ret = this->soft_write(dev_addr, reg_addr, data_len, data_buf);
        if( !ret )
            break;
    }
    return ret;
}

uint8_t Soft_I2C::read( uint8_t dev_addr, uint8_t reg_addr,
            uint8_t data_len, uint8_t * data_buf)
{
    uint8_t retries = 0, ret = 0;
    retries = this->number_of_retry_;

    while( retries-- )
    {
        ret = this->soft_read(dev_addr, reg_addr, data_len, data_buf);
        if( !ret )
            break;
    }
    return ret;
}

}

