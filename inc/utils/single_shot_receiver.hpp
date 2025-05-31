#pragma once

#include "main.h"
#include "buffer_receiver.hpp"

namespace cya::utils{

typedef class Low_Speed_Data_Rx : public Buffer_Receiver
{
public:
    uint16_t read_ptr_;
    uint16_t write_ptr_;
    void write_byte(uint8_t byte);
public:
    Low_Speed_Data_Rx( uint8_t* rx_buffer, uint16_t capacity);

    //  写入数据
    virtual bool write(uint8_t* data, uint16_t size) override;
    //  读出数据，不指定 size 默认全读( 读取数据不等于删除数据 )
    virtual uint16_t read(uint8_t* data, uint16_t size = 0) override;
    //  删除数据，不指定 size 默认全删
    virtual uint16_t clear(uint16_t size ) override;
    //  获取缓冲区当前有多少字节数据
    virtual uint16_t length(void) override;
    //  获取缓冲区剩余空位
    virtual uint16_t remain(void) override;
}Single_Shot_Receiver;

}
