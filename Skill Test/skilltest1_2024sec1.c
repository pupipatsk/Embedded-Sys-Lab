// Real Skill Test 1 sec 1 2024
// Print "6532142421" individual by pressing blue button

/* USER CODE BEGIN 2 */
char sequence[10] = "6532142421"; // array of char size 10
uint8_t index = 0;
uint8_t digit;
/* USER CODE END 2 */
while (1)
{
  if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET)
  {
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5); // Show status
    // Debounce delay
    HAL_Delay(100);
    while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET)
      ;

    // char digit[2];
    digit = sequence[index];
    // digit[1] = '\0';
    HAL_UART_Transmit(&huart2, &digit, 1, 1000); // Print the digit over UART
                                                 // Print newline
    if (index == 9)
      HAL_UART_Transmit(&huart2, (uint8_t *)"\n", 1, HAL_MAX_DELAY);

    // Increment index and loop back to 0 after reaching the end
    index = (index + 1) % sizeof(sequence);
  }
}