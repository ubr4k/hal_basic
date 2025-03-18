/*
 * mainb.c
 *
 *  Created on: Mar 4, 2025
 *      Author: pbu05
 */

#include "stm32f4xx_hal.h"
#include "mainb.h"

void SystemClockConfig(void);
void Error_handler (void);
void timer6_Init (void);
void gpio_Init(void);

TIM_HandleTypeDef htimer6;

int main (void)
{
	HAL_Init();
	SystemClockConfig();

	timer6_Init();
	gpio_Init();
	HAL_TIM_Base_Start(&htimer6);

	while(1)
	{
		while(!(TIM6->SR & TIM_SR_UIF));
		TIM6->SR = 0;
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
	}


}

void SystemClockConfig(void)
{

}

void Error_handler (void)
{
	while(1);
}

void timer6_Init (void)
{

	htimer6.Instance = TIM6;
	htimer6.Init.Prescaler =24;
	htimer6.Init.Period = 64000-1;
	if (HAL_TIM_Base_Init(&htimer6) != HAL_OK)
	{
		Error_handler();
	}

}

void gpio_Init(void)
{
	__HAL_RCC_GPIOA_CLK_ENABLE();

	GPIO_InitTypeDef ledgpio;

	ledgpio.Pin = GPIO_PIN_5;
	ledgpio.Mode = GPIO_MODE_OUTPUT_PP;
	ledgpio.Speed = GPIO_SPEED_FREQ_LOW;
	ledgpio.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &ledgpio);

}

