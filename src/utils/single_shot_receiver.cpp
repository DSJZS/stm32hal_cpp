#include "main.h"

#include "../../inc/utils/single_shot_receiver.hpp"
#include <cstring>

namespace cya::utils{

Low_Speed_Data_Rx::Low_Speed_Data_Rx( uint8_t* rx_buffer, uint16_t capacity)
    : read_ptr_(0), write_ptr_(0)
{
    this->rx_buffer_ = rx_buffer;
    this->capacity_ = capacity;
}

void Low_Speed_Data_Rx::write_byte(uint8_t byte)
{
    this->rx_buffer_[this->write_ptr_++] = byte;
}


uint16_t Low_Speed_Data_Rx::length(void)
{
    return ( this->write_ptr_ - this->read_ptr_ );
}

bool Low_Speed_Data_Rx::write(uint8_t* data, uint16_t size)
{
    if( size == 0 )
        return false;

    if( data == NULL )
        return false;

    if( size > this->remain() )
    {
        this->clear( this->length() );
        return false;
    }

    for( int i = 0 ; i < size ; ++i )
    {
        this->write_byte(data[i]);
    }
    return false;
}

uint16_t Low_Speed_Data_Rx::read(uint8_t* data, uint16_t size)
{
    if( data == NULL)
        return 0;
    if( size > this->length() )
        return 0;

    if( size == 0)
    {
        size = this->length();
    }

    for( int i = this->read_ptr_ ; i < this->read_ptr_ + size ; ++i )
    {
        data[ i - this->read_ptr_ ] = this->rx_buffer_[ i ];
    }
    return size;
}

uint16_t Low_Speed_Data_Rx::clear(uint16_t size)
{
    uint16_t len = this->length();
    if( size >= len )
    {
        this->read_ptr_ = 0;
        this->write_ptr_ = 0;
        return len;
    } else {
        this->read_ptr_ += size;
        return size;
    }
}

uint16_t Low_Speed_Data_Rx::remain(void)
{
    return ( this->capacity_ - this->write_ptr_ );
}



}
