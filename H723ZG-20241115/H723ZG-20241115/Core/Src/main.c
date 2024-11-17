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
#include "adc.h"
#include "cordic.h"
#include "dma.h"
#include "i2c.h"
#include "memorymap.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "liquidcrystal_i2c.h"

//#include "i2c-lcd.h"
#include "stdio.h"
#include "stdlib.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t TxBuf[] = "Hello world\n";

uint8_t tx_buff[7];
uint8_t rx_buff[7];

// ADC
__IO uint32_t ADC_ConvertedValue;

float ADC_Vol;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void PeriphCommonClock_Config(void);
/* USER CODE BEGIN PFP */

#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

PUTCHAR_PROTOTYPE {
	HAL_UART_Transmit(&huart3, (uint8_t*) &ch, 1, HAL_MAX_DELAY);
	return ch;
}

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

// i2c-lcd
int row = 0;
int col = 0;
uint32_t ADCArray[2] = { 0 };
// uint32_t voltage[2] = { 0 };
uint16_t voltage[2] = { 0 };

uint8_t adc_ready = 0;



/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* Configure the peripherals common clocks */
  PeriphCommonClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_TIM4_Init();
  MX_USART3_UART_Init();
  MX_I2C1_Init();
  MX_TIM6_Init();
  MX_ADC2_Init();
  MX_CORDIC_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */

	// HAL_UART_Receive_IT(&huart3, rx_buff, 7);
	HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_1 | TIM_CHANNEL_2);

	HAL_TIM_Base_Start_IT(&htim6);
	HAL_TIM_Base_Stop_IT(&htim6);

//	HAL_ADCEx_Calibration_Start(&hadc2, ADC_CALIB_OFFSET_LINEARITY,
//			ADC_DIFFERENTIAL_ENDED);
	// HAL_ADC_Start_IT(&hadc2);
//	HAL_TIM_Base_Start_IT(&htim2);

//	if (HAL_ADC_Start_DMA(&hadc2, (uint32_t*) voltage, 2) != HAL_OK) {
//		printf("ADC initialization error!\r\n");
//	}

//  HAL_ADCEx_Calibration_Start(&hadc1, ADC_CALIB_OFFSET_LINEARITY,ADC_DIFFERENTIAL_ENDED);

//	HAL_ADCEx_Calibration_Start(&hadc1);

//	 if(HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1) != HAL_OK)
//	                Error_Handler();

	// HAL_TIM_Base_Init(&htim2);
	// HAL_TIM_Base_Start(&htim2);
	// HAL_ADC_Start_DMA(&hadc1, (uint32_t *)voltage, 2);
	// HAL_ADC_Start_DMA(&hadc1, voltage, 2);
	HAL_ADC_Start_DMA(&hadc1, (uint32_t *)voltage, (uint32_t) 2);
	HAL_TIM_Base_Start(&htim2);

	//HAL_ADC_Start_IT(&hadc1, (uint32_t *)voltage, 2);

	//HAL_ADCEx_InjectedStart_IT(&hadc1);




	// Display Strings
//    lcd_init ();
//
//    lcd_put_cur(0, 0);
//    lcd_send_string ("HELLO WORLD");
//    lcd_put_cur(1, 0);
//    lcd_send_string("from CTECH");

	/* Initialize */
	HD44780_Init(2);

	/* Clear buffer */
	HD44780_Clear();

	/* Hide characters */
	HD44780_NoDisplay();
	HD44780_Cursor();
	HD44780_SetCursor(0, 0);
	HD44780_PrintStr("HELLO STM32!!!");
	HD44780_PrintSpecialChar(0);
	HAL_Delay(1000);

	/* Show characters */
	HD44780_Display();

	/* Move position */
	HD44780_SetCursor(0, 1);
	HD44780_PrintStr("BYE STM32!!!");
	HD44780_PrintSpecialChar(1);
	HAL_Delay(1000);

	/* Blink cursor */
	HD44780_Blink();

//  /* Scroll Right */
//  for(int i = 0; i < 3; i++)
//  {
//    HD44780_ScrollDisplayRight();
//    HAL_Delay(1000);
//  }
//
//  /* Scroll Left */
//  for(int i = 0; i < 3; i++)
//  {
//    HD44780_ScrollDisplayLeft();
//    HAL_Delay(1000);
//  }

//  HD44780_Display();

//  HD44780_Clear();
//  HD44780_SetCursor(0,0);
//  HD44780_PrintStr("Learning STM32 with LCD is fun :-)");
//
//  for(int x=0; x<40; x=x+1)
//  {
//    HD44780_ScrollDisplayLeft();  //HD44780_ScrollDisplayRight();
//    HAL_Delay(500);
//  }
//
	char snum[5];
	for (int x = 1; x <= 200; x++) {
		itoa(x, snum, 10);
		HD44780_Clear();
		HD44780_SetCursor(0, 0);
		HD44780_PrintStr(snum);
		HAL_Delay(10);
	}


	HAL_TIM_Base_Start_IT(&htim6);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
//  char sdir[5];
//  char scount[10];
//	printf("Characters: %c %c\n", 'a', 65);
//	printf("Decimals: %d %ld\n", 1977, 650000L);
//	printf("Preceding with blanks: %10d\n", 1977);
//	printf("Preceding with zeros: %010d\n", 1977);
//	printf("Some different radices: %d %x %o %#x %#o\n", 100, 100, 100, 100, 100);
//	printf("floats: %4.2f %+.0e %E\n", 3.1416, 3.1416, 3.1416);
//	printf("Width trick: %*d\n", 5, 10);
//	printf("%s\n", "A string");

	while (1) {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

		while(adc_ready != 1){

		}
		adc_ready = 0;

		HAL_ADC_Start_DMA(&hadc1, (uint32_t *)voltage, (uint32_t) 2);

		// HAL_UART_Transmit(&huart3, TxBuf, sizeof(TxBuf) -1 , 100);
		// HAL_UART_Transmit_IT(&huart3, TxBuf, sizeof(TxBuf));
//	  int Direction = __HAL_TIM_IS_TIM_COUNTING_DOWN(&htim4);
//	  int CaptureNumber = (short) __HAL_TIM_GET_COUNTER(&htim4);
//	  __HAL_TIM_GET_COUNTER(&htim4) = 0;
//
//	  HD44780_Clear();
//
//	  itoa(Direction, sdir, 10);
//	  itoa(CaptureNumber, scount, 10);
//
//	  HD44780_SetCursor(0,0);
//
//	  // HD44780_PrintStr(sdir);
//
//	  if(Direction == 0)
//	  {
//		  HD44780_PrintStr("Positive!");
//	  }
//	  else
//	  {
//		  HD44780_PrintStr("Negative!");
//
//	  }
//
//
//	  HD44780_SetCursor(0,1);
//	  HD44780_PrintStr(scount);
//	  HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
//	  HAL_Delay(1000);

//		 HAL_ADC_PollForConversion(&hadc2,0x01);
//		// HAL_ADC_PollForConversion(&hadc2,HAL_MAX_DELAY);
//
//		if(HAL_IS_BIT_SET(HAL_ADC_GetState(&hadc2),HAL_ADC_STATE_REG_EOC)){
//		    voltage[0] = HAL_ADC_GetValue(&hadc2);
//				voltage[0]=voltage[0]*3300/4095;
//		}
//		 HAL_ADC_PollForConversion(&hadc2,0x01);
//		//HAL_ADC_PollForConversion(&hadc2,HAL_MAX_DELAY);
//		if(HAL_IS_BIT_SET(HAL_ADC_GetState(&hadc2),HAL_ADC_STATE_REG_EOC)){
//		    voltage[1] = HAL_ADC_GetValue(&hadc2);
//				voltage[1]=voltage[1]*3300/4095;
//		}
//
//		printf("Voltage[0]: %d\n", (int)voltage[0]);
//		printf("Voltage[1]: %d\n", (int)voltage[1]);

		// HAL_Delay(100);
	}
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = 64;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 12;
  RCC_OscInitStruct.PLL.PLLP = 1;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief Peripherals Common Clock Configuration
  * @retval None
  */
void PeriphCommonClock_Config(void)
{
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Initializes the peripherals clock
  */
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInitStruct.PLL2.PLL2M = 4;
  PeriphClkInitStruct.PLL2.PLL2N = 13;
  PeriphClkInitStruct.PLL2.PLL2P = 3;
  PeriphClkInitStruct.PLL2.PLL2Q = 2;
  PeriphClkInitStruct.PLL2.PLL2R = 2;
  PeriphClkInitStruct.PLL2.PLL2RGE = RCC_PLL2VCIRANGE_3;
  PeriphClkInitStruct.PLL2.PLL2VCOSEL = RCC_PLL2VCOWIDE;
  PeriphClkInitStruct.PLL2.PLL2FRACN = 4096;
  PeriphClkInitStruct.AdcClockSelection = RCC_ADCCLKSOURCE_PLL2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	HAL_UART_Receive_IT(&huart3, rx_buff, sizeof(rx_buff));

	//memcpy();

	//HAL_UART_Transmit_IT(&huart3, TxBuf, sizeof(TxBuf));

	for (int i = 0; i < sizeof(rx_buff); i++) {
		tx_buff[i] = rx_buff[i];
		rx_buff[i] = '\0';

	}

	HAL_UART_Transmit_IT(&huart3, tx_buff, sizeof(tx_buff));

	// memset(rx_buff,0 , sizeof(rx_buff));
	// strcpy(rx_buff, tx_buff);

}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
//	char sdir[5];
//	char scount[10];

	char x1_col_str[10];
	char x2_col_str[10];

	int Direction = 0;
	int CaptureNumber = 0;


	if(htim->Instance == TIM2){
		// HAL_ADC_Start_DMA(&hadc1, (uint32_t *)voltage, 2);
	}

	if (htim->Instance == TIM6) {
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);

		Direction = __HAL_TIM_IS_TIM_COUNTING_DOWN(&htim4);
		CaptureNumber = (short) __HAL_TIM_GET_COUNTER(&htim4);
		__HAL_TIM_GET_COUNTER(&htim4) = 0;

//		HD44780_Clear();
//
//		itoa(Direction, sdir, 10);
//		itoa(CaptureNumber, scount, 10);
//
//		HD44780_SetCursor(0, 0);
//
//		if (Direction == 0)
//			HD44780_PrintStr("Positive!");
//		else
//			HD44780_PrintStr("Negative!");
//
//		HD44780_SetCursor(0, 1);
//		HD44780_PrintStr(scount);
//
//
//		HAL_ADC_Start(&hadc1);
//		HAL_ADC_PollForConversion(&hadc1, 10);
//		ADC_ConvertedValue = HAL_ADC_GetValue(&hadc1);
//		printf("ADC_ConvertedValue : %d\n", (int)ADC_ConvertedValue);

		HD44780_Clear();
		HD44780_SetCursor(0, 0);
		HD44780_PrintStr("X:");
		HD44780_SetCursor(2, 0);
		itoa(voltage[0], x1_col_str,10);
		HD44780_PrintStr(x1_col_str);


		HD44780_SetCursor(0, 1);
		HD44780_PrintStr("Y:");
		HD44780_SetCursor(2, 1);

		itoa(voltage[1], x2_col_str,10);
		HD44780_PrintStr(x2_col_str);

	}
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {

	if (hadc->Instance == ADC2) {
		//HAL_ADC_Start_DMA(&hadc2, (uint32_t *)voltage, 2);
//		printf("Voltage[0]: %d\n", (int) voltage[0]);
//		printf("Voltage[1]: %d\n", (int) voltage[1]);
	}else if(hadc->Instance == ADC1){
		// Do not thing!
		// HAL_ADC_Start_DMA(&hadc1, (uint32_t *)voltage, 2);
		adc_ready = 1;
		HAL_ADC_Stop_DMA(&hadc1);

	}
}


void HAL_ADCEx_InjectedConvCpltCallback(ADC_HandleTypeDef* hadc) {
    if (hadc->Instance == ADC1) {
    	// HAL_ADC_Start_DMA(&hadc1, (uint32_t *)voltage, 2);
    }
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_PIN)
{
	// User_Button_Pin
	if(GPIO_PIN == User_Button_Pin)
	{

		//ADC_ConvertedValue = HAL_ADC_GetValue(&hadc1);

//		HAL_ADC_Start(&hadc1);
//		HAL_ADC_PollForConversion(&hadc1, 10);
//		ADC_ConvertedValue = HAL_ADC_GetValue(&hadc1);
//		printf("ADC_ConvertedValue : %d\n", (int)ADC_ConvertedValue);
	}
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
	}
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
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
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
