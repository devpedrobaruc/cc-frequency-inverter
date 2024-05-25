#include "frequency_inverter.h"

void configure_inverter(TIM_HandleTypeDef *htim, TIM_HandleTypeDef *htim_int)
{
    HAL_TIM_PWM_Start(htim, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(htim, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(htim, TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(htim, TIM_CHANNEL_4);

    __HAL_RCC_TIM2_CLK_ENABLE();
    htim_int->Init.Prescaler = 1 / FREQUENCY * (SystemCoreClock / (htim_int->Init.Period + 1));
    HAL_TIM_Base_Start(htim_int);
}

double calculateSineWave(int freq, double time, double amplitude, double phase)
{
    return amplitude * sin(2 * M_PI * freq * time + phase);
}

void process_inverter()
{
    double time1 = ((double)TIM2->CNT) * ((TIM2->PSC + 1) / (double)SystemCoreClock);
    double sineWave1 = calculateSineWave(FREQUENCY, time1, MAX_DUTY_CYCLE - (MAX_DUTY_CYCLE * 0.10), 0);
    double sineWave2 = calculateSineWave(FREQUENCY, time1, MAX_DUTY_CYCLE - (MAX_DUTY_CYCLE * 0.10), 90);

    if (sineWave1 < 0)
    {
        sineWave1 = sineWave1 * -1.0;
        TIM1->CCR1 = 0;
        TIM1->CCR2 = sineWave1;
    }
    else
    {
        TIM1->CCR1 = sineWave1;
        TIM1->CCR2 = 0;
    }

    if (sineWave2 < 0)
    {
        sineWave2 = sineWave2 * -1.0;
        TIM1->CCR3 = 0;
        TIM1->CCR4 = sineWave2;
    }
    else
    {
        TIM1->CCR3 = sineWave2;
        TIM1->CCR4 = 0;
    }

    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
}