/*
 * itb.c
 *
 *  Created on: Mar 5, 2025
 *      Author: pbu05
 */
#include "stm32f4xx_hal.h"
void SysTick_Handler (void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}
