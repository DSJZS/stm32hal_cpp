#pragma once

#include "../peripherals/gpio.hpp"

namespace cya::stm32::module{

class Led{
public:
    enum class ActiveLevel{HIGH,LOW};
    enum class State{ON,OFF};

    Led( peripheral::gpio::Pin& pin, Led::ActiveLevel level);
    Led( GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, Led::ActiveLevel level);
    ~Led();

    void on(void);
    void off(void);
    void toggle(void);
    Led::State state(void);
private:
    peripheral::gpio::Pin pin_;
    Led::ActiveLevel level_;
};

}
