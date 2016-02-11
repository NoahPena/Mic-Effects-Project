#include "TIMER.h"

void TIMER6_init(void)
{
		TIM_TimeBaseInitTypeDef timer;
		NVIC_InitTypeDef interrupt;
	
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
	
		TIM_TimeBaseStructInit(&timer);
		timer.TIM_Period = 1909;
		timer.TIM_Prescaler = 0;
		timer.TIM_ClockDivision = 0;
		timer.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_TimeBaseInit(TIM6, &timer);
	
		interrupt.NVIC_IRQChannel = TIM6_DAC_IRQn;
		interrupt.NVIC_IRQChannelPreemptionPriority = 0;
		interrupt.NVIC_IRQChannelSubPriority = 0;
		interrupt.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&interrupt);
	
		TIM_Cmd(TIM6, ENABLE);
		TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);
}


