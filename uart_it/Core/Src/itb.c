/*
 * itb.c
 *
 *  Created on: Mar 6, 2025
 *      Author: pbu05
 */
#include"mainb.h"

extern UART_HandleTypeDef huart2;

void SysTick_Handler (void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

void USART2_IRQHandler (void)
{
	HAL_UART_IRQHandler(&huart2);
}
