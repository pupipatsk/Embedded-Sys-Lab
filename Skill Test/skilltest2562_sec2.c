// Skill Test Sec 2 2562
// 1. Make all lights blink every 150 ms (on 50 ms, off 100 ms)
// 2. push button TOGGLE (on 100 ms, off 50 ms)
// 3. hold to all light on and button dont respone anymore
// to push button anymore.

/* USER CODE BEGIN WHILE */

uint8_t state = 1;
uint8_t buttonState = GPIO_PIN_SET;
while (1)
{
	if (state == 1)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5 | GPIO_PIN_6, GPIO_PIN_SET); // LED on
		HAL_Delay(50);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5 | GPIO_PIN_6, GPIO_PIN_RESET); // LED off
		HAL_Delay(100);

		//	  		  if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET) {
		//	  			  state++;
		//	  			  // debouncing the button
		//	  			  while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET);
		//	  		  }
		// Debouncing
		if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET && buttonState == GPIO_PIN_SET)
		{
			HAL_Delay(50); // Debounce delay
			if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET)
				state++; // Increment state
		}
		buttonState = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13);
	}
	else if (state == 2)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5 | GPIO_PIN_6, GPIO_PIN_SET); // LED on
		HAL_Delay(100);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5 | GPIO_PIN_6, GPIO_PIN_RESET); // LED off
		HAL_Delay(50);

		//	  		  if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET) {
		//	  			  state++;
		//	  			  // debouncing the button
		//	  			  while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET);
		//	  		  }
		// Debouncing
		if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET && buttonState == GPIO_PIN_SET)
		{
			HAL_Delay(50); // Debounce delay
			if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET)
				state++; // Increment state
		}
		buttonState = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5 | GPIO_PIN_6, GPIO_PIN_SET); // All LEDs on
	}
}

// Debounce function
uint8_t buttonState = GPIO_PIN_SET;
if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET && buttonState == GPIO_PIN_SET)
{
	HAL_Delay(50); // Debounce delay
	if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET)
	{
		state++; // Increment state
		// stage controller
		if (state > 2)
			state = 0; // Reset state after the third press
	}
}
buttonState = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13);