/*
 * mainb.c
 *
 *  Created on: Mar 6, 2025
 *      Author: pbu05
 */

#include "stm32f4xx_hal.h"
#include "mainb.h"

void Error_handler(void);

void UART2_Init(void);

UART_HandleTypeDef huart2;

int main(void)
{
	RCC_OscInitTypeDef osc_init;
	RCC_ClkInitTypeDef clk_init;

	osc_init.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	osc_init.HSEState = RCC_HSE_ON;
	osc_init.LSEState = RCC_LSE_OFF;
	osc_init.HSIState = RCC_HSI_OFF;
	osc_init.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	osc_init.LSIState = RCC_LSI_OFF;
	osc_init.PLL = RCC_PLL_NONE;



	HAL_Init();
	UART2_Init();

	while(1);

	return 0;
}


void Error_handler (void)
{
	while(1);
}

void UART2_Init(void)
{
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	if(HAL_UART_Init(&huart2) != HAL_OK)
	{
		Error_handler();
	}
}
