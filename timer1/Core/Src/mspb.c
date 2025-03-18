/*
 * mspb.c
 *
 *  Created on: Mar 4, 2025
 *      Author: pbu05
 */

#include "stm32f4xx_hal.h"
#include "mainb.h"


void HAL_MspInit(void)
{
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

	SCB->SHCSR |= 0x7 << 16;

	HAL_NVIC_SetPriority(BusFault_IRQn, 15, 0);
	HAL_NVIC_SetPriority(UsageFault_IRQn, 15, 0);
	HAL_NVIC_SetPriority(MemoryManagement_IRQn, 15, 0);

}

void HAL_TIM_Base_MspInit (TIM_HandleTypeDef *htimer)
{
	__HAL_RCC_TIM6_CLK_ENABLE();

	HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);

	HAL_NVIC_SetPriority(TIM6_DAC_IRQn, 15, 0);
}

