// ---------- skilltest2561 ----------
// Implement the following:
// 1 The indicator LEDs blinks every one second (500ms on, 500ms off) after reset
// 2 Pushing the USER button the first time will change the state such that only one LED is blinking. ( choose
// any)
// 3 Pushing the USER button the second time will change the state such that only two LEDs are blinking.
// 4 Pushing the USER button the third time will go back to the first state after reset

// Setup: HSE clock, GPIO mode Rising edge, NVIC 2 bit 2

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint16_t state = 0;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);
	HAL_Delay(100);

	if (state == 0)
		state = 1;
	else if (state == 1)
		state = 2;
	else
		state = 0;

	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);
}

while (1)
{
	if (state == 0)
	{
		// HAL_GPIO_WritePin: Set Status
		// off: GPIO_PIN_RESET, on: GPIO_PIN_SET
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5 | GPIO_PIN_6, GPIO_PIN_RESET); // All LEDs off
		// debouncing the button
		while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET)
			;
	}
	else if (state == 1)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET); // Turn off LED
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
		HAL_Delay(500); // Delay for 500ms
		// debouncing the button
		while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET)
			;
	}
	else if (state == 2)
	{
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5 | GPIO_PIN_6);
		HAL_Delay(500);
		// debouncing the button
		while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET)
			;
	}