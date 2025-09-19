#ifndef __KEY_H__
#define __KEY_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f1xx_hal.h"
typedef enum {
    KEY_NONE = 0,   // 没有按键
    KEY_BACK,       //返回
    KEY_UP,         // 上
    KEY_DOWN,       // 下
    KEY_ENTER      // 确认 / 前进
   
} KeyValue;

//KEY1
#define KEY1_PORT	GPIOB
#define KEY1_PIN	GPIO_PIN_12
#define KEY1 HAL_GPIO_ReadPin(KEY1_PORT,KEY1_PIN)

//KEY2
#define KEY2_PORT	GPIOB
#define KEY2_PIN	GPIO_PIN_15
#define KEY2 HAL_GPIO_ReadPin(KEY2_PORT,KEY2_PIN)

//KEY3
#define KEY3_PORT	GPIOA
#define KEY3_PIN	GPIO_PIN_10
#define KEY3 HAL_GPIO_ReadPin(KEY3_PORT,KEY3_PIN)

//KEY4
#define KEY4_PORT	GPIOA
#define KEY4_PIN	GPIO_PIN_15
#define KEY4 HAL_GPIO_ReadPin(KEY4_PORT,KEY4_PIN)

void Key_Port_Init(void);
uint8_t KeyScan();


#ifdef __cplusplus
}
#endif
#endif

