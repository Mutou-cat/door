#include "servo.h"
#include "tim.h"


void Servo_Init(void)
{
    // 启动定时器
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
    
    // 设置初始角度为90度
    Servo_SetAngle(0);
}
void Servo_SetAngle(uint8_t angle)
{
    
    if(angle > 180) angle = 180; // 限制角度在0-180度之间
    uint16_t pulseWidth = (uint16_t)(500 + (angle * 2000) / 180); // 计算脉宽，范围500-2500微秒
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, pulseWidth); // 设置比较值
}