/*
 * mainb.c
 *
 *  Created on: Mar 10, 2025
 *      Author: pbu05
 */

#include "mainb.h"

void SystemClock_Config_HSE(uint8_t clock_freq);
void Error_handler(void);
void uart2_init(void);
void gpio_init(void);
void timer2_init(void);

UART_HandleTypeDef huart2;
TIM_HandleTypeDef htimer2;

uint32_t pulse1_value = 25000;//500hz switching freq 1khz(pulsewidth)
uint32_t pulse2_value = 12500;//1khz
uint32_t pulse3_value = 6250; //2khz
uint32_t pulse4_value = 3125; //4khz

volatile uint32_t ccr;

int main(void)
{
	HAL_Init();
	SystemClock_Config_HSE(50);
	gpio_init();
	uart2_init();
	timer2_init();


	if(HAL_TIM_OC_Start_IT(&htimer2, TIM_CHANNEL_1)!= HAL_OK)
	{
		Error_handler();
	}

	if(HAL_TIM_OC_Start_IT(&htimer2, TIM_CHANNEL_2)!= HAL_OK)
		{
			Error_handler();
		}

	if(HAL_TIM_OC_Start_IT(&htimer2, TIM_CHANNEL_3)!= HAL_OK)
		{
			Error_handler();
		}

	if(HAL_TIM_OC_Start_IT(&htimer2, TIM_CHANNEL_4)!= HAL_OK)
		{
			Error_handler();
		}
	while(1);
	return 0;
}

void SystemClock_Config_HSE(uint8_t clock_freq)
{

    RCC_OscInitTypeDef Osc_Init;
    RCC_ClkInitTypeDef Clock_Init;
    uint8_t flash_latency=0;

    Osc_Init.OscillatorType = RCC_OSCILLATORTYPE_HSE ;
    Osc_Init.HSEState = RCC_HSE_ON;
    Osc_Init.PLL.PLLState = RCC_PLL_ON;
    Osc_Init.PLL.PLLSource = RCC_PLLSOURCE_HSE;

    switch(clock_freq) {
    case 50:
      Osc_Init.PLL.PLLM = 4;
      Osc_Init.PLL.PLLN = 50;
      Osc_Init.PLL.PLLP = RCC_PLLP_DIV2;
      Osc_Init.PLL.PLLQ = 2;
      Osc_Init.PLL.PLLR = 2;
      Clock_Init.ClockType = RCC_CLOCKTYPE_HCLK  | RCC_CLOCKTYPE_SYSCLK |
                             RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
      Clock_Init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
      Clock_Init.AHBCLKDivider = RCC_SYSCLK_DIV1;
      Clock_Init.APB1CLKDivider = RCC_HCLK_DIV2;
      Clock_Init.APB2CLKDivider = RCC_HCLK_DIV1;
      flash_latency = 1;
      break;

    case 84:
      Osc_Init.PLL.PLLM = 4;
      Osc_Init.PLL.PLLN = 84;
      Osc_Init.PLL.PLLP = RCC_PLLP_DIV2;
      Osc_Init.PLL.PLLQ = 2;
      Osc_Init.PLL.PLLR = 2;
      Clock_Init.ClockType = RCC_CLOCKTYPE_HCLK  | RCC_CLOCKTYPE_SYSCLK |
                             RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
      Clock_Init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
      Clock_Init.AHBCLKDivider = RCC_SYSCLK_DIV1;
      Clock_Init.APB1CLKDivider = RCC_HCLK_DIV2;
      Clock_Init.APB2CLKDivider = RCC_HCLK_DIV1;
      flash_latency = 2;
      break;

    case 120:
      Osc_Init.PLL.PLLM = 4;
      Osc_Init.PLL.PLLN = 120;
      Osc_Init.PLL.PLLP = RCC_PLLP_DIV2;
      Osc_Init.PLL.PLLQ = 2;
      Osc_Init.PLL.PLLR = 2;
      Clock_Init.ClockType = RCC_CLOCKTYPE_HCLK  | RCC_CLOCKTYPE_SYSCLK |
                             RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
      Clock_Init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
      Clock_Init.AHBCLKDivider = RCC_SYSCLK_DIV1;
      Clock_Init.APB1CLKDivider = RCC_HCLK_DIV4;
      Clock_Init.APB2CLKDivider = RCC_HCLK_DIV2;
      flash_latency = 3;
      break;

    default:

      return ;
    }

    if (HAL_RCC_OscConfig(&Osc_Init) != HAL_OK)
    {
      Error_handler();
    }

    if (HAL_RCC_ClockConfig(&Clock_Init, flash_latency) != HAL_OK)
    {
      Error_handler();
    }

    uint32_t hclk_freq = HAL_RCC_GetHCLKFreq();
    HAL_SYSTICK_Config(hclk_freq/1000);

    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

    HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

void uart2_init(void)
{
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.OverSampling = UART_OVERSAMPLING_16;
	if(HAL_UART_Init(&huart2) != HAL_OK)
	{
		Error_handler();
	}

}
void timer2_init(void)
{
	htimer2.Instance = TIM2;
	htimer2.Init.Prescaler = 1;
	htimer2.Init.Period = 0xffffffff;
	if(HAL_TIM_OC_Init(&htimer2)!= HAL_OK)
	{
		Error_handler();
	}

	TIM_OC_InitTypeDef timoc_init;

	timoc_init.OCMode = TIM_OCMODE_TOGGLE;
	timoc_init.Pulse = pulse1_value;
	timoc_init.OCPolarity = TIM_OCPOLARITY_HIGH;

	if(HAL_TIM_OC_ConfigChannel(&htimer2, &timoc_init, TIM_CHANNEL_1) != HAL_OK)
	{
		Error_handler();
	}

	timoc_init.Pulse = pulse2_value;
	if(HAL_TIM_OC_ConfigChannel(&htimer2, &timoc_init, TIM_CHANNEL_2) != HAL_OK)
	{
		Error_handler();
	}

	timoc_init.Pulse = pulse3_value;
	if(HAL_TIM_OC_ConfigChannel(&htimer2, &timoc_init, TIM_CHANNEL_3) != HAL_OK)
	{
		Error_handler();
	}

	timoc_init.Pulse = pulse4_value;
	if(HAL_TIM_OC_ConfigChannel(&htimer2, &timoc_init, TIM_CHANNEL_4) != HAL_OK)
	{
		Error_handler();
	}

}
void gpio_init(void)
{
	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitTypeDef ledgpio;
	ledgpio.Pin = GPIO_PIN_5;
	ledgpio.Pull = GPIO_NOPULL;
	ledgpio.Mode = GPIO_MODE_OUTPUT_PP;
	ledgpio.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIOA, &ledgpio);

}

void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{

    if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
    {
      ccr = HAL_TIM_ReadCapturedValue(htim,TIM_CHANNEL_1);
      __HAL_TIM_SET_COMPARE(htim,TIM_CHANNEL_1,ccr+pulse1_value);
    }

    if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
    {
      ccr = HAL_TIM_ReadCapturedValue(htim,TIM_CHANNEL_2);
      __HAL_TIM_SET_COMPARE(htim,TIM_CHANNEL_2,ccr+pulse2_value);
    }

    if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3)
    {
      ccr = HAL_TIM_ReadCapturedValue(htim,TIM_CHANNEL_3);
      __HAL_TIM_SET_COMPARE(htim,TIM_CHANNEL_3,ccr+pulse3_value);
    }

    if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_4)
    {
      ccr = HAL_TIM_ReadCapturedValue(htim,TIM_CHANNEL_4);
      __HAL_TIM_SET_COMPARE(htim,TIM_CHANNEL_4,ccr+pulse4_value);
    }
}

void Error_handler(void)
{
	while(1);
}
