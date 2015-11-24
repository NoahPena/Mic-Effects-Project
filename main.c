#include "main.h"
#include "FFT.h"
#include "ADC.h"
#include "UART.h"
#include "InputData.h"

#include <stdio.h>

float32_t input[FFT_INPUT_SIZE];
float32_t output[FFT_SIZE];

uint16_t inputIndex = 0;
uint16_t outputIndex = 0;

uint8_t dataReady = 0;

uint32_t divisor = 3809;

uint32_t currentFrequencyBin = 0;

void InitializeSystem(void)
{
		
		Initialize_ADC();
		Initialize_UART(9600);
		GPIOB->ODR |= 0x02;
		//EnableTimerInterrupt();
		//resetTable();
}

void SetupDebugLeds(void)
{
		GPIO_InitTypeDef gpio;
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	
		gpio.GPIO_OType = GPIO_OType_PP;
		gpio.GPIO_Pin = 0x02;
		gpio.GPIO_Mode = GPIO_Mode_OUT;
		gpio.GPIO_PuPd = GPIO_PuPd_UP;
		gpio.GPIO_Speed = GPIO_Speed_100MHz;
	
		GPIO_Init(GPIOB, &gpio);
	
		GPIOB->ODR = 0x00;
}

void SetupDebugButtons(void)
{
		GPIO_InitTypeDef gpio;
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	
		gpio.GPIO_OType = GPIO_OType_PP;
		gpio.GPIO_Pin = 0x01;
		gpio.GPIO_Mode = GPIO_Mode_IN;
		gpio.GPIO_PuPd = GPIO_PuPd_UP;
		gpio.GPIO_Speed = GPIO_Speed_100MHz;
	
		GPIO_Init(GPIOB, &gpio);
}

int main(void)
{
	char str[10];
	char status = 0;
	
	uint16_t data = 0;
	
	SetupDebugLeds();
	SetupDebugButtons();
	
	
	//GPIOB->ODR |= 0x02;

//	do
//	{
//		status = GPIO_ReadInputDataBit(GPIOB, 0x01);
//		//UART_puts("Start\n");
//	} while(status == 0);

	
//	while(!(GPIOB->IDR & 0x01))
//	{
//		UART_puts("Start\n");
//	}
	InitializeSystem();
	
	UART_puts("Start\n");
	
	GPIOB->ODR |= 0x02;
	
	while(1)
	{
			data = readADC1(10);
			sprintf(str, "%d\n", data);
			UART_puts(str);
	}
		
	while(1)
	{
			if(dataReady)
			{
					currentFrequencyBin = getFrequency();
					sprintf(str, "%d\n", currentFrequencyBin);
					UART_puts(str);
			}
			else
			{
					currentFrequencyBin = 0;
					//UART_puts("no\n");
			}
	}
}
