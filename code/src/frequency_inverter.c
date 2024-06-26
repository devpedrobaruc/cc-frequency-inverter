#include "frequency_inverter.h"

double amplitude;

void configure_inverter(TIM_HandleTypeDef *htim, TIM_HandleTypeDef *htim_int)
{
    // Start PWM generation
    HAL_TIM_PWM_Start(htim, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(htim, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(htim, TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(htim, TIM_CHANNEL_4);

    // Configure timer to count microseconds for sine wave generation(0us to wave period)
    __HAL_RCC_TIM2_CLK_ENABLE();
    htim_int->Init.Prescaler = 1 / SINE_WAVE_FREQUENCY * (SystemCoreClock / (htim_int->Init.Period + 1));
    HAL_TIM_Base_Start(htim_int);

    // Calculate max amplitude of sine wave
    amplitude = ((1.0 / PWM_FREQUENCY) / (1.0 / (SystemCoreClock / htim->Init.Prescaler + 1)));
    amplitude *= 0.90;
}

double calculateSineWave(int freq, double time, double phase)
{
    return amplitude * sin(2 * M_PI * freq * time + phase);
}

void process_inverter()
{
    double time1 = ((double)TIM2->CNT) * ((TIM2->PSC + 1) / (double)SystemCoreClock);
    double sineWave1 = calculateSineWave(SINE_WAVE_FREQUENCY, time1, 0);
    double sineWave2 = calculateSineWave(SINE_WAVE_FREQUENCY, time1, 90);

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