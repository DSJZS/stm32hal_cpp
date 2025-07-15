#pragma once

#include "main.h"
#include <cmath>

namespace cya::utils{

class pid{
private:
    bool float_abs_limit( float* num, float max);
    float error_;            //  本次误差
    float last_error_;       //  上次误差

    float target_;           //  目标值
    float current_;          //  当前值
    float kp_;               //  Kp参数
    float ki_;               //  Ki参数
    float kd_;               //  Kd参数
    float p_out_;          //  比例输出
    float i_out_;          //  积分输出
    float d_out_;          //  微分输出
    float total_out_;      //  总输出
    float total_out_limit_;//  总输出最大值
    float i_threshold_;        //  积分分离
    float i_limit_;       //  积分限幅

public:
    pid(float kp,float ki,float kd,
            float total_out_limit = 1.0,
            float i_threshold = 1.0,
            float i_limit = 1.0);
    void set_pid(float kp ,float ki,float kd);
    void set_out_limit(float total_out_limit);
    void set_i_limit(float i_limit);
    void set_i_threshold(float i_threshold);
    void set_target(float target);
    float calc_output(float current, float target = std::numeric_limits<float>::quiet_NaN());
    void stop_output(void);
    void clear_i_out(void);
};

}
