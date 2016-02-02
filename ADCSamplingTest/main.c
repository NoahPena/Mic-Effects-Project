
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"


void Setup_Debug_LEDS(void)
{
		GPIO_InitTypeDef gpio;
		
		RCC_AHB1PeriphClockCmd(RCC_AHB1ENR_GPIOBEN, ENABLE);
	
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
		Setup_Debug_LEDS();
}

int main(void)
{
		Initialize_System_Peripherals();

	
}
