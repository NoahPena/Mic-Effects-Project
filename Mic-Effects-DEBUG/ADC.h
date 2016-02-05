#ifndef ADC_H
#define ADC_H

#include "main.h"

void Initialize_ADC(void);
void EnableTimerInterrupt(void);
uint16_t readADC1(uint8_t channel);

#endif