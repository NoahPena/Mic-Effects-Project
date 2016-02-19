#include "main.h"
#include "ADC.h"
#include "DAC.h"
#include "TIMER.h"

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
	
		ADC_init();
		DAC2_init();
		TIMER6_init();
}

//Simple "bandpass resonator" (notch) filter I generated with FIVIEW,
// used to demostrate that the ADC to DAC path is working.

// Center frequency is 880Hz, Q=50
// FIVIEW generates code with doubles, I converted it to floats as
// the STM32F4 had hardware FP for floats, but not doubles

///////////////////////////////////////////////////////////////////////

// Generated by Fiview 0.9.10 <http://uazu.net/fiview/>.  
// All generated example code below is in the public domain.
// Filter 1
// File: -i #1
// Guessed type: band-pass
//
// Frequency-response:
//   Peak gain: 796.775
//   Guessed 100% gain: 796.775
//   Regions between half-power points (70.71% response or -3.01dB):
//     871.245Hz -> 888.845Hz  (width 17.6Hz, midpoint 880.045Hz)
//   Regions between quarter-power points (50% response or -6.02dB):
//     864.89Hz -> 895.372Hz  (width 30.482Hz, midpoint 880.131Hz)
//
// Filter descriptions:
//   BpRe/50/880 == Bandpass resonator, Q=50 (0 means Inf), frequency 880
//
// Example code (optimised for cleaner compilation to efficient machine code)
float filter(register float val)
{
   static float buf[2];
   register float tmp, fir, iir;
   tmp= buf[0]; 
	 memmove(buf, buf+1, 1*sizeof(float));

   iir= val * 0.001255059246835381 * 0.75;   
   iir -= 0.9974898815063291*tmp; 
	 fir = -tmp;
   iir -= -1.981739077169366*buf[0];

   fir += iir;
   buf[1]= iir; val= fir;
   return val;
}


void TIM6_DAC_IRQHandler(void)
{
		int n;
	
		if(TIM_GetITStatus(TIM6, TIM_IT_Update))
		{
				n = ADC_get();
				ADC_Start();
			
				//DAC2_set((uint16_t)(filter(n)));
				DAC2_set((uint16_t)n);
				//DAC2_set((uint16_t)(DAC_MID + n));
				//DAC2_set((uint16_t)(DAC_MID + (int)filter(n)));
			
				TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
		}
}


int main(void)
{
		InitializeSystem();
	
		while(1)
		{
			
		}
}
