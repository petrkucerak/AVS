/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "inttypes.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#ifndef HSEM_ID_0
#define HSEM_ID_0 (0U) /* HW semaphore 0*/
#endif

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

#define EMPTY 15

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void PeriphCommonClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */
	/* USER CODE BEGIN Boot_Mode_Sequence_0 */
	int32_t timeout;
	/* USER CODE END Boot_Mode_Sequence_0 */

	/* USER CODE BEGIN Boot_Mode_Sequence_1 */
	/* Wait until CPU2 boots and enters in stop mode or timeout*/
	timeout = 0xFFFF;
	while ((__HAL_RCC_GET_FLAG(RCC_FLAG_D2CKRDY) != RESET) && (timeout-- > 0))
		;
	if (timeout < 0) {
		Error_Handler();
	}
	/* USER CODE END Boot_Mode_Sequence_1 */
	/* MCU
	 * Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick.
	 */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* Configure the peripherals common clocks */
	PeriphCommonClock_Config();
	/* USER CODE BEGIN Boot_Mode_Sequence_2 */
	/* When system initialization is finished, Cortex-M7 will release Cortex-M4
	 by means of HSEM notification */
	/*HW semaphore Clock enable*/
	__HAL_RCC_HSEM_CLK_ENABLE();
	/*Take HSEM */
	HAL_HSEM_FastTake(HSEM_ID_0);
	/*Release HSEM in order to notify the CPU2(CM4)*/
	HAL_HSEM_Release(HSEM_ID_0, 0);
	/* wait until CPU2 wakes up from stop mode */
	timeout = 0xFFFF;
	while ((__HAL_RCC_GET_FLAG(RCC_FLAG_D2CKRDY) == RESET) && (timeout-- > 0))
		;
	if (timeout < 0) {
		Error_Handler();
	}
	/* USER CODE END Boot_Mode_Sequence_2 */

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_USART1_UART_Init();
	/* USER CODE BEGIN 2 */

	uint8_t symbol = EMPTY;

	// turn off all LEDs
	HAL_GPIO_WritePin(GPIOI, LED1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOI, LED2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOI, LED3_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOI, LED4_Pin, GPIO_PIN_SET);

	uint8_t rx_buff[10];
	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {

		// MIRROR UART
		if (HAL_UART_Receive(&huart1, rx_buff, 10, 100) == HAL_OK) // if transfer is successful
				{
			__NOP(); // You need to toggle a breakpoint on this line!
		} else {
			__NOP();
		}
		HAL_UART_Transmit(&huart1, rx_buff, 10, 100);

		HAL_GPIO_WritePin(GPIOJ, KEYBOARD_1_Pin, GPIO_PIN_RESET);
		if (!HAL_GPIO_ReadPin(GPIOF, KEYBOARD_4_Pin))
			symbol = 1;
		if (!HAL_GPIO_ReadPin(GPIOJ, KEYBOARD_5_Pin))
			symbol = 10;
		if (!HAL_GPIO_ReadPin(GPIOA, KEYBOARD_6_Pin))
			symbol = 11;
		if (!HAL_GPIO_ReadPin(GPIOJ, KEYBOARD_7_Pin))
			symbol = 6;
		HAL_GPIO_WritePin(GPIOJ, KEYBOARD_1_Pin, GPIO_PIN_SET);

		HAL_Delay(10);

		HAL_GPIO_WritePin(GPIOJ, KEYBOARD_2_Pin, GPIO_PIN_RESET);
		if (!HAL_GPIO_ReadPin(GPIOF, KEYBOARD_4_Pin))
			symbol = 2;
		if (!HAL_GPIO_ReadPin(GPIOJ, KEYBOARD_5_Pin))
			symbol = 4;
		if (!HAL_GPIO_ReadPin(GPIOA, KEYBOARD_6_Pin))
			symbol = 9;
		if (!HAL_GPIO_ReadPin(GPIOJ, KEYBOARD_7_Pin))
			symbol = 7;
		HAL_GPIO_WritePin(GPIOJ, KEYBOARD_2_Pin, GPIO_PIN_SET);

		HAL_Delay(10);

		HAL_GPIO_WritePin(GPIOJ, KEYBOARD_3_Pin, GPIO_PIN_RESET);
		if (!HAL_GPIO_ReadPin(GPIOF, KEYBOARD_4_Pin))
			symbol = 3;
		if (!HAL_GPIO_ReadPin(GPIOJ, KEYBOARD_5_Pin))
			symbol = 5;
		if (!HAL_GPIO_ReadPin(GPIOA, KEYBOARD_6_Pin))
			symbol = 0;
		if (!HAL_GPIO_ReadPin(GPIOJ, KEYBOARD_7_Pin))
			symbol = 8;
		HAL_GPIO_WritePin(GPIOJ, KEYBOARD_3_Pin, GPIO_PIN_SET);

		if (symbol != EMPTY) {
			switch (symbol) {
			case 0:
				rx_buff[0] = 48;
				break;
			case 1:
				rx_buff[0] = 49;
				break;
			case 2:
				rx_buff[0] = 50;
				break;
			case 3:
				rx_buff[0] = 51;
				break;
			case 4:
				rx_buff[0] = 52;
				break;
			case 5:
				rx_buff[0] = 53;
				break;
			case 6:
				rx_buff[0] = 54;
				break;
			case 7:
				rx_buff[0] = 55;
				break;
			case 8:
				rx_buff[0] = 56;
				break;
			case 9:
				rx_buff[0] = 57;
				break;
			case 10:
				rx_buff[0] = 8;
				break;
			case 11:
				rx_buff[0] = 127;
				break;

			default:
				break;
			}
			symbol = EMPTY;
			HAL_UART_Transmit(&huart1, rx_buff, 1, 10);
			HAL_Delay(50);
		}

		// DISPLAY BINARY NUMBER BY LIGHT
		// first bit
		if (rx_buff[0] == 49 || rx_buff[0] == 51 || rx_buff[0] == 53
				|| rx_buff[0] == 55 || rx_buff[0] == 57)
			HAL_GPIO_WritePin(GPIOI, LED1_Pin, GPIO_PIN_RESET);
		else
			HAL_GPIO_WritePin(GPIOI, LED1_Pin, GPIO_PIN_SET);
		// second bit
		if (rx_buff[0] == 50 || rx_buff[0] == 51 || rx_buff[0] == 54
				|| rx_buff[0] == 55)
			HAL_GPIO_WritePin(GPIOI, LED2_Pin, GPIO_PIN_RESET);
		else
			HAL_GPIO_WritePin(GPIOI, LED2_Pin, GPIO_PIN_SET);

		// third bit
		if (rx_buff[0] == 52 || rx_buff[0] == 53 || rx_buff[0] == 54
				|| rx_buff[0] == 55)
			HAL_GPIO_WritePin(GPIOI, LED3_Pin, GPIO_PIN_RESET);
		else
			HAL_GPIO_WritePin(GPIOI, LED3_Pin, GPIO_PIN_SET);

		// fourth bit
		if (rx_buff[0] == 56 || rx_buff[0] == 57)
			HAL_GPIO_WritePin(GPIOI, LED4_Pin, GPIO_PIN_RESET);
		else
			HAL_GPIO_WritePin(GPIOI, LED4_Pin, GPIO_PIN_SET);


		// clean the array for rx_buff
		for (uint8_t i = 0; i < 10; ++i) {
			rx_buff[i] = 0;
		}

		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Supply configuration update enable
	 */
	HAL_PWREx_ConfigSupply(PWR_DIRECT_SMPS_SUPPLY);

	/** Configure the main internal regulator output voltage
	 */
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	while (!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {
	}

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType =
	RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.HSIState = RCC_HSI_DIV1;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.LSIState = RCC_LSI_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 5;
	RCC_OscInitStruct.PLL.PLLN = 48;
	RCC_OscInitStruct.PLL.PLLP = 2;
	RCC_OscInitStruct.PLL.PLLQ = 5;
	RCC_OscInitStruct.PLL.PLLR = 2;
	RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_2;
	RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
	RCC_OscInitStruct.PLL.PLLFRACN = 0;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK |
	RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2 |
	RCC_CLOCKTYPE_D3PCLK1 | RCC_CLOCKTYPE_D1PCLK1;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
	RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV1;
	RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK) {
		Error_Handler();
	}
	HAL_RCC_MCOConfig(RCC_MCO1, RCC_MCO1SOURCE_HSI, RCC_MCODIV_1);
}

/**
 * @brief Peripherals Common Clock Configuration
 * @retval None
 */
void PeriphCommonClock_Config(void) {
	RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = { 0 };

	/** Initializes the peripherals clock
	 */
	PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_ADC;
	PeriphClkInitStruct.PLL2.PLL2M = 2;
	PeriphClkInitStruct.PLL2.PLL2N = 12;
	PeriphClkInitStruct.PLL2.PLL2P = 2;
	PeriphClkInitStruct.PLL2.PLL2Q = 2;
	PeriphClkInitStruct.PLL2.PLL2R = 2;
	PeriphClkInitStruct.PLL2.PLL2RGE = RCC_PLL2VCIRANGE_3;
	PeriphClkInitStruct.PLL2.PLL2VCOSEL = RCC_PLL2VCOMEDIUM;
	PeriphClkInitStruct.PLL2.PLL2FRACN = 0;
	PeriphClkInitStruct.AdcClockSelection = RCC_ADCCLKSOURCE_PLL2;
	if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK) {
		Error_Handler();
	}
}

/**
 * @brief USART1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_USART1_UART_Init(void) {

	/* USER CODE BEGIN USART1_Init 0 */

	/* USER CODE END USART1_Init 0 */

	/* USER CODE BEGIN USART1_Init 1 */

	/* USER CODE END USART1_Init 1 */
	huart1.Instance = USART1;
	huart1.Init.BaudRate = 115200;
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.StopBits = UART_STOPBITS_1;
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.Mode = UART_MODE_TX_RX;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	huart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
	huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	if (HAL_UART_Init(&huart1) != HAL_OK) {
		Error_Handler();
	}
	if (HAL_UARTEx_SetTxFifoThreshold(&huart1, UART_TXFIFO_THRESHOLD_1_8)
			!= HAL_OK) {
		Error_Handler();
	}
	if (HAL_UARTEx_SetRxFifoThreshold(&huart1, UART_RXFIFO_THRESHOLD_1_8)
			!= HAL_OK) {
		Error_Handler();
	}
	if (HAL_UARTEx_DisableFifoMode(&huart1) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN USART1_Init 2 */

	/* USER CODE END USART1_Init 2 */
}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void) {
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	/* USER CODE BEGIN MX_GPIO_Init_1 */
	/* USER CODE END MX_GPIO_Init_1 */

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOI_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOF_CLK_ENABLE();
	__HAL_RCC_GPIOJ_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOI, LED1_Pin | LED2_Pin | LED3_Pin | LED4_Pin,
			GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOJ, KEYBOARD_1_Pin | KEYBOARD_2_Pin | KEYBOARD_3_Pin,
			GPIO_PIN_RESET);

	/*Configure GPIO pin : CEC_CK_MCO1_Pin */
	GPIO_InitStruct.Pin = CEC_CK_MCO1_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Alternate = GPIO_AF0_MCO;
	HAL_GPIO_Init(CEC_CK_MCO1_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pins : LED1_Pin LED2_Pin LED3_Pin LED4_Pin */
	GPIO_InitStruct.Pin = LED1_Pin | LED2_Pin | LED3_Pin | LED4_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

	/*Configure GPIO pin : KEYBOARD_4_Pin */
	GPIO_InitStruct.Pin = KEYBOARD_4_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(KEYBOARD_4_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pins : KEYBOARD_1_Pin KEYBOARD_2_Pin KEYBOARD_3_Pin */
	GPIO_InitStruct.Pin = KEYBOARD_1_Pin | KEYBOARD_2_Pin | KEYBOARD_3_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOJ, &GPIO_InitStruct);

	/*Configure GPIO pins : KEYBOARD_7_Pin KEYBOARD_5_Pin */
	GPIO_InitStruct.Pin = KEYBOARD_7_Pin | KEYBOARD_5_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOJ, &GPIO_InitStruct);

	/*Configure GPIO pin : KEYBOARD_6_Pin */
	GPIO_InitStruct.Pin = KEYBOARD_6_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(KEYBOARD_6_GPIO_Port, &GPIO_InitStruct);

	/* USER CODE BEGIN MX_GPIO_Init_2 */
	/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state
	 */
	__disable_irq();
	while (1) {
	}
	/* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
   /* USER CODE BEGIN 6 */
   /* User can add his own implementation to report the file name and line
      number, ex: printf("Wrong parameters value: file %s on line %d\r\n", file,
      line) */
   /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
