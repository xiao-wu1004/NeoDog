#include "drv_all.h"
//adc1 pb1 ͨ��0 ������0
void adc1_init()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	ADC_CommonInitTypeDef ADC_CommonInitStruct;
	ADC_InitTypeDef ADC_InitStruct;
	DMA_InitTypeDef DMA_InitStruct;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_DMA2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;//ģ������
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;//����
	GPIO_Init(GPIOB, &GPIO_InitStruct);

	ADC_CommonInitStruct.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;//��ʹ��DMAֱ�ӼĴ�������
	ADC_CommonInitStruct.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonInitStruct.ADC_Prescaler = ADC_Prescaler_Div4;//84/4=21mhz  ADC��Ƶ����߲��ܳ���36Mhz
	ADC_CommonInitStruct.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;//��������5��ʱ������
	ADC_CommonInit(&ADC_CommonInitStruct);

	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;//ʹ������ת��
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;//�����Ҷ���
	ADC_InitStruct.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//��ʹ���ⲿ����
	ADC_InitStruct.ADC_NbrOfConversion = 1;//ͨ����
	ADC_InitStruct.ADC_Resolution = ADC_Resolution_12b;//12λ�ֱ���
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;//��ɨ��
	ADC_Init(ADC1, &ADC_InitStruct);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
    DMA_InitTypeDef DMA_InitStruct;
	DMA_InitStruct.DMA_BufferSize=size;//????????????????
	DMA_InitStruct.DMA_Channel=DMA_Channel_0;
	DMA_InitStruct.DMA_DIR=DMA_DIR_MemoryToMemory;
	DMA_InitStruct.DMA_FIFOMode=DMA_FIFOMode_Disable;
	DMA_InitStruct.DMA_Memory0BaseAddr=(uint32_t)dir;//?????
	DMA_InitStruct.DMA_MemoryBurst=DMA_MemoryBurst_Single;
	DMA_InitStruct.DMA_MemoryDataSize=DMA_MemoryDataSize_Word;
	DMA_InitStruct.DMA_MemoryInc=DMA_MemoryInc_Enable;
	DMA_InitStruct.DMA_Mode=DMA_Mode_Normal;
	
	DMA_InitStruct.DMA_PeripheralBaseAddr=(uint32_t )src;//????
	DMA_InitStruct.DMA_PeripheralBurst=DMA_PeripheralBurst_Single;//???????
	DMA_InitStruct.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Word;
	DMA_InitStruct.DMA_PeripheralInc=DMA_PeripheralInc_Enable;
	DMA_InitStruct.DMA_Priority=DMA_Priority_High;
    DMA_Init(DMA2_Stream0, &DMA_InitStruct);
	DMA_Cmd(DMA2_Stream0,ENABLE);
}