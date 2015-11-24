#include "FFT.h"
#include "InputData.h"
#include "UART.h"

#include <stdio.h>

void computeFFT(void)
{
		arm_cfft_f32(&arm_cfft_sR_f32_len1024, input, 0, 1);
	
		arm_cmplx_mag_f32(input, output, FFT_SIZE);
	
		dataReady = 1;
	
		currentFrequencyBin = getFrequency();
}

//float32_t getMaxValue(void)
//{
//	float32_t maxValue;
//	uint32_t maxValueIndex;
//	
//	arm_max_f32(output, FFT_SIZE, &maxValue, &maxValueIndex);
//	
//	return maxValue;
//}

uint32_t getMaxValueIndex(void)
{
	uint32_t maxValueIndex;
	float32_t maxValue;
	
	arm_max_f32(output, FFT_SIZE, &maxValue, &maxValueIndex);
	
//	if(maxValueIndex == 0)
//	{
//			output[0] = 0;
//			arm_max_f32(output, FFT_SIZE, &maxValue, &maxValueIndex);
//	}
	
	return maxValueIndex;
}

uint32_t getFrequency(void)
{
		uint32_t index;
		uint32_t i = 0;
		float32_t fs;
		uint32_t fftSize = FFT_SIZE;
		uint32_t frequency = 0;
		char str[15];
	
		//computeFFT();
	
		if(dataReady)
		{
				UART_puts("\t----\n");
				index = getMaxValueIndex();
				sprintf(str, "\t%d\n", index);
				UART_puts(str);
				fs = 44100;
				sprintf(str, "\t%f\n", fs);
				UART_puts(str);
				frequency = (float32_t)((fs * (float32_t)index) / (float32_t)fftSize);
				sprintf(str, "\t%d\n", frequency);
				UART_puts(str);
				UART_puts("\t-----\n");
				
				for(;i < 1024; i++)
				{
						sprintf(str, "%f", output[i]);
						UART_puts(str);
						UART_puts("\n");
				}
				
				while(1);
				
				resetTable();
		}
	
		return frequency;
}
