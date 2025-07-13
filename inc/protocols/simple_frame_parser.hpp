#pragma once

#include "main.h"
#include "lwrb/lwrb.h"

namespace cya::protocol
{

/*  数据格式:
 *  单字节包头 + 单字节包长度 + 可变多字节数据 + 单字节校验和

 *  其中:
 *  单字节包头      - 可以为任意字符或者单字节数字
 *  单字节包长度    - 整个包有多少个字节
 *  可变多字节数据  - 实际数据
 *  单字节校验和    - 整个包包除了单字节校验和字节以外所有字节相加取第八位
 */
typedef class Simple_Frame_Parser{
private:
    enum ParseState{
        HEAD_ERR = -3,
        SIZE_ERR = -2,
        CHECK_SUM_ERR = -1
    };
    //  数据包最小长度
    constexpr static uint16_t kCommandMinLength = 4;
    //  数据包解析缓存区最大长度
    constexpr static uint16_t kParserBufferLength = 256;
    //  数据包包头指定
    uint8_t packet_head_;
public:
    Simple_Frame_Parser( uint8_t packet_head );
    void set_packet_head( uint8_t packet_head );

    bool get_command( lwrb_t* buff, uint8_t* data, uint16_t* bwritten);  //  环形队列缓存的实际最大长度应该小于等于 kParserBufferLength
    static bool pack_data(uint8_t* packet, uint8_t* data,uint16_t size, uint8_t packet_id);
    static uint16_t unpack_data(uint8_t* packet, uint8_t* data ,uint8_t packet_id);
}Simple_Frame;


}
