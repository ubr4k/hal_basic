/*
 * mainb.c
 *
 *  Created on: Mar 6, 2025
 *      Author: pbu05
 */


#include "mainb.h"
#include <string.h>
#include "stm32f4xx_hal.h"

void SystemClockConfig(void);
void Error_handler(void);

void UART2_Init(void);
uint8_t convert_to_capital(uint8_t data);
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

UART_HandleTypeDef huart2;
char *user_data = "hola!!\r\n";
uint32_t count=0;
uint8_t rx_data;
uint8_t data_buffer[100];
uint8_t reception_complete = 0;


int main(void)
{
	HAL_Init();
	SystemClockConfig();
	UART2_Init();

	uint16_t len_of_data = strlen(user_data);
	HAL_UART_Transmit(&huart2,(uint8_t*)user_data,len_of_data,HAL_MAX_DELAY);

	while(reception_complete != 1 )
	{
		HAL_UART_Receive_IT(&huart2, &rx_data, 1);
	}

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

void UART2_Init(void)
{
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	if(HAL_UART_Init(&huart2) != HAL_OK)
	{
		Error_handler();
	}
}

uint8_t convert_to_capital(uint8_t data)
{

    if( data >= 'a' && data <= 'z')
    {
        data = data - ( 'a'- 'A');
    }

    return data;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(rx_data == '\r')
	{
		reception_complete = 1;
		data_buffer[count++] = '\r';
		HAL_UART_Transmit(huart, data_buffer, count, HAL_MAX_DELAY);
	}else
	{
		data_buffer[count++] = rx_data;
	}

}
