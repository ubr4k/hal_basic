/*
 * mainb.c
 *
 *  Created on: Mar 12, 2025
 *      Author: pbu05
 */


#include "mainb.h"

void SystemClockConfig(uint8_t clock);
void Error_handler (void);
void uart2_init(void);
void gpio_init(void);
void timer2_init(void);
void adc_init(void);
void read_adc (void);
void update_pwm(uint16_t x);

UART_HandleTypeDef huart2;
GPIO_InitTypeDef ledgpio;
GPIO_InitTypeDef gpioadc;
TIM_HandleTypeDef htim2;
ADC_HandleTypeDef hadc1;
ADC_ChannelConfTypeDef cadc1;

uint16_t readvalue1;
uint16_t pwm;


int main (void)
{
	HAL_Init();
	SystemClockConfig(50);
	uart2_init();
	gpio_init();
	timer2_init();
	adc_init();

	/*if ( HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1) != HAL_OK)
	  {
	    Error_handler();
	  }*/


	while(1)
	{
		read_adc();
		update_pwm(readvalue1);
		HAL_Delay(10);
	}
	return 0;
}

void SystemClockConfig(uint8_t clock)
{

	RCC_OscInitTypeDef Osc_Init;
	RCC_ClkInitTypeDef Clock_Init;
	uint8_t flash_latency=0;

	Osc_Init.OscillatorType = RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_LSE | RCC_OSCILLATORTYPE_HSI ;
	Osc_Init.HSEState = RCC_HSE_ON;
	Osc_Init.LSEState = RCC_LSE_ON;
	Osc_Init.HSIState = RCC_HSI_ON;
    Osc_Init.PLL.PLLState = RCC_PLL_ON;
	Osc_Init.PLL.PLLSource = RCC_PLLSOURCE_HSE;

	switch(clock) {
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
	huart2.Init.Mode=UART_MODE_TX_RX;
	if(HAL_UART_Init(&huart2)!= HAL_OK)
	{
		Error_handler();
	}
}

void gpio_init(void)
{
	__HAL_RCC_GPIOA_CLK_ENABLE();
	ledgpio.Pin = GPIO_PIN_5;
	ledgpio.Mode = GPIO_MODE_OUTPUT_PP;
	ledgpio.Speed = GPIO_SPEED_LOW;
	ledgpio.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &ledgpio);

	__HAL_RCC_GPIOB_CLK_ENABLE();
	gpioadc.Pin = GPIO_PIN_0;
	gpioadc.Mode = GPIO_MODE_ANALOG;
	gpioadc.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOB, &gpioadc);
}

void timer2_init(void)
{
	htim2.Instance = TIM2;
	htim2.Init.Period = 20;
	htim2.Init.Prescaler =16;
	if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
	{
		Error_handler();
	}
	TIM_OC_InitTypeDef tim2pwm;

	memset(&tim2pwm,0,sizeof(tim2pwm));

	tim2pwm.OCMode = TIM_OCMODE_PWM1;
	tim2pwm.OCPolarity = TIM_OCPOLARITY_HIGH;

	tim2pwm.Pulse = (htim2.Init.Period *25)/100;
	if(HAL_TIM_PWM_ConfigChannel(&htim2, &tim2pwm, TIM_CHANNEL_1)!= HAL_OK)
	{
		Error_handler();
	}
	if (HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1) != HAL_OK)
	{
	    Error_handler(); // Hata durumu
	}

}

void adc_init (void)
{
	hadc1.Instance = ADC1;
	hadc1.Init.ClockPrescaler =ADC_CLOCK_SYNC_PCLK_DIV4;
	hadc1.Init.Resolution = ADC_RESOLUTION_12B;
	hadc1.Init.ScanConvMode = DISABLE;
	hadc1.Init.ContinuousConvMode = ENABLE;
	hadc1.Init.DiscontinuousConvMode = DISABLE;
	hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadc1.Init.NbrOfConversion = 1;
	hadc1.Init.DMAContinuousRequests = DISABLE;
	hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
	if (HAL_ADC_Init(&hadc1) != HAL_OK)
	{
	  Error_handler();
	}

}

void read_adc (void)
{

		cadc1.Channel = ADC_CHANNEL_8; //pinb0
		cadc1.Rank = 1;
		cadc1.SamplingTime = ADC_SAMPLETIME_3CYCLES;
		if (HAL_ADC_ConfigChannel(&hadc1, &cadc1) != HAL_OK)
		{
		  Error_handler();
		}

		if (HAL_ADC_Start(&hadc1)!= HAL_OK)
		{
		    Error_handler();
		}

		HAL_ADC_PollForConversion(&hadc1, 1000);
		readvalue1 = HAL_ADC_GetValue(&hadc1);

		//update_pwm(readvalue1);

		if(HAL_ADC_Stop(&hadc1)!= HAL_OK)
		{
			Error_handler();
		}

}
void update_pwm(uint16_t x)
{
	pwm = (x * (htim2.Init.Period)) / 4095;  // 12-bit ADC okuması
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, pwm);
}

void Error_handler (void)
{
	while(1);
}
