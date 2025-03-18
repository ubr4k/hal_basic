/*
 * mainb.c
 *
 *  Created on: Mar 7, 2025
 *      Author: pbu05
 */


#include "stm32f4xx_hal.h"
#include "mainb.h"

void SystemClockConfig(void);
void Error_handler(void);

void tim6_Init(void);
void gpio_Init(void);

TIM_HandleTypeDef htimer6;


int main (void)
{
	HAL_Init();
	SystemClockConfig();
	tim6_Init();
	gpio_Init();

	HAL_TIM_Base_Start_IT(&htimer6);

	while(1);

	return 0;

}

void SystemClockConfig(void)
{

}

void Error_handler(void)
{
	while(1);
}

void tim6_Init(void)
{
	htimer6.Instance =TIM6;
	htimer6.Init.Prescaler = 24;
	htimer6.Init.Period = 64000-1;
	if(HAL_TIM_Base_Init(&htimer6)!= HAL_OK)
	{
		Error_handler();
	}
}
void gpio_Init (void)
{
	__HAL_RCC_GPIOA_CLK_ENABLE();

	GPIO_InitTypeDef gpio;

	gpio.Pin = GPIO_PIN_5;
	gpio.Mode = GPIO_MODE_OUTPUT_PP;
	gpio.Speed = GPIO_SPEED_FREQ_LOW;
	gpio.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &gpio);

}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);

}
