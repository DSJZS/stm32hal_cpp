#pragma once

#include "../utils/buffer_receiver.hpp"

namespace cya::halcpp::protocol
{

typedef struct Parser_In_Out{
    utils::Buffer_Receiver* rx_buffer;
    uint8_t* o_data;
    uint16_t o_data_size;
    void* user_param;   //  冗余变量，用于用于自定义扩展
                        //  尽量用成员变量或者其它方式替代使用该变量
}Parser_IO;

class Protocol_Parser_Base{
public:
    virtual bool get_command( Parser_IO* pas_io) = 0;
};
    
}
