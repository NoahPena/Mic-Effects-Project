#include "UART.h"
#include "ADC.h"

#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"

void Setup_Clocks(void)
{
		RCC_AHB1PeriphClockCmd(RCC_AHB1ENR_GPIOBEN, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1ENR_GPIOCEN, ENABLE);
}

void Setup_Debug_LEDS(void)
{
		GPIO_InitTypeDef gpio;		
	
		gpio.GPIO_Mode = GPIO_Mode_OUT;
		gpio.GPIO_OType = GPIO_OType_PP;
		gpio.GPIO_Pin = 0x02;
		gpio.GPIO_PuPd = GPIO_PuPd_UP;
		gpio.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_Init(GPIOB, &gpio);
	
		GPIOB->ODR = 0x00;
}

void Initialize_System_Peripherals(void)
{
		Setup_Clocks();
		Setup_Debug_LEDS();
		Initialize_UART(115200);
		Initialize_ADC();
		InitializeTimer();
}

void Enable_System_Interrupts(void)
{
		EnableTimerInterrupt();
}

int main(void)
{
		Initialize_System_Peripherals();
		Enable_System_Interrupts();
	
		while(1)
		{
			
		}

	
}
