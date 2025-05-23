#pragma once

#include "main.h"

namespace cya::halcpp::peripheral::tim{

class Base{
protected:
    TIM_HandleTypeDef* ptr_htim_;
public:
    Base(TIM_HandleTypeDef* ptr_htim, bool tim_enable = false);
    HAL_StatusTypeDef start(void) const;
    HAL_StatusTypeDef stop(void) const;
    void set_counter(uint16_t tim_counter) const;
    uint16_t get_counter(void) const;
};

/*
class Pwm{
private:
    TIM_HandleTypeDef* ptr_htim_;
    uint16_t max_speed_compare_;
    uint16_t min_speed_compare_;
public:
    Pwm(TIM_HandleTypeDef* ptr_pwm_htim,
            uint16_t max_speed_compare, uint16_t min_speed_compare = 0);
    HAL_StatusTypeDef start(uint32_t pwm_channel) const;
    HAL_StatusTypeDef stop(uint32_t pwm_channel) const;
    void set_compare(uint32_t pwm_channel, float compare_value) const;
};
*/

class Pwm_Channel{
protected:
    TIM_HandleTypeDef* ptr_htim_;
    uint32_t pwm_channel_;
    uint16_t max_speed_compare_;
    uint16_t min_speed_compare_;
public:
    Pwm_Channel(TIM_HandleTypeDef* ptr_htim_,uint32_t pwm_channel,
            uint16_t max_speed_compare, uint16_t min_speed_compare = 0,
            bool pwm_enable = false);
    HAL_StatusTypeDef start(void) const;
    HAL_StatusTypeDef stop(void) const;
    void set_compare(float compare_value) const;
};

class Encoder{
protected:
    TIM_HandleTypeDef* ptr_htim_;
    uint32_t encoder_channel_;
public:
    Encoder(TIM_HandleTypeDef* ptr_htim_,
            uint32_t encoder_channel = TIM_CHANNEL_ALL,
            bool enable_enable = false);
    HAL_StatusTypeDef start(void) const;
    HAL_StatusTypeDef stop(void) const;
    int16_t get_count_1fm(void) const;
    int16_t get_count_2fm(void) const;
    float get_count_2fm_f(void) const;
    int16_t get_count_4fm(void) const;
    float get_count_4fm_f(void) const;
};

}
