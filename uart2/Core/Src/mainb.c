/*
 * mainb.c
 *
 *  Created on: Mar 5, 2025
 *      Author: pbu05
 */

#include "stm32f4xx_hal.h"
#include "mainb.h"
#include <stdio.h>
#include <string.h>

void SystemClockConfig(void);
void Error_handler(void);
void UART2_Init(void);
uint8_t conv_to_cap(uint8_t data);


UART_HandleTypeDef huart2;

char *tx_data = "HOLA!!\r\n";

int main (void)
{
	HAL_Init();
	SystemClockConfig();
	UART2_Init();

    uint16_t len_of_data = strlen(tx_data);
	HAL_UART_Transmit(&huart2,(uint8_t*)tx_data, len_of_data, HAL_MAX_DELAY);

	uint8_t rx_data;
	uint8_t data_buffer[100];
	uint32_t count =0;



	while(1)
	{
	    HAL_UART_Receive(&huart2, &rx_data, 1, HAL_MAX_DELAY);

	    if(rx_data == '\r')
	    {
	    	break;
	    }else
	    {
            data_buffer[count++]=conv_to_cap(rx_data);
	    }
	}

	data_buffer[count++] = '\r';
	HAL_UART_Transmit(&huart2,data_buffer, count, HAL_MAX_DELAY);

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

void UART2_Init (void)
{
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	if( HAL_UART_Init(&huart2) != HAL_OK)
	{
		Error_handler();
	}
}

uint8_t conv_to_cap(uint8_t data)
{
	if(data >= 'a' && data <= 'z')
	{
		data = data - (-'A'+'a');
	}
	return data;
}
