#ifndef UART_H
#define UART_H

#include <stdint.h>

void Initialize_UART(uint32_t);
void UART_puts(volatile char*);

#endif
