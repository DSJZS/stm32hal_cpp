#pragma once

#include "../utils/buffer_receiver.hpp"

namespace cya::halcpp::protocol
{

class Protocol_Parser{
protected:
    utils::Buffer_Receiver* rx_buffer_;
public:
    Protocol_Parser( utils::Buffer_Receiver* rx_buffer );
    void set_buffer( utils::Buffer_Receiver* rx_buffer );
};
    
}
