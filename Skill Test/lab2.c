// ---------- Lab2 - 01 & 02 ----------
// blink (on/off) with a period of 0.2 sec. for an on board LED
// blink (on/off) with a period of 0.2 sec. for an external LED

/* Infinite loop */
/* USER CODE BEGIN WHILE */
while (1)
{
	HAL_Delay(100);
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
	/* USER CODE END WHILE */
	/* USER CODE BEGIN 3 */
}
/* USER CODE END 3 */

// ---------- Lab2 - 03 ----------
// toggle an LED (on/off) with pushing USER push-button. (Debouching is required)

while (1)
{
	// blue button(PC13) is pressed(GPIO_PIN_RESET state)
	if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET)
	{
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
		HAL_Delay(100);
		// debouncing the button
		while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET)
			;
	}

	// ---------- Lab2 - 04 ----------
	// communicate UART, serial terminal
	// screen /dev/tty.usbmodem11203 115200, onclr
	// quit: ctrl + A then ctrl + \

	uint8_t ch;
	while (1)
	{
		if (HAL_UART_Receive(&huart2, &ch, 1, 100) == HAL_OK)
		{
			HAL_UART_Transmit(&huart2, &ch, 1, 100);
		}

		// ---------- Lab2 - 05 ----------
		// toggle an LED status (on/off) with commands via serial console.
		// (Type “on” or “off” then press Enter to on or off the LED

		/* Infinite loop */
		/* USER CODE BEGIN WHILE */
		int idx = 0;
		uint8_t ch;
		uint8_t buf[256];
		while (1)
		{
			if (HAL_UART_Receive(&huart2, buf + idx, 1, 1000) == HAL_OK)
			{
				HAL_UART_Transmit(&huart2, buf + idx, 1, 1000);
				if (buf[0] == 'o' && buf[1] == 'n' && buf[2] == '\r' && ch != 1)
				{
					HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
					HAL_Delay(100);
					ch = 1;
				}
				else if (buf[0] == 'o' && buf[1] == 'f' && buf[2] == 'f' && buf[3] == '\r' && ch != 0)
				{
					HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
					HAL_Delay(100);
					ch = 0;
				}
				if (buf[idx] == '\r')
				{
					idx = 0;
					buf[2] = '0';
					buf[3] = '0';
				}
				else
				{
					idx++;
				}
			}
		}