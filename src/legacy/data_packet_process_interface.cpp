#include "../../inc/Legacy/data_packet_process_interface.hpp"
#include <cstring>

namespace cya::halcpp::legacy{

bool Data_Packet_Checksum::pack_data(uint8_t* packet, uint8_t* data, uint16_t data_size,
        uint8_t packet_id, uint32_t hParam,uint32_t lParam)
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

uint16_t Data_Packet_Checksum::unpack_data(uint8_t* packet, uint8_t* data, uint16_t data_size,
        uint8_t packet_id, uint32_t hParam,uint32_t lParam)
{
    if( packet_id != packet[0] )
        return 0;
    if( data_size != packet[1] )
        return 0;


    uint8_t sum = 0;
    sum += packet[0];
    sum += packet[1];
    for( int i = 2 ; i < ( data_size - 1 ) ; ++i )
    {
        data[i-2] = packet[i];
        sum += packet[i];
    }
    if( sum != packet[data_size - 1] )
        return 0;

    return packet[1] - 3;
}

bool Data_Packet_Firewater::pack_data(uint8_t* packet, uint8_t* data, uint16_t data_size,
        uint8_t packet_id, uint32_t hParam,uint32_t lParam)
{
    return true;
}

uint16_t Data_Packet_Firewater::unpack_data(uint8_t* packet, uint8_t* data, uint16_t data_size,
        uint8_t packet_id, uint32_t hParam,uint32_t lParam)
{
    return 0;
}

Data_Packet_Receiver::Data_Packet_Receiver(uint8_t head,uint8_t rear)
    : head_(head),rear_(rear),ptr_(0)
{
    memset(this->buffer_, 0,sizeof(this->buffer_));
}

void Data_Packet_Receiver::receive_byte(uint8_t byte)
{
    this->buffer_[this->ptr_++] = byte;
}

bool Data_Packet_Receiver::receive_data(uint8_t* data, uint16_t size)
{
    if( size == 0 )
        return false;
    if( data == NULL )
        return false;
    for( int i = 0 ; i < size ; ++i )
    {
        if( data[i] == this->head_ )
            this->clear_buffer();
        else if( data[i] == this->rear_ )
            return true;
        else
            this->receive_byte(data[i]);
    }
    return false;
}

uint8_t* Data_Packet_Receiver::get_buffer(uint8_t* ptr_size)
{
    if( ptr_size != NULL)
        *ptr_size = this->ptr_;
    return this->buffer_;
}

void Data_Packet_Receiver::clear_buffer(void)
{
    memset(this->buffer_, 0,sizeof(this->buffer_));
    this->ptr_ = 0;
}

}
