#include "main.h"
#include "../../inc/peripherals/tim.hpp"

namespace cya::peripheral::tim{

Base::Base(TIM_HandleTypeDef* ptr_htim, bool tim_enable)
    : ptr_htim_(ptr_htim)
{
    if(tim_enable && this->ptr_htim_)
        this->start();
}

HAL_StatusTypeDef Base::start(void) const
{
    if( this->ptr_htim_ )
        return HAL_TIM_Base_Start(this->ptr_htim_);
    return HAL_ERROR;
}

HAL_StatusTypeDef Base::start_it(void) const
{
    if( this->ptr_htim_ )
        return HAL_TIM_Base_Start_IT(this->ptr_htim_);
    return HAL_ERROR;
}

HAL_StatusTypeDef Base::start_dma(const uint32_t *pData, uint16_t Length) const
{
    if( this->ptr_htim_ )
        return HAL_TIM_Base_Start_DMA(this->ptr_htim_,pData,Length);
    return HAL_ERROR;
}

HAL_StatusTypeDef Base::stop(void) const
{
    if( this->ptr_htim_ )
        return HAL_TIM_Base_Stop(this->ptr_htim_);
    return HAL_ERROR;
}

HAL_StatusTypeDef Base::stop_it(void) const
{
    if( this->ptr_htim_ )
        return HAL_TIM_Base_Stop_IT(this->ptr_htim_);
    return HAL_ERROR;
}

HAL_StatusTypeDef Base::stop_dma(void) const
{
    if( this->ptr_htim_ )
        return HAL_TIM_Base_Stop_DMA(this->ptr_htim_);
    return HAL_ERROR;
}

uint16_t Base::get_counter(void) const
{
    if( this->ptr_htim_ )
        return __HAL_TIM_GET_COUNTER(this->ptr_htim_);
    return 0;
}

TIM_HandleTypeDef* Base::ptr_handle(void) const
{
    return this->ptr_htim_;
}

void Base::set_counter(uint16_t tim_counter) const
{
    if( this->ptr_htim_ )
        __HAL_TIM_SET_COUNTER(this->ptr_htim_, tim_counter);
}

Pwm_Channel::Pwm_Channel(
        TIM_HandleTypeDef* ptr_htim,uint32_t pwm_channel,
        uint16_t max_speed_compare, uint16_t min_speed_compare,
        bool pwm_enable)
    : ptr_htim_(ptr_htim), pwm_channel_(pwm_channel),
      max_speed_compare_(max_speed_compare),min_speed_compare_(min_speed_compare)
{
    if( pwm_enable && this->ptr_htim_ )
        this->start();
}

HAL_StatusTypeDef Pwm_Channel::start(void) const
{
    if( this->ptr_htim_ )
        return HAL_TIM_PWM_Start(this->ptr_htim_, this->pwm_channel_);
    return HAL_ERROR;
}

HAL_StatusTypeDef Pwm_Channel::stop(void) const
{
    if( this->ptr_htim_ )
        return HAL_TIM_PWM_Stop(this->ptr_htim_, this->pwm_channel_);
    return HAL_ERROR;
}

void Pwm_Channel::set_compare(float compare_value) const
{
    if( this->ptr_htim_ )
        __HAL_TIM_SET_COMPARE(this->ptr_htim_,this->pwm_channel_,
            compare_value * ( this->max_speed_compare_ - this->min_speed_compare_));
}

Encoder::Encoder(TIM_HandleTypeDef* ptr_htim,
        uint32_t encoder_channel, bool enable_enable)
    : ptr_htim_(ptr_htim), encoder_channel_(encoder_channel)
{
    if( enable_enable && this->ptr_htim_ )
        HAL_TIM_Encoder_Start(this->ptr_htim_, this->encoder_channel_);
}

HAL_StatusTypeDef Encoder::start(void) const
{
    if( this->ptr_htim_ )
        return HAL_TIM_Encoder_Start(this->ptr_htim_, this->encoder_channel_);
    return HAL_ERROR;
}

HAL_StatusTypeDef Encoder::stop(void) const
{
    if( this->ptr_htim_ )
        return HAL_TIM_Encoder_Stop(this->ptr_htim_, this->encoder_channel_);
    return HAL_ERROR;
}

int16_t Encoder::get_count_1fm(void) const
{
    if( this->ptr_htim_ )
    {
        int16_t encoder_counter = (int16_t)( __HAL_TIM_GET_COUNTER(this->ptr_htim_) );
        __HAL_TIM_SET_COUNTER( this->ptr_htim_, 0);
        return encoder_counter;
    }
    return 0;
}

int16_t Encoder::get_count_2fm(void) const
{
    return this->get_count_1fm() / 2;
}

float Encoder::get_count_2fm_f(void) const
{
    return (float)(this->get_count_1fm()) / 2.0f;
}

int16_t Encoder::get_count_4fm(void) const
{
    return this->get_count_1fm() / 4;
}

float Encoder::get_count_4fm_f(void) const
{
    return (float)(this->get_count_1fm()) / 4.0f;
}

}
