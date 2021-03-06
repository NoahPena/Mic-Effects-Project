#ifndef MAIN_H
#define MAIN_H

#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_adc.h"
#include "stm32f4xx_tim.h"
#include "misc.h"

#include "arm_math.h"
#include "arm_const_structs.h"

#define FFT_SIZE 1024
#define FFT_INPUT_SIZE (FFT_SIZE * 2)

extern float32_t input[FFT_INPUT_SIZE];
extern float32_t output[FFT_SIZE];

extern uint16_t inputIndex;
extern uint16_t outputIndex;

extern uint8_t dataReady;

extern uint32_t divisor;

extern uint32_t currentFrequencyBin;

#endif
