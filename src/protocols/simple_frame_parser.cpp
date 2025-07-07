#include "main.h"
#include "../../inc/protocols/simple_frame_parser.hpp"
#include "../../inc/utils/buffer_receiver.hpp"

namespace cya::protocol
{

Simple_Frame_Parser::Simple_Frame_Parser( uint8_t packet_head )
    : packet_head_( packet_head )
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

uint16_t Simple_Frame_Parser::unpack_data(uint8_t* packet, uint8_t* data ,uint8_t packet_id)
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

void Simple_Frame_Parser::set_packet_head( uint8_t packet_head )
{
    this->packet_head_ = packet_head;
}

bool Simple_Frame_Parser::get_command( Parser_IO* sfp_io)
{
    int16_t ret = 0;
    uint16_t packet_size = 0;
    uint16_t read_size = 0;

    uint8_t packet[Simple_Frame_Parser::kParserBufferLength] = {0}; //  以后改为动态数组

    packet_size = sfp_io->rx_buffer->read(packet);

    if( packet_size < Simple_Frame_Parser::kCommandMinLength )
        return false;

    while( 1 )
    {
        ret = Simple_Frame_Parser::unpack_data(
                packet + read_size, sfp_io->o_data, this->packet_head_ );
        if( ret == Simple_Frame_Parser::ParseState::SIZE_ERR )
        {
            sfp_io->rx_buffer->clear(read_size);
            return false;
        }
        else if( ret == Simple_Frame_Parser::ParseState::HEAD_ERR ||
                ret == Simple_Frame_Parser::ParseState::CHECK_SUM_ERR )
        {
            ++read_size;
            continue;
        } else {
            sfp_io->o_data_size = ret;
            sfp_io->rx_buffer->clear(read_size + packet[read_size+1] );
            return true;
        }
    }
}

}
