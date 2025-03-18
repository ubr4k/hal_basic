/*
 * mspb.c
 *
 *  Created on: Mar 10, 2025
 *      Author: pbu05
 */

#include "mainb.h"

void HAL_MspInit(void)
{
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

	SCB->SHCSR |= 0x7 << 16;

	HAL_NVIC_EnableIRQ(BusFault_IRQn);
	HAL_NVIC_EnableIRQ(UsageFault_IRQn);
	HAL_NVIC_EnableIRQ(MemoryManagement_IRQn);

}

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
	__HAL_RCC_USART2_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

	GPIO_InitTypeDef gpiou;
	gpiou.Pin = GPIO_PIN_2;
	gpiou.Mode = GPIO_MODE_AF_PP;
	gpiou.Speed = GPIO_SPEED_FREQ_LOW;
	gpiou.Pull = GPIO_NOPULL;
	gpiou.Alternate =GPIO_AF7_USART2;
	HAL_GPIO_Init(GPIOA, &gpiou);

	HAL_NVIC_EnableIRQ(USART2_IRQn);
	HAL_NVIC_SetPriority(USART2_IRQn, 15, 0);
}

void HAL_TIM_OC_MspInit(TIM_HandleTypeDef *htim)
{
	__HAL_RCC_TIM2_CLK_ENABLE();

	GPIO_InitTypeDef gpioc;
	gpioc.Pin = GPIO_PIN_0 | GPIO_PIN_1;
	gpioc.Mode = GPIO_MODE_AF_PP;
	gpioc.Pull = GPIO_NOPULL;
	gpioc.Alternate = GPIO_AF1_TIM2;
	gpioc.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIOA, &gpioc);

	gpioc.Pin = GPIO_PIN_2 | GPIO_PIN_10;
	gpioc.Mode = GPIO_MODE_AF_PP;
	gpioc.Pull = GPIO_NOPULL;
	gpioc.Alternate = GPIO_AF1_TIM2;
	gpioc.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIOB, &gpioc);

	HAL_NVIC_EnableIRQ(TIM2_IRQn);
	HAL_NVIC_SetPriority(TIM2_IRQn, 15, 0);

}
