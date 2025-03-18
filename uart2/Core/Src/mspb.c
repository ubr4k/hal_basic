/*
 * mspb.c
 *
 *  Created on: Mar 5, 2025
 *      Author: pbu05
 */


#include "stm32f4xx_hal.h"

void HAL_MspInit(void)
{
	/*
	 * 1- Priority group of processor
	 * 2- Enable system exceptions
	 * 3- Priority of system exceptions
	 * 4- Other specialization
	 */
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4); // 4bitlik position 4-0 olarak pre sub
	SCB->SHCSR |= 0x7 <<16; //usg,mem,bus fault
	HAL_NVIC_SetPriority(BusFault_IRQn, 0, 0);
	HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0, 0);
	HAL_NVIC_SetPriority(UsageFault_IRQn, 0, 0);



}

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
     /*
      * 1- enable clock
      * 2- pin muxing config
      * 3- enable irq and set up priority
      */
	__HAL_RCC_USART2_CLK_ENABLE();

	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitTypeDef gpioa_uart;
	gpioa_uart.Pin = GPIO_PIN_2; // RX
	gpioa_uart.Mode = GPIO_MODE_AF_PP;
	gpioa_uart.Pull = GPIO_PULLUP;
	gpioa_uart.Speed = GPIO_SPEED_FREQ_LOW;
	gpioa_uart.Alternate = GPIO_AF7_USART2;
	HAL_GPIO_Init(GPIOA, &gpioa_uart);
	gpioa_uart.Pin = GPIO_PIN_3; // TX
	HAL_GPIO_Init(GPIOA, &gpioa_uart);

	HAL_NVIC_EnableIRQ(USART2_IRQn);
	HAL_NVIC_SetPriority(USART2_IRQn, 15, 0);
}
