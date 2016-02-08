#include "DAC.h"

void Initialize_DAC(void)
{
		GPIO_InitTypeDef gpio;
		DAC_InitTypeDef DAC_InitStruct;
	
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
	
		gpio.GPIO_Pin = 0x30;
		gpio.GPIO_Mode = GPIO_Mode_AN;
		gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_Init(GPIOA, &gpio);
	
		DAC_InitStruct.DAC_Trigger = DAC_Trigger_None;
		DAC_InitStruct.DAC_WaveGeneration = DAC_WaveGeneration_None;
		DAC_InitStruct.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
		DAC_InitStruct.DAC_LFSRUnmask_TriangleAmplitude = 0;
		DAC_Init(DAC_Channel_1, &DAC_InitStruct);
	
		DAC_Cmd(DAC_Channel_1, ENABLE);
	
	
}
