#include "main.h"
#include "../../inc/peripherals/tim.hpp"

namespace cya::peripheral::tim{

Core::Core(TIM_HandleTypeDef* ptr_htim)
    : ptr_htim_(ptr_htim)
{}

void Core::set_cnt(uint16_t cnt) const
{
    if( this->ptr_htim_ )
        __HAL_TIM_SET_COUNTER(this->ptr_htim_, cnt);
}

uint16_t Core::get_cnt(void) const
{
    if( this->ptr_htim_ )
        return __HAL_TIM_GET_COUNTER(this->ptr_htim_);
    return 0;
}

void Core::set_arr( uint16_t arr ) const
{
    if( this->ptr_htim_ )
        __HAL_TIM_SET_AUTORELOAD(this->ptr_htim_, arr);
}

uint16_t Core::get_arr(void) const
{
    if( this->ptr_htim_ )
        return __HAL_TIM_GET_AUTORELOAD(this->ptr_htim_);
    return 0;
}

void Core::set_psc( uint16_t psc ) const
{
    if( this->ptr_htim_ )
        __HAL_TIM_SET_PRESCALER(this->ptr_htim_, psc);
}

uint16_t Core::get_psc(void) const
{
    if( this->ptr_htim_ )
        return this->ptr_htim_->Instance->PSC;
    return 0;
}

TIM_HandleTypeDef* Core::handle(void) const
{
    return this->ptr_htim_;
}

void Core::set_handle( TIM_HandleTypeDef* ptr_htim )
{
    this->ptr_htim_ = ptr_htim;
}


bool  Core::isValid(void) const
{
    if( this->ptr_htim_ == nullptr )
        return false;
    else
        return true;
        
}

Base::Base(TIM_HandleTypeDef* ptr_htim, bool tim_enable)
    : Core(ptr_htim)
{
    if(tim_enable && this->ptr_htim_)
        this->start();
}

Base::Base( const Base& other)
    : Core(other.ptr_htim_)
{}

Base::Base( Base&& other)
    : Core(other.ptr_htim_)
{
    other.ptr_htim_ = nullptr;
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

Pwm_Channel::Pwm_Channel(TIM_HandleTypeDef* ptr_htim,uint32_t pwm_channel,bool pwm_enable)
    : Core(ptr_htim), pwm_channel_(pwm_channel)
{
    if( pwm_enable && this->ptr_htim_ )
        this->start();
}

Pwm_Channel::Pwm_Channel( const Pwm_Channel& other)
    : Core(other.ptr_htim_), pwm_channel_(other.pwm_channel_)
{}

Pwm_Channel::Pwm_Channel( Pwm_Channel&& other)
    : Core(other.ptr_htim_), pwm_channel_(other.pwm_channel_)
{
    other.ptr_htim_ = nullptr;
    other.pwm_channel_ = -1;
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
// duty = CCR / (ARR + 1)
// CCR = duty * (ARR + 1)
void Pwm_Channel::set_duty(float duty) const
{
    if( this->ptr_htim_ )
        __HAL_TIM_SET_COMPARE(this->ptr_htim_,this->pwm_channel_,
            duty * ( __HAL_TIM_GET_AUTORELOAD(this->ptr_htim_) + 1 ));
}

void Pwm_Channel::set_ccr(uint16_t ccr) const
{
    if( this->ptr_htim_ )
        __HAL_TIM_SET_COMPARE(this->ptr_htim_,this->pwm_channel_,ccr);
}

uint16_t Pwm_Channel::get_ccr(void) const
{
    if( this->ptr_htim_ )
        __HAL_TIM_GET_COMPARE(this->ptr_htim_,this->pwm_channel_);
    return 0;
}

IC::IC(TIM_HandleTypeDef* ptr_htim,uint32_t ic_channel)
    : Core(ptr_htim), ic_channel_(ic_channel)
{}

IC::IC( const IC& other)
    : Core(other.ptr_htim_), ic_channel_(other.ic_channel_)
{}

IC::IC( IC&& other)
    : Core(other.ptr_htim_), ic_channel_(other.ic_channel_)
{
    other.ptr_htim_ = nullptr;
    other.ic_channel_ = -1;
}

HAL_StatusTypeDef IC::start(void) const
{
    return HAL_TIM_IC_Start( this->ptr_htim_, this->ic_channel_);
}

HAL_StatusTypeDef IC::start_it(void) const
{
    return HAL_TIM_IC_Start_IT( this->ptr_htim_, this->ic_channel_);
}

HAL_StatusTypeDef IC::stop(void) const
{
    return HAL_TIM_IC_Stop( this->ptr_htim_, this->ic_channel_);
}

HAL_StatusTypeDef IC::stop_it(void) const
{
    return HAL_TIM_IC_Stop_IT( this->ptr_htim_, this->ic_channel_);
}

uint16_t IC::get_ccr(void) const
{
    if( this->ptr_htim_ )
        HAL_TIM_ReadCapturedValue(this->ptr_htim_,this->ic_channel_);
    return 0;
}

Encoder::Encoder(TIM_HandleTypeDef* ptr_htim,
        uint32_t encoder_channel, bool enable_enable)
    : Core(ptr_htim), encoder_channel_(encoder_channel)
{
    if( enable_enable && this->ptr_htim_ )
        HAL_TIM_Encoder_Start(this->ptr_htim_, this->encoder_channel_);
}

Encoder::Encoder( const Encoder& other)
    : Core(other.ptr_htim_), encoder_channel_(other.encoder_channel_)
{}

Encoder::Encoder( Encoder&& other)
    : Core(other.ptr_htim_), encoder_channel_(other.encoder_channel_)
{
    other.ptr_htim_ = nullptr;
    other.encoder_channel_ = -1;
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
