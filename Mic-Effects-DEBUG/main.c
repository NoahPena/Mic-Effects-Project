#include "main.h"
#include "ADC.h"

float32_t input[FFT_INPUT_SIZE];
float32_t output[FFT_SIZE];

uint16_t inputIndex = 0;
uint16_t outputIndex = 0;

uint8_t dataReady = 0;

uint32_t divisor = 3809;

uint32_t currentFrequencyBin = 0;


void InitializeClocks(void)
{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1ENR_GPIOCEN, ENABLE);
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

void Initialize_System(void)
{
		InitializeClocks();
		SetupDebugLEDS();
		Initialize_ADC();
		EnableTimerInterrupt();
}

int main(void)
{
		Initialize_System();
	
		GPIOD->ODR |= 0x8000;
	
		while(1)
		{
			
		}
}

