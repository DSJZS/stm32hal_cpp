#pragma once

namespace cya::halcpp::module{

class Blue_Tooth{
public:
    virtual void init(void) = 0;
    virtual void send_data(uint8_t* data, uint16_t size) = 0;
};

}
