#pragma once

#include "main.h"
#include <stdbool.h>
#include <math.h>

#define FREQUENCY 100
#define AMPLITUDE ((1.0 / 30000.0) / (1.0 / (8000000.0 / 8.0)))

void configure_inverter(TIM_HandleTypeDef *htim, TIM_HandleTypeDef *htim_int);

void process_inverter();

double calculateSineWave(int freq, double time, double amplitude, double phase);