#pragma once

#include "main.h"

namespace cya::peripheral::tim{

class Core{ //  方便用户修改对应数据
protected:
    TIM_HandleTypeDef* ptr_htim_;
public:
    Core(TIM_HandleTypeDef* ptr_htim);

    //  计数值
    void set_cnt( uint16_t cnt ) const;
    uint16_t get_cnt(void) const;

    //  重装载值
    void set_arr( uint16_t arr ) const;
    uint16_t get_arr(void) const;

    //  预分频值
    void set_psc( uint16_t psc ) const;
    uint16_t get_psc(void) const;

    TIM_HandleTypeDef* handle(void) const;
    void set_handle( TIM_HandleTypeDef* ptr_htim );

    bool  isValid(void) const;
};

class Base : public Core{
public:
    Base(TIM_HandleTypeDef* ptr_htim, bool tim_enable = false);
    Base( const Base& other);
    Base( Base&& other);

    HAL_StatusTypeDef start(void) const;
    HAL_StatusTypeDef start_it(void) const;
    HAL_StatusTypeDef start_dma(const uint32_t *pData, uint16_t Length) const;
    HAL_StatusTypeDef stop(void) const;
    HAL_StatusTypeDef stop_it(void) const;
    HAL_StatusTypeDef stop_dma(void) const;
};

/*  废案，占空比上下限可调Pwm
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

class Pwm_Channel : public Core{
protected:
    uint32_t pwm_channel_;
public:
    Pwm_Channel(TIM_HandleTypeDef* ptr_htim,uint32_t pwm_channel,bool pwm_enable = false);
    Pwm_Channel( const Pwm_Channel& other);
    Pwm_Channel( Pwm_Channel&& other);

    HAL_StatusTypeDef start(void) const;
    HAL_StatusTypeDef stop(void) const;
    void set_duty(float duty) const;
    void set_ccr(uint16_t ccr) const;
    uint16_t get_ccr(void) const;
};

class IC : public Core{
protected:
    uint32_t ic_channel_;
public:
    IC(TIM_HandleTypeDef* ptr_htim,uint32_t ic_channel);
    IC( const IC& other);
    IC( IC&& other);

    HAL_StatusTypeDef start(void) const;
    HAL_StatusTypeDef start_it(void) const;
    HAL_StatusTypeDef stop(void) const;
    HAL_StatusTypeDef stop_it(void) const;
};

class Encoder : public Core{
protected:
    uint32_t encoder_channel_;
public:
    Encoder(TIM_HandleTypeDef* ptr_htim_,
            uint32_t encoder_channel = TIM_CHANNEL_ALL,
            bool enable_enable = false);

    Encoder( const Encoder& other);
    Encoder( Encoder&& other);

    HAL_StatusTypeDef start(void) const;
    HAL_StatusTypeDef stop(void) const;
    int16_t get_count_1fm(void) const;
    int16_t get_count_2fm(void) const;
    float get_count_2fm_f(void) const;
    int16_t get_count_4fm(void) const;
    float get_count_4fm_f(void) const;
};



}
