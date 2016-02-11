#ifndef DAC_H
#define DAC_H

#include "main.h"

#define DAC_MIN 0
#define DAC_MID (1 << 9)
#define DAC_MAX ((1 << 12) - 1)

void DAC2_init(void);
void DAC2_set(uint16_t);

#endif
