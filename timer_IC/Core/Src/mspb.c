/*
 * mspb.c
 *
 *  Created on: Mar 8, 2025
 *      Author: pbu05
 */


#include "mainb.h"


void HAL_MspInit(void)
{
  HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

  SCB->SHCSR |= 0x7 << 16;

  HAL_NVIC_SetPriority(BusFault_IRQn, 0, 0);
  HAL_NVIC_SetPriority(UsageFault_IRQn, 0, 0);
  HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0, 0);

}

void HAL_TIM_IC_MspInit(TIM_HandleTypeDef *htim)
{
	__HAL_RCC_TIM2_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

	GPIO_InitTypeDef gpio;
	gpio.Pin = GPIO_PIN_0;
	gpio.Mode = GPIO_MODE_AF_PP;
	gpio.Speed = GPIO_SPEED_FREQ_LOW;
	gpio.Pull = GPIO_NOPULL;
	gpio.Alternate = GPIO_AF1_TIM2;
	HAL_GPIO_Init(GPIOA, &gpio);

	HAL_NVIC_EnableIRQ(TIM2_IRQn);

	HAL_NVIC_SetPriority(TIM2_IRQn, 15, 0);
}
