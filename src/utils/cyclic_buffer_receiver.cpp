#include "main.h"

#include "../../inc/utils/cyclic_buffer_receiver.hpp"
#include <cstring>

namespace cya::halcpp::utils{

High_Speed_Data_Rx::High_Speed_Data_Rx( uint8_t* rx_buffer, uint16_t capacity)
    : read_ptr_(0),write_ptr_(0)
{
    this->rx_buffer_ = rx_buffer;
    this->capacity_ = capacity;
}

void High_Speed_Data_Rx::add_read_ptr(uint16_t length)
{
    this->read_ptr_ += length;
    this->read_ptr_ %= this->capacity_;
}

void High_Speed_Data_Rx::write_byte(uint8_t byte)
{
    this->rx_buffer_[ this->write_ptr_ ] = byte;
    ++( this->write_ptr_ );
    this->write_ptr_ %= this->capacity_;
}

uint8_t High_Speed_Data_Rx::read_byte(uint8_t i)
{
    uint16_t index = i % this->capacity_;
    return this->rx_buffer_[ index ];
}

//  写入数据
bool High_Speed_Data_Rx::write(uint8_t* data, uint16_t size)
{
    if( size > this->remain() )
        return 0;
    if( ( data == NULL ) || ( size == 0 ) )
        return 0;

    /*
    for( int i = 0 ; i < size ; ++i )
        this->write_byte(data[i]);
    */

    if( this->write_ptr_ + size < this->capacity_)
    {
        memcpy( this->rx_buffer_ + this->write_ptr_ , data, size);
        this->write_ptr_ += size;
    } else {
        uint16_t first_size = this->capacity_ - this->write_ptr_;
        memcpy( this->rx_buffer_ + this->write_ptr_ , data, first_size);
        memcpy( this->rx_buffer_, data + first_size, size - first_size);
        this->write_ptr_ = size - first_size;
    }

    return size;
}
//  读出数据，不指定 size 默认全读( 读取数据不等于删除数据 )
uint16_t High_Speed_Data_Rx::read(uint8_t* data, uint16_t size)
{
    if( size > this->length() )
        return 0;
    if( data == NULL )
        return 0;
    if( size == 0 )
        size = this->length();

    for( int i = 0 ; i < size ; ++i)
    {
        data[ i ] = this->read_byte( i + this->read_ptr_ );
    }
    return size;
}
//  删除数据，不指定 size 默认全删
uint16_t High_Speed_Data_Rx::clear(uint16_t size)
{
    if( size >= this->length() )
    {
        this->read_ptr_ = 0;
        this->write_ptr_ = 0;
    } else {
        this->read_ptr_ += size;
        this->read_ptr_ %= this->capacity_;
    }
}
//  获取缓冲区当前有多少字节数据
uint16_t High_Speed_Data_Rx::length(void)
{
    return ( this->capacity_ + this->write_ptr_ - this->read_ptr_ ) % this->capacity_;
}
//  获取缓冲区剩余空位
uint16_t High_Speed_Data_Rx::remain(void)
{
    return ( this->capacity_ - this->length() );
}

}
