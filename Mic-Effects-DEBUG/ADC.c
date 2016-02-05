#include "ADC.h"


void InitializeTimer()
{
		TIM_TimeBaseInitTypeDef timer;
	
		timer.TIM_Prescaler = 0;
		timer.TIM_CounterMode = TIM_CounterMode_Up;
		timer.TIM_Period = 951;
		timer.TIM_ClockDivision = TIM_CKD_DIV1;
		timer.TIM_RepetitionCounter = 0;
		TIM_TimeBaseInit(TIM2, &timer);
		TIM_Cmd(TIM2, ENABLE);
	
		TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
}

void EnableTimerInterrupt()
{
    NVIC_InitTypeDef nvicStructure;
    nvicStructure.NVIC_IRQChannel = TIM2_IRQn;
    nvicStructure.NVIC_IRQChannelPreemptionPriority = 0;
    nvicStructure.NVIC_IRQChannelSubPriority = 1;
    nvicStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvicStructure);
}

void Initialize_ADC(void)
{
		ADC_InitTypeDef ADC_InitStruct;
		GPIO_InitTypeDef GPIO_InitStruct;
	
		GPIO_StructInit(&GPIO_InitStruct);
		GPIO_InitStruct.GPIO_Pin = 0x01;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
		GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_Init(GPIOC, &GPIO_InitStruct);
	
		ADC_DeInit();
		ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
		ADC_InitStruct.ADC_Resolution = ADC_Resolution_12b;
		ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;
		ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
		ADC_InitStruct.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
		ADC_InitStruct.ADC_NbrOfConversion = 1;
		ADC_InitStruct.ADC_ScanConvMode = DISABLE;
		ADC_Init(ADC1, &ADC_InitStruct);
		
		ADC_Cmd(ADC1, ENABLE);
		
		ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 1, ADC_SampleTime_144Cycles);
		
		
		InitializeTimer();		
}

uint16_t readADC1(uint8_t channel)
{
		ADC_SoftwareStartConv(ADC1);
		while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));
		return ADC_GetConversionValue(ADC1);
}

void TIM2_IRQHandler()
{
		float32_t data;
		char str[10];
	
		if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
		{
				TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
			
				//data = (readADC1(10) - 2047.5)/(2047.5);
				GPIOD->ODR ^= 0x2000;
				data = readADC1(10);
				GPIOD->ODR ^= 0x4000;
		}
}
