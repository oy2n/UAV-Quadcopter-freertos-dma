
#include "adc1.h"
#include "delay.h"

volatile uint16_t adcValues;
extern DMA_HandleTypeDef hdma_adc1;
extern ADC_HandleTypeDef hadc1;

void adc1Init(void)
{
	while(HAL_ADC_Start_DMA(&hadc1, &adcValues, 2))
	{
		;
	}
//	GPIO_InitTypeDef GPIO_InitStructure;
//    ADC_InitTypeDef ADC_InitStructure;
//    DMA_InitTypeDef DMA_InitStructure;
//    ADC_CommonInitTypeDef ADC_CommonInitStructure;
//
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
//
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 ;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
//	GPIO_Init(GPIOC, &GPIO_InitStructure);
//
//    DMA_DeInit(DMA2_Stream4);
//    DMA_StructInit(&DMA_InitStructure);
//    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;
//	DMA_InitStructure.DMA_Channel = DMA_Channel_0;
//    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&adcValues;
//    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
//    DMA_InitStructure.DMA_BufferSize = 1;
//    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
//    DMA_InitStructure.DMA_MemoryInc =  DMA_MemoryInc_Disable;
//    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
//    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
//    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
//    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
//    DMA_Init(DMA2_Stream4, &DMA_InitStructure);
//
//    DMA_Cmd(DMA2_Stream4, ENABLE);
//
//    ADC_CommonStructInit(&ADC_CommonInitStructure);
//    ADC_CommonInitStructure.ADC_Mode             = ADC_Mode_Independent;
//    ADC_CommonInitStructure.ADC_Prescaler        = ADC_Prescaler_Div8;
//    ADC_CommonInitStructure.ADC_DMAAccessMode    = ADC_DMAAccessMode_Disabled;
//    ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
//    ADC_CommonInit(&ADC_CommonInitStructure);
//
//    ADC_StructInit(&ADC_InitStructure);
//    ADC_InitStructure.ADC_ContinuousConvMode       = ENABLE;
//    ADC_InitStructure.ADC_Resolution               = ADC_Resolution_12b;
//    ADC_InitStructure.ADC_ExternalTrigConv         = ADC_ExternalTrigConv_T1_CC1;
//    ADC_InitStructure.ADC_ExternalTrigConvEdge     = ADC_ExternalTrigConvEdge_None;
//    ADC_InitStructure.ADC_DataAlign                = ADC_DataAlign_Right;
//    ADC_InitStructure.ADC_NbrOfConversion          = 1;
//    ADC_InitStructure.ADC_ScanConvMode             = DISABLE;
//    ADC_Init(ADC1, &ADC_InitStructure);
//
//    ADC_RegularChannelConfig(ADC1, ADC_Channel_15, 1, ADC_SampleTime_56Cycles);
//
//	ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);
//
//    ADC_DMACmd(ADC1, ENABLE);
//	ADC_Cmd(ADC1, ENABLE);
//
//    ADC_SoftwareStartConv(ADC1);
}

