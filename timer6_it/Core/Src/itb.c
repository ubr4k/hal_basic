/*
 * itb.c
 *
 *  Created on: Mar 7, 2025
 *      Author: pbu05
 */
#include "mainb.h"

extern TIM_HandleTypeDef htimer6;

void SysTick_Handler (void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

void TIM6_DAC_IRQHandler(void)
{

	HAL_TIM_IRQHandler(&htimer6);
}
