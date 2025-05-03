#pragma once

#include "main.h"

namespace cya::halcpp::utils{

class Buffer_Receiver{
protected:
    uint8_t* rx_buffer_; //  缓冲区
    uint16_t capacity_;  //  容量( 缓冲区实际大小，字节为单位 )
public:
    //  写入数据
    virtual bool write(uint8_t* data, uint16_t size) = 0;
    //  读出数据，不指定 size 默认全读( 读取数据不等于删除数据 )
    virtual uint16_t read(uint8_t* data, uint16_t size = 0) = 0;
    //  删除数据
    virtual uint16_t clear(uint16_t size ) = 0;
    //  获取缓冲区当前有多少字节数据
    virtual uint16_t length(void) = 0;
    //  获取缓冲区剩余空位
    virtual uint16_t remain(void) = 0;
};

}
