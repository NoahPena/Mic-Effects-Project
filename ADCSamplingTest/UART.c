#include "UART.h"

#include "stm32f4xx_gpio.h"
#include "stm32f4xx_usart.h"

void Initialize_UART(uint32_t baudrate)
{
		GPIO_InitTypeDef gpio;
		USART_InitTypeDef USART_InitStruct;
	
		gpio.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
		gpio.GPIO_Mode = GPIO_Mode_AF;
		gpio.GPIO_OType = GPIO_OType_PP;
		gpio.GPIO_PuPd = GPIO_PuPd_UP;
		gpio.GPIO_Speed = GPIO_Speed_100MHz;
	
		GPIO_Init(GPIOB, &gpio);
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_USART1);
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1);
	
		USART_InitStruct.USART_BaudRate = baudrate;
		USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
		USART_InitStruct.USART_Parity = USART_Parity_No;
		USART_InitStruct.USART_StopBits = USART_StopBits_1;
		USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	
		USART_Init(USART1, &USART_InitStruct);
		USART_Cmd(USART1, ENABLE);
}

void UART_puts(volatile char *s)
{
		while(*s)
		{
				while(!(USART1->SR & 0x40));
				USART_SendData(USART1, *s);
				*s++;
		}
}
