#include "drv_all.h"
//adc1 pb1 ͨ��0 ������0

uint16_t adc_buf[100];
void adc1_init()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	ADC_CommonInitTypeDef ADC_CommonInitStruct;
	ADC_InitTypeDef ADC_InitStruct;
	DMA_InitTypeDef DMA_InitStruct;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
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
    
	DMA_InitStruct.DMA_BufferSize=100;//��Ҫ�������ݵ�����
	DMA_InitStruct.DMA_Channel=DMA_Channel_0;//DMAͨ��
	DMA_InitStruct.DMA_DIR=DMA_DIR_PeripheralToMemory;//���赽�ڴ� ��adc�ɼ�����
	DMA_InitStruct.DMA_FIFOMode=DMA_FIFOMode_Disable;
	DMA_InitStruct.DMA_Memory0BaseAddr=(uint32_t)adc_buf;//Ŀ���ַ
	DMA_InitStruct.DMA_MemoryBurst=DMA_MemoryBurst_Single;//����ͻ��
	DMA_InitStruct.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord;//����
	DMA_InitStruct.DMA_MemoryInc=DMA_MemoryInc_Enable;//��ַ����
	DMA_InitStruct.DMA_Mode=DMA_Mode_Circular;//ѭ��ģʽ
	
	DMA_InitStruct.DMA_PeripheralBaseAddr=(uint32_t)&ADC1->DR;//����Դ��ַ
	DMA_InitStruct.DMA_PeripheralBurst=DMA_PeripheralBurst_Single;//����ͻ��
	DMA_InitStruct.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord;//����
	DMA_InitStruct.DMA_PeripheralInc=DMA_PeripheralInc_Disable;
	DMA_InitStruct.DMA_Priority=DMA_Priority_High;
    DMA_Init(DMA2_Stream0, &DMA_InitStruct);
	DMA_Cmd(DMA2_Stream0,ENABLE);

	ADC_RegularChannelConfig( ADC1,  ADC_Channel_9, 1, ADC_SampleTime_84Cycles);//���ò������򣬲���ʱ��
	ADC_DMARequestAfterLastTransferCmd( ADC1,  ENABLE);//����dma��������
	ADC_DMACmd( ADC1, ENABLE);//ʹ��adc dma
	ADC_Cmd( ADC1,  ENABLE);//ʹ��adc
	ADC_SoftwareStartConv( ADC1);//����adc��ʼת��
	
}

uint16_t adc1_avg()
{
	uint8_t i;
	uint32_t sum=0;
	for(i=0;i<100;i++)
		{
			sum+=adc_buf[i];
		}
	printf("%d\r\n",sum);
	return (uint16_t)sum/100;
}
