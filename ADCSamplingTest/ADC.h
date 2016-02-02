#ifndef ADC_H
#define ADC_H

#include <stdint.h>
#include <stdio.h>

void InitializeTimer(void);
void EnableTimerInterrupt(void);
void Initialize_ADC(void);
uint16_t readADC1(uint8_t channel);
void TIM2_IRQHandler(void);

#endif
