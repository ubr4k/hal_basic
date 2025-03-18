/*
 * itb.c
 *
 *  Created on: Mar 4, 2025
 *      Author: pbu05
 */

#include "mainb.h"

void SysTick_Handler (void)
{

	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}
