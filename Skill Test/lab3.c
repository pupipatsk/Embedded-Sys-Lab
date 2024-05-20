// ---------- Lab3 - 01 ----------

// GPIO -> PC13: GPIO Mode: Rising
// NVIC -> 2bit -> EXTI interupt enable priority 2

/* USER CODE BEGIN 0 */
uint16_t blinktime = 200;
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
  HAL_Delay(100);
  while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET);
  if (blinktime == 200) blinktime = 1000;
  else if (blinktime == 1000) blinktime = 5000;
  else blinktime = 200;
  __HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);
}
/* USER CODE END 0 */
/* Infinite loop */
/* USER CODE BEGIN WHILE */
while (1)
{
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
	HAL_Delay(blinkTime);
}

// ---------- Lab3 - 02 ----------

Desire Time Freq = SysClock / ( (PSC+1)*(CP+1) )

// ---------- Lab3 - 03 ----------

// UART Interupt Timer
// ClkConfig: HSE -> 100 MHz
// Timers: Tim2 Tim3 Tim4 -> ClkSource: Internal
// NVIC: Tim2 Tim3 Tim4 global interupt enable
// adjust PSC&CP: Period 500ms: 4999 9999, 490.5ms: 4904 9999, 999.9ms: 9998 9999

/* USER CODE BEGIN 0 */
uint8_t green_cnt = 0; // PA5
uint8_t red_cnt = 0; // PA6
// Timer interrupt handlers (controller)
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim){
	if (htim->Instance == TIM2){
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
		green_cnt++;
	}
	else if (htim->Instance == TIM3){
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_6);
		red_cnt++;
	}
	else if (htim->Instance == TIM4){
//		HAL_UART_Transmit(&huart2, &green_cnt, sizeof(green_cnt), HAL_MAX_DELAY);
//		HAL_UART_Transmit(&huart2, &red_cnt, sizeof(red_cnt), HAL_MAX_DELAY);
		char green_cnt_str[10];
		char red_cnt_str[10];
//		sprintf(green_cnt_str, "%d", green_cnt/2);
//		sprintf(rS, "%d", red_cnt/2);
		itoa(green_cnt/2, green_cnt_str, 10); // Convert green_cnt to ASCII string
		itoa(red_cnt/2, red_cnt_str, 10);   // Convert red_cnt to ASCII string
		HAL_UART_Transmit(&huart2, green_cnt_str, strlen(green_cnt_str), 10);
		HAL_UART_Transmit(&huart2," " , 1, 10);
		HAL_UART_Transmit(&huart2, red_cnt_str, strlen(red_cnt_str), 10);
		HAL_UART_Transmit(&huart2,"\r\n" , 2, 10); // \r: cursor to begin of line, \n: new line
	}
}
/* USER CODE END 0 */
/* USER CODE BEGIN 2 */
  // Start timers
  	  HAL_TIM_Base_Start_IT(&htim2);
      HAL_TIM_Base_Start_IT(&htim3);
      HAL_TIM_Base_Start_IT(&htim4);
/* USER CODE END 2 */


// ---------- Lab3 - 04 ----------
// echo back (transmit the receive data) USART2 interrupt
// NVIC -> UART2 global interupt prio2

/* USER CODE BEGIN 2 */
  	  HAL_UART_Receive_IT(&huart2, &ch, 1);
/* USER CODE END 2 */
/* USER CODE BEGIN 0 */
char ch;
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	HAL_UART_Transmit(&huart2, &ch, 1, 1000);
	HAL_UART_Receive_IT(&huart2, &ch, 1);
}
/* USER CODE END 0 */