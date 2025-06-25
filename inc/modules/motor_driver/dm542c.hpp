#pragma once
   
#include "./base.hpp"
#include "../../peripherals/gpio.hpp"
#include "../../peripherals/tim.hpp"

namespace cya::module::motor_driver{

//  默认 共阳极 接法
class Dm542c : public motor_driver::Base{
public:
    enum class ConnectType{
        CC,     //  共阴极
        CA,     //  共阳极
    };
    enum class DireType{
        CW,     //  顺时针
        CCW,    //  逆时针
    };
    Dm542c( Dm542c::ConnectType ct, uint16_t microsteps, const peripheral::gpio::Pin& EN, const peripheral::gpio::Pin& DIR );
protected:
    Dm542c::ConnectType ct_;    //  共阴极 or 共阳极
    uint16_t microsteps_;       //  微步

    const peripheral::gpio::Pin EN_;
    const peripheral::gpio::Pin DIR_;

    void set_enable( uint8_t enable) const;
    void set_dire( Dm542c::DireType dire) const;

    //  set_speed 会关闭门控定位
    //  set_angle 在 angle != 0 时会开启门控定位, 在 angle == 0 时等价于 set_speed
    virtual void set_angle(float angle, float base_speed = 0.0f) const = 0;
    virtual bool is_rotation_complete(void) const = 0;
};

class Dm542c_Pin : public Dm542c{
private:
    const peripheral::gpio::Pin PULSE_;
public:
    Dm542c_Pin( Dm542c::ConnectType ct, uint16_t microsteps,
        const peripheral::gpio::Pin& EN, const peripheral::gpio::Pin& DIR,
        const peripheral::gpio::Pin& PULSE);

    virtual void init(void) override;
    virtual void set_speed(float base_speed = 0.0f) const override; //  undefined
    virtual void set_angle(float angle, float base_speed = 0.0f) const override; //  undefined
    virtual bool is_rotation_complete(void) const override; //  undefined
};

/* 如果要使用 set_angle 方法, 门空配置方法
 * TIMx 输出PWM，TIMy 产生门信号
 * 
 * TIMx 配置: 
 * Slave Mode : Gated Mode
 * Trigger Mode : ITRy ( 指向 TIMy )
 * Clock Source : Internal Clock
 * ARR : 调节脉冲频率
 * CCR : = ARR >> 1
 * TRGO : Update Event
 * Channelx : PWM Generation CHx( PWM mode 1 )
 * 按照 PWM 配置
 * 
 * TIMy 配置: 
 * Slave Mode : External Clock Mode 1
 * Trigger Mode : ITRx ( 指向 TIMx )
 * Clock Source : Disable
 * ARR : 尽可能大, 增大可操作范围
 * CCR : 调节目标脉冲数, 最大值为 ARR+1 即关闭定位( 要求 ARR 值合理，放置 +1 后溢出 )
 * TRGO : OCxREF
 * Channelx : PWM Generation No Output( PWM mode 1 )
 * 
 * 
 * Slave TIM        ITR0    ITR1    ITR2    ITR3
 *       TIM1       TIM5    TIM2    TIM3    TIM4
 *       TIM2       TIM1    TIM8    TIM3    TIM4
 *       TIM3       TIM1    TIM2    TIM5    TIM4
 *       TIM4       TIM1    TIM2    TIM3    TIM8
 *       TIM5       TIM2    TIM3    TIM4    TIM8
 *       TIM8       TIM1    TIM2    TIM4    TIM5
 *       TIM9       TIM2    TIM3    TIM10   TIM11
 *       TIM12      TIM4    TIM5    TIM13   TIM14
 */
class Dm542c_Pwm : public Dm542c{
private:
    const peripheral::tim::Pwm_Channel PULSE_;  //  PWM通道  
    const peripheral::tim::Pwm_Channel GATE_;   //  门信号通道

    void set_step(uint16_t step) const;
public:
    Dm542c_Pwm(Dm542c::ConnectType ct, uint16_t microsteps,
        const peripheral::gpio::Pin& EN, const peripheral::gpio::Pin& DIR,
        const peripheral::tim::Pwm_Channel& PULSE,
        const peripheral::tim::Pwm_Channel& GATE);

    Dm542c_Pwm(Dm542c::ConnectType ct, uint16_t microsteps,
        const peripheral::gpio::Pin& EN, const peripheral::gpio::Pin& DIR,
        const peripheral::tim::Pwm_Channel& PULSE);

    virtual void init(void) override;
    virtual void set_speed(float base_speed = 0.0f) const override;
    virtual void set_angle(float angle, float base_speed = 0.0f) const override;
    virtual bool is_rotation_complete(void) const override;
};

}