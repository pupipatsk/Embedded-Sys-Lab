// ---------- Lab4 - 01 ----------
// DIM an LED by increasing the duty cycle from 0% duty cycle
// by 1% every 0.01 second. When the PWM reaches the 100% duty cycle,
// decrease the duty cycle by 1% every 0.01 second to 0% duty cycle.
// Repeat the following step forever. (use 100 microseconds period for PWM)

// CLKconfig -> TIM2 -> CLKsource: Internal -> PWM CH1 -> Adjust PSC&CP
// -> Auto-reload preload: Enable -> PWM Generation Channel 1 -> Adj Pulse

/* USER CODE BEGIN 2 */
HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
TIM2->CCR1 = 50;
// TIMx->CNT - Clock counter // TIMx->PSC - Prescaler values
// TIMx->ARR - Period values // TIMx->CCR1 – PWM for channel 1
/* USER CODE END 2 */
while (1)
{
    for (int i = 0; i < 100; i++)
    {
        TIM2->CCR1 = i;
        HAL_Delay(10);
    }
    for (int i = 100; i >= 0; i--)
    {
        TIM2->CCR1 = i;
        HAL_Delay(10);
    }
}

// ---------- Lab4 - 02 ----------
// Connect LDR read the value from LDR and display serial terminal via UART

// 2.1 Setup a PIN to accept an analog input: IOC -> Analog
// pin in INx // ADC1_IN0 is corresponding to PIN PA0.

/* USER CODE BEGIN 2 */
int adcval = 0;
char buf[256];
/* USER CODE END 2 */
while (1)
{
    HAL_ADC_Start(&hadc1);
    // Wait for 1000ms or when the conversion is finished.
    if (HAL_ADC_PollForConversion(&hadc1, 1000) == HAL_OK)
    {
        // Read the ADC value
        adcval = HAL_ADC_GetValue(&hadc1);
        // Write integer to buffer
        sprintf(buf, "%d\r\n", adcval);
        // Transmitted with UART
        HAL_UART_Transmit(&huart2, buf, strlen(buf), 1000);
    }
}

// ---------- Lab4 - 03 ----------
// green LED brightness with PWM from the value of LDR.
// PWM Duty Cycle = ( 1 – (C / P) ) * 100 %
// C = (max environment brightness) – (current environment brightness)
// P = (max environment brightness) - (min environment brightness)

/* Initialize all configured peripherals */
MX_GPIO_Init();
MX_USART2_UART_Init();
MX_ADC1_Init();
MX_TIM2_Init();
/* USER CODE BEGIN 2 */
HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
TIM2->CCR1 = 0;
int adcval = 0;
double c = 700, p = 150;
char buf[256];
/* USER CODE END 2 */
while (1)
{
    HAL_ADC_Start(&hadc1);
    if (HAL_ADC_PollForConversion(&hadc1, 1000) == HAL_OK)
    {
        adcval = HAL_ADC_GetValue(&hadc1);
        c = 700 - adcval;
        p = 700 - 150;
        int b = (1 - (c / p)) * 100;
        TIM2->CCR1 = b;
        sprintf(buf, "%d\r\n", b);
        HAL_UART_Transmit(&huart2, buf, strlen(buf), 1000);
    }
}