/***************************************************************************************
* 本源文件含有PID运算相关函数
***************************************************************************************
*/

#include "main.h"

#include "../../inc/utils/PID.hpp"
#include <cmath>

namespace cya::utils{


bool pid::float_abs_limit( float* num, float max)
{
    float x = *num;
    if (max < 0)
        return false;  // 处理无效的max值

    float abs_x = fabs(x);
    *num = (abs_x > max) ? ((x < 0) ? -max : max) : x;
    return true;
}

pid::pid(float kp,float ki,float kd,
        float total_out_limit,float i_threshold,float i_limit)
    : error_(0.0f), last_error_(0.0f), target_(0.0f), current_(0.0f),
      kp_(kp), ki_(ki), kd_(kd), p_out_(0.0f), i_out_(0.0f), d_out_(0.0f), total_out_(0.0f),
      total_out_limit_(total_out_limit), i_threshold_(i_threshold), i_limit_(i_limit)
{}

void pid::set_pid(float kp ,float ki,float kd)
{
    this->kp_ = kp;
    this->ki_ = ki;
    this->kd_ = kd;
}

void pid::set_out_limit(float total_out_limit)
{
    this->total_out_limit_ = total_out_limit;
}

void pid::set_i_limit(float i_limit)
{
    this->i_limit_ = i_limit;
}

void pid::set_i_threshold(float i_threshold)
{
    this->i_threshold_ = i_threshold;
}

void pid::set_target(float target)
{
    this->target_ = target;
}

float pid::calc_output( float current, float target)
{
    if( !std::isnan(target) )
        this->target_ = target;
        
    this->current_ = current;

    this->error_ = this->target_ - this->current_;            //  得出本次误差

    this->p_out_ = ( this->kp_ * this->error_ );     //  通过本次误差和上次误差得出比例输出

    if( fabsf(this->error_) < this->i_threshold_)                //  判断是否要进行积分分离
    {
        this->i_out_ += ( this->ki_ * this->error_ );//  积分累计误差

        this->float_abs_limit( &(this->i_out_), this->i_limit_ );       //  判断是否要进行积分限幅
    }
    else                                                //  如果要进行积分分离
    {
        this->i_out_ = 0;                                 //  清零积分输出
    }

    this->d_out_ = ( this->kd_ * ( this->error_ - this->last_error_ ) );   //  通过本次误差和上次误差得出微分输出

    this->total_out_ = this->p_out_ + this->i_out_ + this->d_out_;                  //  通过比例输出、积分输出、微分输出得出总输出

    this->float_abs_limit( &(this->total_out_), this->total_out_limit_ );                   //  判断总输出是否过大，对其进行限制

    this->last_error_ = this->error_;                                           //  将本次输出保存到上次输出变量以供下一次运算

    return this->total_out_;
}

void pid::stop_output(void)
{
    this->error_ = 0;
    this->last_error_ = 0;
    this->target_ = 0;
    this->p_out_ = 0;
    this->i_out_ = 0;
    this->d_out_ = 0;
}

void pid::clear_i_out(void)
{
    this->i_out_ = 0;
}

}
