#include "../../inc/protocols/protocol_parser.hpp"

namespace cya::halcpp::protocol
{


Protocol_Parser::Protocol_Parser( utils::Buffer_Receiver* rx_buffer )
    : rx_buffer_(rx_buffer)
{}

void Protocol_Parser::set_buffer( utils::Buffer_Receiver* rx_buffer )
{
    this->rx_buffer_ = rx_buffer;
}


    
}
