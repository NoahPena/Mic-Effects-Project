#include "ADC.h"

void ADC_init(void)
{
   ADC_InitTypeDef ADC_InitStructure;
   ADC_CommonInitTypeDef ADC_CommonInitStructure;
   GPIO_InitTypeDef GPIO_InitStructure;
	
		/* Enable peripheral clocks */
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
 
   /* Configure ADC Channel 10 pin as analog input */

   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
   GPIO_Init(GPIOC, &GPIO_InitStructure);
 
   /* ADC Common configuration *************************************************/

   ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
   // APB2 clock is half the 168Mhz system clock (i.e. 84Mhz),
   // so with a div by 8, ADC PCLK would be 10.5Mhz.
   // F4 datasheet says ADC clock freq should be 0.6Mhz - 30Mhz for Vdda=3.3V
   ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div8;
   ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
   //TwoSamplingDelay is only used in dual and triple modes)
   ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;   
   ADC_CommonInit(&ADC_CommonInitStructure);
 
   /* ADC1 regular channel 10 to 15 configuration ************************************/

   ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
   ADC_InitStructure.ADC_ScanConvMode = DISABLE; // 1 Channel
   ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; // Conversions Triggered
   ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None; // Manual
   ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T2_TRGO;  //Unused for manual?
   ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
   ADC_InitStructure.ADC_NbrOfConversion = 1;
   ADC_Init(ADC1, &ADC_InitStructure);

   //The sample time is how long the input is sampled before the conversion is done.
   //Since PCLK is 10.5Mhz, 144 cycles is about 13.7uS and the DAC output rate is
   //running manually off a 44Khz timer interrupt (22uS), we should be fine
   //(once conversion starts, it takes about 16 cycles)
   ADC_RegularChannelConfig(ADC1, ADC_Channel_15, 1, ADC_SampleTime_144Cycles);
 
   /* Enable ADC1 */
   ADC_Cmd(ADC1, ENABLE);

   ADC_Start();
}

void ADC_Start(void)
{
		ADC_SoftwareStartConv(ADC1);
}

int32_t ADC_get(void)
{
		while(ADC_GetSoftwareStartConvStatus(ADC1) != RESET);
		
		return (ADC_GetSoftwareStartConvStatus(ADC1) == RESET) ? ADC_GetConversionValue(ADC1) : -1;
}

