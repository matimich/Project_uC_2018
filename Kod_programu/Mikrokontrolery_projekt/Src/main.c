/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2019 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "fatfs.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdlib.h>
#include "zone.h"
#include <string.h>
#include "stm32f4xx_hal_flash.h"
#include "../SW4STM32/UART_GPS/EEPROM/eeprom.h"
#include "GSM.h"
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
SPI_HandleTypeDef hspi1;
TIM_HandleTypeDef htim10;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart6;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
uint8_t GPS_Rec[68];
uint8_t *GPS_Rec_2;
uint8_t GPS_Check;

FATFS FatFs;
FIL fil;
FRESULT fresult;

/*
// Zmienne biblioteki "EEPROM"
uint16_t VirtAddVarTab[NB_OF_VAR] = {0x5555, 0x6666, 0x7777};
uint16_t VarDataTab[NB_OF_VAR] = {0, 0, 0};
uint16_t VarValue,VarDataTmp = 77;
*/

/* parametry strefy */
int Szer_Gorna_Granica =  510000000; // 5100.00000,N
int Szer_Dolna_Granica = -490000000; // 4900.00000,S
int Dl_prawo_Granica = 215911430; // 02159.11430,E
int Dl_lewo_Granica = -205911430; // 02059.11430,W



/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART6_UART_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_TIM10_Init(void);
static void MX_SPI1_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/





void gsm(void)	// funkcja przetwazajaca polecenia od GSM
{
	if (GSM_Buff[1] == '1')	// #1 - wyslij aktualna pozycje
	{
		if ((char) GPS_Rec_2[17] == 'V' || (char) GPS_Rec_2[18] == 'V' || (char) GPS_Rec_2[9] == 'V')
		{
			GSM_send(NUMER,"Blad,gps nie odbiera sygnalu.\n\r");
		}
		else
		{
			char* source = (char*) malloc(85 * sizeof(uint8_t)); //dlugosc ramki stala, sprawdzone
			send_google((char*) GPS_Rec_2, source); //wlasna funkcja tworzaca link do google maps
			GSM_send(NUMER,source);
		}
	}

	else if (GSM_Buff[1] == '2') //#2 -ramka NMEA
	{
		GSM_send(NUMER,(char*)GPS_Rec_2);
	}

	else if (GSM_Buff[1] == '3') //#3 - RESET rejestratora
	{
		NVIC_SystemReset();
	}
	else if (GSM_Buff[1] == '4') //#4 - TEST
	{
		GSM_send(NUMER,"\n\r<GPS_Check>\n\r");
	}
	/*			/////Do rozwiniecia w przyszlosci
	else if (GSM_Buff[1] == '5') //#5 ustaw gorna szerokosc geograficzna za ktora rejestrator nie moze wyjsc
	{
		Szer_Gorna_Granica = 510000000;
		ustaw_punkt_GS(&Szer_Gorna_Granica);
	}

	else if (GSM_Buff[1] == '6') //#6 -ustaw dolna szerokosc geograficzna za ktora rejestrator nie moze wyjsc
	{
		VarValue = 16;
	    if((EE_WriteVariable(VirtAddVarTab[0],  VarValue)) != HAL_OK)
	    {
	    	//ustaw_punkt_A(&Szer_Gorna_Granica);
	    }
	}

	else if (GSM_Buff[1] == '7') //#7 -ustaw lewa granice dlugosci geograficznej za ktora rejestrator nie moze wyjsc
	{
	    if(EE_ReadVariable(VirtAddVarTab[0], &VarDataTmp) != HAL_OK)
	    {
	    	char* information = "blad odczytu\r\n";
	    	int length = sprintf(information,"blad odczytu\r\n");
	    	HAL_UART_Transmit(&huart6, (uint8_t*) information,(uint16_t) length,10);
	    }
	}
	else if (GSM_Buff[1] == '8') //#8 -ustaw prawa granice dlugosci geograficznej za ktora rejestrator nie moze wyjsc
	{
		//ustaw_punkt_A(&Szer_Gorna_Granica);
	}
	*/
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (GSM_Buff[0] != '#') // pobieranie ramki GPS wylaczone gdy nadawany jest GSM
	{
		if (GPS_Check == 10)	// wykrycie poczatku ramki NMEA, 10 == '$'
		{
			HAL_UART_Receive_IT(&huart1, GPS_Rec, 68);//odbierz cala ramke NMEA
			GPS_Rec_2 = GPS_Rec;	//przypisanie ramki do drugiego stringa

			f_lseek(&fil,f_size(&fil)); //przejscie na koniec pliku
			f_puts(GPS_Rec_2,&fil);	//zapis ramki na karte
			f_sync(&fil);		//"Flush cached data"

			GPS_Check = '0';	//wyczyszczenie znaku
			HAL_UART_Receive_IT(&huart1, &GPS_Check, 1);	//sprawdzaj ponowine
		}
		else
		{
			HAL_UART_Receive_IT(&huart1, &GPS_Check, 1);// szukaj znaku poczatku ramki
		}
	}


	if(huart->Instance == USART2)	//przerwanie od modulu GSM
	{
			if(GSM_Rx == '+')	//poczatek komunikatu od modulu GSM
			{
				if(GSM_rec_check() == 1)
				{
					save_mess(GSM_Buff);
					if (GSM_Buff[0] == '#')	//znak oznaczajacy detekcje polecenia od GSM
					{
						//HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);
						gsm();
						GSM_Buff[0] = '0';	//wyczyszczenie komendy od GSM
						HAL_UART_Receive_IT(&huart2, &GSM_Rx, 1); 	// sprawdznie kolejnego znaku
					}
					else
					{
						HAL_UART_Receive_IT(&huart2, &GSM_Rx, 1); //czekaj na komunikat od GSM
					}
				}
				else
				{
					HAL_UART_Receive_IT(&huart2, &GSM_Rx, 1);
				}
			}
			else
			{
				HAL_UART_Receive_IT(&huart2, &GSM_Rx, 1);
			}
		}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM10)	//wykrycie timera zliczajecego co 10 sec
	{
		if(StrefaSzerokosc((char*)GPS_Rec_2,Szer_Gorna_Granica,Szer_Dolna_Granica) == 0
		||DlugoscSzerokosc((char*)GPS_Rec_2,Dl_prawo_Granica,Dl_lewo_Granica)== 0)	// sprawdzenie naruszenia strefy
		{
			GSM_send(NUMER,"\n\rLOKALIZATOR OPUSCIL WYZNACZONA STREFE!\n\r");
		}
	}
}

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	GPS_Rec_2 = (uint8_t*) malloc(68 * sizeof(uint8_t)); /* przyporzadkowanie pamieci dla stringa
	 przechowujacego ramke NMEA
	 */
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART6_UART_Init();
  MX_USART1_UART_Init();
  MX_TIM10_Init();
  MX_SPI1_Init();
  MX_USART2_UART_Init();
  MX_FATFS_Init();
  /* USER CODE BEGIN 2 */

  HAL_UART_Receive_IT(&huart1, &GPS_Check, 1); //rozpoczecie odbierania danych  z GPS
  HAL_UART_Receive_IT(&huart2, &GSM_Rx, 1);   //rozpoczecie odbierania danych  z GSM
  HAL_TIM_Base_Start_IT(&htim10);			 //rozpoczecie pracy timera

  /*zapisanie poczatowych punktow strefy w pamieci flash */
  /*
  HAL_FLASH_Unlock();
  if( EE_Init() != EE_OK)	//inicializacja
  {
	   	  char* information = "blad inicializacji\r\n";
	   	  int length = sprintf(information,"blad inicializacji\r\n");
	   	  HAL_UART_Transmit(&huart6, (uint8_t*) information,(uint16_t) length,10);
  }
  {
    	EE_WriteVariable(VirtAddVarTab[0],  '+');	//+ lub -
    	EE_WriteVariable(VirtAddVarTab[1],  5);
    	EE_WriteVariable(VirtAddVarTab[2],  1);
    	EE_WriteVariable(VirtAddVarTab[3],  0);
    	EE_WriteVariable(VirtAddVarTab[4],  0);
    	EE_WriteVariable(VirtAddVarTab[5],  0);
    	EE_WriteVariable(VirtAddVarTab[6],  0);
    	EE_WriteVariable(VirtAddVarTab[7],  0);
    	EE_WriteVariable(VirtAddVarTab[8],  0);
    	EE_WriteVariable(VirtAddVarTab[9],  0);
    	EE_WriteVariable(VirtAddVarTab[10], 'X'); //znak separacji pomiedzy kolejnymi punktami
  }
*/
    GSM_rec_set();	//inicializacja modulu GSM
   //Inicializacja karty
	fresult = f_mount(&FatFs, "", 1);
	fresult = f_open(&fil, "file.txt", FA_CREATE_ALWAYS | FA_WRITE);


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */




    while (1)
	{
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

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

  /**Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /**Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 100;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /**Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_HARD_OUTPUT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief TIM10 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM10_Init(void)
{

  /* USER CODE BEGIN TIM10_Init 0 */

  /* USER CODE END TIM10_Init 0 */

  /* USER CODE BEGIN TIM10_Init 1 */

  /* USER CODE END TIM10_Init 1 */
  htim10.Instance = TIM10;
  htim10.Init.Prescaler = 49999;
  htim10.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim10.Init.Period = 19999;
  htim10.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  if (HAL_TIM_Base_Init(&htim10) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM10_Init 2 */

  /* USER CODE END TIM10_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief USART6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART6_UART_Init(void)
{

  /* USER CODE BEGIN USART6_Init 0 */

  /* USER CODE END USART6_Init 0 */

  /* USER CODE BEGIN USART6_Init 1 */

  /* USER CODE END USART6_Init 1 */
  huart6.Instance = USART6;
  huart6.Init.BaudRate = 115200;
  huart6.Init.WordLength = UART_WORDLENGTH_8B;
  huart6.Init.StopBits = UART_STOPBITS_1;
  huart6.Init.Parity = UART_PARITY_NONE;
  huart6.Init.Mode = UART_MODE_TX_RX;
  huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart6.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart6) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART6_Init 2 */

  /* USER CODE END USART6_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pin : PA0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PD15 */
  GPIO_InitStruct.Pin = GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
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
	 tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
