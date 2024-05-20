// ---------- skill test 2566 01 ----------

/* USER CODE BEGIN 0 */
char input[32];
int index = 0;
char c;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM3)
    {
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
    }
}
/* USER CODE END 0 */
/* USER CODE BEGIN 2 */
HAL_TIM_Base_Start_IT(&htim3);
/* USER CODE END 2 */
while (1)
{
    if (HAL_UART_Receive(&huart2, (uint8_t *)&c, 1, HAL_MAX_DELAY) == HAL_OK)
    {
        HAL_UART_Transmit(&huart2, (uint8_t *)&c, 1, HAL_MAX_DELAY);

        if (c == '\r' || c == '\n')
        {
            HAL_UART_Transmit(&huart2, (uint8_t *)"\r\n", 2, HAL_MAX_DELAY);
            for (int i = index - 1; i >= 0; i--)
            {
                HAL_UART_Transmit(&huart2, (uint8_t *)&input[i], 1, HAL_MAX_DELAY);
            }
            HAL_UART_Transmit(&huart2, (uint8_t *)"\r\n", 2, HAL_MAX_DELAY);
            index = 0;
        }
        else
        {
            input[index++] = c;
            if (index >= sizeof(input))
            {
                index = 0;
            }
        }
    }
}

// ---------- skill test 2566 02 ----------

/* USER CODE BEGIN 0 */
int density = 0;
int timer_counter = 0;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    HAL_Delay(100);
    density += 10;
    density = density % 100;
    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM2)
    {
        timer_counter++;
        if (timer_counter == 1000)
        { // 10 seconds have elapsed
            timer_counter = 0;
            density = 0; // Reset the density variable
        }
    }
}
/* USER CODE END 0 */
/* USER CODE BEGIN 2 */
HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
TIM2->CCR1 = 50;
/* USER CODE END 2 */
while (1)
{
    TIM2->CCR1 = density;
}