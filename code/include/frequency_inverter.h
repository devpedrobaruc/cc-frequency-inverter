#pragma once

#include "main.h"
#include <stdbool.h>
#include <math.h>

#define SINE_WAVE_FREQUENCY 100
#define PWM_FREQUENCY 30000.0

void configure_inverter(TIM_HandleTypeDef *htim, TIM_HandleTypeDef *htim_int);

void process_inverter();

double calculateSineWave(int freq, double time, double phase);