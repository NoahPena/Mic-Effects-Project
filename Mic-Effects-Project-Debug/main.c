#include "main.h"
#include "ADC.h"
#include "DAC.h"

float32_t input[FFT_INPUT_SIZE];
float32_t output[FFT_SIZE];

uint16_t inputIndex = 0;
uint16_t outputIndex = 0;

uint8_t dataReady = 0;

uint32_t divisor = 3809;

uint32_t currentFrequencyBin = 0;

void IntializeClocks(void)
{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
}

void SetupDebugLEDS(void)
{
		GPIO_InitTypeDef gpio;
	
		gpio.GPIO_OType = GPIO_OType_PP;
		gpio.GPIO_Pin = 0xF000;
		gpio.GPIO_Mode = GPIO_Mode_OUT;
		gpio.GPIO_PuPd = GPIO_PuPd_UP;
		gpio.GPIO_Speed = GPIO_Speed_100MHz;
	
		GPIO_Init(GPIOD, &gpio);
		
		GPIOD->ODR = 0x0000;
}

void InitializeSystem(void)
{
		IntializeClocks();
		SetupDebugLEDS();
		Initialize_ADC();
		Initialize_DAC();
		
		EnableTimerInterrupt();
}

int main(void)
{
		InitializeSystem();
	
		while(1)
		{
			
		}
}
