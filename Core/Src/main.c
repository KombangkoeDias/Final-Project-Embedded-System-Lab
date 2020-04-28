/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
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
TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
char StartString[] = "Welcome to the HangMan game!! Choose the option that you want :\r\n [1] Start \r\n [2] How to play?? \r\n Choose one (type 1 or 2): ";
char HardVocabularies[50][25] = {
		"abysmal", "antithetical", "apocryphal", "begrudge", "behoove", "belligerent", "capricious", "chivalrous", "commensurate", "conundrum",
		"denigrate", "dilapidated", "efficacious", "evenhanded", "exegesis", "forlorn", "frugal", "garrulous", "hackneyed", "idiosyncrasy",
		"imbroglio", "incorrigible", "inscrutable", "intransigent", "juggernaut", "largesse", "lascivious", "malapropism", "malfeasance", "malodorous",
		"misogynist", "obsequious", "overweening", "parsimonious", "pejorative", "piquant", "pollyannaish", "prescience", "presumptuous", "prevaricate",
		"profligate", "querulous", "restive", "saturnine", "soporific", "supercilious", "sycophant", "tantamount", "veracious", "vicissitude"
};

char MediumVocabularies[50][25] = {

		"anomaly", "arduous", "blatant", "strenuous", "bombard", "concensus", "confront", "disparate", "disperse", "dwindle",
		"emphasize", "exacerbate", "exhaustive", "foremost", "forthcoming", "grueling", "impetus", "implausible", "indignant", "inexorable",
		"infinitesimal", "innocuous", "intersperse", "intervene", "jeopardy", "juxtapose", "notwithstanding", "nuance", "overlook", "overshadow",
		"overwhelm", "predominant", "preposterous", "prevalent", "profound", "propagate", "propulsion", "rebound", "remnant", "ruthless",
		"salvage", "subsequent", "substitute", "subsume", "superfluous", "transitory", "trivial", "undermine", "upheaval", "vicarious"
};


char EasyVocularies[50][25] = {

		"absolve", "anxious", "apparent", "aspire", "bashful", "blossom", "bold", "catastrophe", "complain", "contrast",
		"crave", "criticize", "crowded", "dangerous", "deadly", "debate", "degenerate", "demote", "deport", "distinct",
		"disturb", "endless", "enormous", "escalate", "exile", "exterminate", "fearless", "forever", "fruitful", "immense",
		"intelligent", "interesting", "large", "minute", "obsessed", "pacific", "partiality", "perceive", "poisonous", "pressing",
		"pursue", "reckless", "relegate", "renowned", "request", "shade", "stalk", "tiresome", "transparent", "typical"
};

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
char pData[1]; //hold the user's input
char word[25]; //hold the random word.
char usedCharacter[] = "                          "; //used characters
int start = 0; //start by pushing the button
int state = 0; //state of the program
int mode = 0; //mode of the game (easy,medium,hard)
int Timeout = 1000000;
int size = 0; //size of the random word

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	//HAL_UART_Transmit(&huart2, StartString, sizeof(StartString), 1000000);
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
  MX_TIM2_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  //HAL_UART_Transmit(&huart2, StartString, sizeof(StartString), 1000000);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  while (1)
  {
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
	if (!HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13)){
		buttonPushStart();
	}
	if (state == 1){
		if (HAL_UART_Receive(&huart2, pData, 1, Timeout) == HAL_OK){
			if (pData[0] == '1'){
				startGame();
			}
			else if (pData[0] == '2'){
				howToPlay();
			}
			else{
				error1();
			}
		}
	}
	if (state == 2){
		if (HAL_UART_Receive(&huart2, pData, 1, Timeout) == HAL_OK){
			if (pData[0] == '1'){
				startEasy();
			}
			else if (pData[0] == '2'){
				startMedium();
			}
			else if (pData[0] == '3'){
				startHard();
			}
			else{
				error2();
			}
		}
	}
	if (state == 3){
		startNow();
	}
	if (state == 4){
		firstTurn();
	}
	if (state == 5){
		continueTurn();
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
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 8400;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 50;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

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
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void setVocabularySets(char set[50][25]){
	state = 3;
	int k = TIM2->CNT %50;
	for (int i = 0; i < 25; ++i){
		if (set[k][i] != NULL){
			size++;
		}
	}
	//size = sizeof(EasyVocularies[k]);
	for (int i = 0; i < size; ++i){
		word[i] = set[k][i];
	}
	for (int i = size; i < 25; ++i){
		word[i] = NULL;
	}
	//HAL_UART_Transmit(&huart2, word, sizeof(word), Timeout);
}

void startGame(){
	state = 2;
	char Start[] = "\r\n \r\n Now starting the game! Are you ready? How strong a man are you? Choose one Level: \r\n [1] Easy \r\n [2] Medium \r\n [3] Hard \r\n (type 1 or 2 or 3): ";
	HAL_UART_Transmit(&huart2, Start, sizeof(Start), Timeout);
	//HAL_UART_Transmit(&huart2, pData, 1, 1000000);
}

void howToPlay(){
	state = 1;
	char How[] = "\r\n \r\n This is how you are going to play this game: \r\n [1] You guess the character that you think is in the word \r\n [2] You only have limited guess so choose well \r\n [3] of course if you guess all correct character before the quota runs out, you win!";
	HAL_UART_Transmit(&huart2, How, sizeof(How), Timeout);
	//HAL_UART_Transmit(&huart2, pData, 1, 1000000);
	HAL_Delay(2000);
	char anoStart[] = "\r\n \r\n Already familiar with the rule? \r\n Now let's Choose the option that you want :\r\n [1] Start \r\n [2] How to play?? \r\n Choose one (type 1 or 2):";
	HAL_UART_Transmit(&huart2, anoStart , sizeof(anoStart), Timeout);
}

void error1(){
	state = 1;
	char Error[] = "\r\n \r\n Such a strange person you are, type only 1 or 2 !!!";
	HAL_UART_Transmit(&huart2, Error, sizeof(Error), Timeout);
	char TryAgain[] = "\r\n Now Try again, remember, type only 1 or 2 !!!!";
	HAL_UART_Transmit(&huart2, TryAgain, sizeof(TryAgain), Timeout);
}

void buttonPushStart(){
	while(!HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13));
	if (start == 0){
		start = 1;
		state = 1;
		HAL_UART_Transmit(&huart2, StartString , sizeof(StartString), Timeout);
	}
}

void startEasy(){
	char easy[] = " \r\n \r\n Always start small right? Let's see if you can defeat the easiest level! \r\n";
	HAL_UART_Transmit(&huart2, easy , sizeof(easy), Timeout);
	setVocabularySets(EasyVocularies);
	mode = 1;
}

void startMedium(){
	char middle[] = "\r\n \r\n Like to choose things in the middle ha? These medium-level vocabularies are not so easy as you would think! \r\n";
	HAL_UART_Transmit(&huart2, middle , sizeof(middle), Timeout);
	setVocabularySets(MediumVocabularies);
	mode = 2;
}

void startHard(){
	char Hard[] = "\r\n \r\n Such a brave lad you are!!! This is the toughest of all the levels, don't expect it to be your level!! \r\n";
	HAL_UART_Transmit(&huart2, Hard , sizeof(Hard), Timeout);
	setVocabularySets(HardVocabularies);
	mode = 3;
}
char myword[25];
void error2(){
	state = 2;
	char Error[] = "\r\n \r\n Such a strange person you are, type only 1, 2, or 3 !!!";
	HAL_UART_Transmit(&huart2, Error, sizeof(Error), Timeout);
	char TryAgain[] = "\r\n Now Try again, remember, type only 1, 2, or 3 !!!!";
	HAL_UART_Transmit(&huart2, TryAgain, sizeof(TryAgain), Timeout);
}
void startNow(){
	char StartNow[] = "\r\n \r\n Here are the clue and tips to your words \r\n [1] Your word has ";
	char Continue[2];
	state = 4;
	char EndNow[] = " characters... \r\n [2] try typing vowels first (a,e,i,o,u) \r\n\r\n Now let's get started, shall we? \r\n \r\n ";
	HAL_UART_Transmit(&huart2, StartNow, sizeof(StartNow), Timeout);
	sprintf(Continue,"%d", size);
	HAL_UART_Transmit(&huart2, Continue, sizeof(Continue), Timeout);
	HAL_UART_Transmit(&huart2, EndNow, sizeof(EndNow), Timeout);
}

void firstTurn(){
	state = 5;
	char underscore[size*2];
	char stretchedword[size*2];
	for (int i = 0; i < size*2; ++i){
		if (i % 2 == 0){
			underscore[i] = '_';
			stretchedword[i] = word[i/2];
			myword[i] = '1';
		}
		else{
			underscore[i] = ' ';
			stretchedword[i] = ' ';
			myword[i] = '1';
		}
	}

	//HAL_UART_Transmit(&huart2, stretchedword, size*2, Timeout);
	HAL_UART_Transmit(&huart2, myword, size*2, Timeout);
	HAL_UART_Transmit(&huart2, "\r\n", 4, Timeout);
	HAL_UART_Transmit(&huart2, " ", 1, Timeout);
	HAL_UART_Transmit(&huart2, underscore, size*2, Timeout);
	char after[] = "\r\n \r\n Now choose (or guess) a character that you think is in this word... : ";
	char format[] = "(%d characters) used characters : ";
	char HereIsYourWords[sizeof(format)-1];
	sprintf(HereIsYourWords,format, size);
	HAL_UART_Transmit(&huart2, HereIsYourWords, sizeof(HereIsYourWords), Timeout);
	HAL_UART_Transmit(&huart2, usedCharacter, sizeof(usedCharacter), Timeout);
	HAL_UART_Transmit(&huart2, after, sizeof(after), Timeout);
}

void nextTurn(){
	char underscore[size*2];
	char stretchedword[size*2];
	for (int i = 0; i < size*2; ++i){
		if (i % 2 == 0){
			underscore[i] = '_';
			stretchedword[i] = word[i/2];
		}
		else{
			underscore[i] = ' ';
			stretchedword[i] = ' ';
		}
	}

	//HAL_UART_Transmit(&huart2, stretchedword, size*2, Timeout);
	HAL_UART_Transmit(&huart2, "\r\n\r\n", 8, Timeout);
	HAL_UART_Transmit(&huart2, " ", 1, Timeout);
	HAL_UART_Transmit(&huart2, myword, size*2, Timeout);
	HAL_UART_Transmit(&huart2, "\r\n", 4, Timeout);
	HAL_UART_Transmit(&huart2, " ", 1, Timeout);
	HAL_UART_Transmit(&huart2, underscore, size*2, Timeout);
	char after[] = "\r\n \r\n Now choose (or guess) another character that you think is in this word... : ";
	char format[] = "(%d characters) used characters : ";
	char HereIsYourWords[sizeof(format)-1];
	sprintf(HereIsYourWords,format, size);
	HAL_UART_Transmit(&huart2, HereIsYourWords, sizeof(HereIsYourWords), Timeout);
	HAL_UART_Transmit(&huart2, usedCharacter, sizeof(usedCharacter), Timeout);
	HAL_UART_Transmit(&huart2, after, sizeof(after), Timeout);
}

void continueTurn(){
	if (HAL_UART_Receive(&huart2, pData, 1, Timeout) == HAL_OK){
		int check = 0;
		if (!isdigit(pData[0])){
			for (int i = 0; i < sizeof(alphabet); ++i){
				if (pData[0] == alphabet[i]){
					usedCharacter[i] = pData[0];
					check = 1;
				}
			}
			nextTurn();
			if (check == 0){
				char Error[] = "\r\n\r\n The word does not have this character for sure!!! \r\n Have you read the how to play guide? \r\n The word does not contain the strange symbol that you type!! \r\n The word contains only a-z";
				char TryAgain[] = "\r\n Now Try Again!!!";
				HAL_UART_Transmit(&huart2, Error, sizeof(Error), Timeout);
				HAL_UART_Transmit(&huart2, TryAgain, sizeof(TryAgain), Timeout);
				nextTurn();
			}
		}
		else{
			char Error[] = "\r\n\r\n The word does not have this character for sure!!! \r\n Have you read the how to play guide? \r\n The word does not contain numbers!! \r\n The word contains only a-z";
			char TryAgain[] = "\r\n Now Try Again!!!";
			HAL_UART_Transmit(&huart2, Error, sizeof(Error), Timeout);
			HAL_UART_Transmit(&huart2, TryAgain, sizeof(TryAgain), Timeout);
			nextTurn();
		}

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
