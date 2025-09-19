#include "key.h"


void Key_Port_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};


  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();


  /*Configure GPIO pin : KEY_1_Pin|KEY_2_Pin */
  GPIO_InitStruct.Pin = KEY1_PIN|KEY2_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : KEY_3_Pin KEY_4_Pin */
  GPIO_InitStruct.Pin = KEY3_PIN|KEY4_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

uint8_t KeyScan()
{
	uint8_t keyvalue=0;
	// 检测按键1是否按下
	if (!KEY1) // KEY1为低电平表示按下
	{
		osDelay(20); // 消抖延时
		while (!KEY1); // 等待按键1松开
		osDelay(20); // 再次消抖延时
		keyvalue = 1; // 按键1按下，返回键值1
		
	}

	// 检测按键2是否按下
	if (!KEY2) // KEY2为低电平表示按下
	{
		osDelay(20); // 消抖延时
		while (!KEY2); // 等待按键2松开
		osDelay(20); // 再次消抖延时
		keyvalue = 2; // 按键2按下，返回键值2
	}

	// 检测按键3是否按下
	if (!KEY3) // KEY3为低电平表示按下
	{
		osDelay(20); // 消抖延时
		while (!KEY3); // 等待按键3松开
		osDelay(20); // 再次消抖延时
		keyvalue = 3; // 按键3按下，返回键值3
	}

		// 检测按键4是否按下
	if (!KEY4) // KEY4为低电平表示按下
	{
		osDelay(20); // 消抖延时
		while (!KEY4); // 等待按键4松开
		osDelay(20); // 再次消抖延时
		keyvalue = 4; // 按键4按下，返回键值4
	}
	return keyvalue;
}