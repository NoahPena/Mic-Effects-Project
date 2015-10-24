#include "main.h"
#include "FFT.h"
#include "ADC.h"

uint8_t isFull(void)
{
		return (inputIndex == FFT_INPUT_SIZE);
}

void resetTable(void) 
{
		inputIndex = 0;
		dataReady = 0;
		NVIC_EnableIRQ(TIM2_IRQn);
}

void insertValueFloat(float32_t data)
{
		if(dataReady)
		{
				return;
		}
		
		input[inputIndex] = data;
		inputIndex++;
		input[inputIndex] = 0;
		inputIndex++;
	
		if(inputIndex >= FFT_INPUT_SIZE)
		{
				NVIC_DisableIRQ(TIM2_IRQn);
				computeFFT();
				//resetTable();
		}
}

void insertValue(float32_t data)
{
		if(dataReady)
		{
				return;
		}
		
		input[inputIndex] = data;
		inputIndex++;
		input[inputIndex] = 0;
		inputIndex++;
	
		if(inputIndex >= FFT_INPUT_SIZE)
		{
				NVIC_DisableIRQ(TIM2_IRQn);
				computeFFT();
				//resetTable();
		}
}
