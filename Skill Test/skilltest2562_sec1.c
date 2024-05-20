// ---------- Skill Test Sec 1 2562 ----------
// 1. Make red and green lights blink every ms.
// 2. Use user push button to to make red and green lights blink every ms.
// 3. Hold push button at least
// push button anymore.

/* USER CODE BEGIN WHILE */
uint8_t state = 1;

while (1)
{
	if (state == 1)
	{
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5 | GPIO_PIN_6);
		HAL_Delay(75); // Delay for 75ms
		if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET)
		{
			state++;
			// debouncing the button
			while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET)
				;
		}
	}
	else if (state == 2)
	{
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5 | GPIO_PIN_6);
		HAL_Delay(15); // Delay for 75ms
		if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET)
		{
			state++;
			// debouncing the button
			while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET)
				;
		}
	}
	else
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5 | GPIO_PIN_6, GPIO_PIN_RESET); // All LEDs off
	}
}