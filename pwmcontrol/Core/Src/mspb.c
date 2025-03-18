/*
 * mspb.c
 *
 *  Created on: Mar 12, 2025
 *      Author: pbu05
 */


#include "mainb.h"

void HAL_MspInit (void)
{
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

	SCB->SHCSR |= 0x7 << 16;

	HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0, 0);
	HAL_NVIC_SetPriority(BusFault_IRQn, 0, 0);
	HAL_NVIC_SetPriority(UsageFault_IRQn, 0, 0);
}

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
  __HAL_RCC_USART2_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  GPIO_InitTypeDef gpio_uart2;
  gpio_uart2.Pin = GPIO_PIN_2;
  gpio_uart2.Pull = GPIO_NOPULL;
  gpio_uart2.Speed = GPIO_SPEED_LOW;
  gpio_uart2.Mode = GPIO_MODE_AF_PP;
  gpio_uart2.Alternate = GPIO_AF7_USART2;
  HAL_GPIO_Init(GPIOA, &gpio_uart2);

  gpio_uart2.Pin = GPIO_PIN_3;
  HAL_GPIO_Init(GPIOA, &gpio_uart2);

  HAL_NVIC_EnableIRQ(USART2_IRQn);
  HAL_NVIC_SetPriority(USART2_IRQn, 15, 0);

}

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
	__HAL_RCC_TIM2_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

	GPIO_InitTypeDef tim2chn;
	tim2chn.Pin = GPIO_PIN_0;
	tim2chn.Mode = GPIO_MODE_AF_PP;
	tim2chn.Pull = GPIO_PULLDOWN;
	tim2chn.Speed = GPIO_SPEED_FREQ_LOW;
	tim2chn.Alternate = GPIO_AF1_TIM2;
	HAL_GPIO_Init(GPIOA, &tim2chn);


	HAL_NVIC_EnableIRQ(TIM2_IRQn);
	HAL_NVIC_SetPriority(TIM2_IRQn, 15, 0);

}

void HAL_ADC_MspInit(ADC_HandleTypeDef *hadc)
{
	__HAL_RCC_ADC1_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	GPIO_InitTypeDef gpio_init;
	gpio_init.Pin = GPIO_PIN_0;
	gpio_init.Mode = GPIO_MODE_ANALOG;
	gpio_init.Pull = GPIO_NOPULL;
	gpio_init.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &gpio_init);

    HAL_NVIC_SetPriority(ADC_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(ADC_IRQn);
}


