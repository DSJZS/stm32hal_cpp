#pragma once

#include "main.h"
#include "protocol_parser.hpp"
#include "../utils/buffer_receiver.hpp"

namespace cya::halcpp::protocol
{

typedef class Simple_Frame_Parser : public Protocol_Parser{
private:
    enum ParseState{
        HEAD_ERR = -3,
        SIZE_ERR = -2,
        CHECK_SUM_ERR = -1
    };
    constexpr static uint16_t kCommandMinLength = 4;
public:
    Simple_Frame_Parser( utils::Buffer_Receiver* rx_buffer );
    uint16_t get_command( uint8_t* data ,uint8_t packet_id = 0xAA);
    static bool pack_data(uint8_t* packet, uint8_t* data,
            uint16_t size, uint8_t packet_id = 0xAA);
    static int16_t unpack_data(uint8_t* packet, uint8_t* data ,uint8_t packet_id = 0xAA);
}Simple_Frame;


}
