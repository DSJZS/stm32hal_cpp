#pragma once

#include "main.h"
#include "protocol_parser_base.hpp"
#include "../utils/buffer_receiver.hpp"

namespace cya::halcpp::protocol
{

typedef class Simple_Frame_Parser : public Protocol_Parser_Base{
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
    virtual bool get_command( Parser_IO* sfp_io) override;
    static bool pack_data(uint8_t* packet, uint8_t* data,
            uint16_t size, uint8_t packet_id = 0xAA);
    static int16_t unpack_data(uint8_t* packet, uint8_t* data ,uint8_t packet_id = 0xAA);
}Simple_Frame;


}
