#include "main.h"
#include "../../inc/protocols/simple_frame_parser.hpp"
#include "../../inc/utils/buffer_receiver.hpp"

namespace cya::halcpp::protocol
{

Simple_Frame_Parser::Simple_Frame_Parser( utils::Buffer_Receiver* rx_buffer )
    : Protocol_Parser(rx_buffer)
{}

bool Simple_Frame_Parser::pack_data(uint8_t* packet, uint8_t* data,
        uint16_t data_size,uint8_t packet_id)
{
    uint8_t sum = 0;

    packet[0] = packet_id;
    sum += packet[0];

    packet[1] = data_size + 3;
    if( packet[1] > 256 )
        return false;
    sum += packet[1];

    for( int i = 2 ; i < packet[1] - 1 ; ++i)
    {
        packet[i] = data[ i - 2 ];
        sum += packet[i];
    }

    packet[ packet[1] - 1 ] = sum;

    return true;
}

int16_t Simple_Frame_Parser::unpack_data(uint8_t* packet, uint8_t* data ,uint8_t packet_id)
{
    if( packet_id != packet[0] )
        return Simple_Frame_Parser::ParseState::HEAD_ERR;

    uint16_t packet_size = packet[1];

    if( packet_size < Simple_Frame_Parser::kCommandMinLength )
            return Simple_Frame_Parser::ParseState::SIZE_ERR;
    if( packet_size != packet[1] )
        return Simple_Frame_Parser::ParseState::SIZE_ERR;


    uint8_t sum = 0;
    sum += packet[0];
    sum += packet[1];
    for( int i = 2 ; i < ( packet_size - 1 ) ; ++i )
    {
        data[i-2] = packet[i];
        sum += packet[i];
    }
    if( sum != packet[packet_size - 1] )
        return Simple_Frame_Parser::ParseState::CHECK_SUM_ERR;

    return packet[1] - 3;
}

uint16_t Simple_Frame_Parser::get_command( uint8_t* data ,uint8_t packet_id)
{
    int16_t ret = 0;
    uint16_t packet_size = 0;
    uint16_t read_size = 0;
    uint8_t packet[256] = {0}; //  以后改为动态数组
    packet_size = this->rx_buffer_->read(packet);
    if( packet_size < Simple_Frame_Parser::kCommandMinLength )
        return 0;

    while( 1 )
    {
        ret = Simple_Frame_Parser::unpack_data(packet+read_size, data, packet_id);
        if( ret == Simple_Frame_Parser::ParseState::SIZE_ERR )
        {
            this->rx_buffer_->clear(read_size);
            return 0;
        }
        else if( ret == Simple_Frame_Parser::ParseState::HEAD_ERR ||
                ret == Simple_Frame_Parser::ParseState::CHECK_SUM_ERR )
        {
            ++read_size;
            continue;
        } else{
            return ret;
        }
    }
}

}
