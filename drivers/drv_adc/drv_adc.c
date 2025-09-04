#include "drv_all.h"
//adc1 pb1 通道0 数据流0

uint16_t adc_buf[100];
void adc1_init()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	ADC_CommonInitTypeDef ADC_CommonInitStruct;
	ADC_InitTypeDef ADC_InitStruct;
	DMA_InitTypeDef DMA_InitStruct;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;//模拟输入
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;//浮空
	GPIO_Init(GPIOB, &GPIO_InitStruct);

	ADC_CommonInitStruct.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;//不使用DMA直接寄存器访问
	ADC_CommonInitStruct.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonInitStruct.ADC_Prescaler = ADC_Prescaler_Div4;//84/4=21mhz  ADC的频率最高不能超过36Mhz
	ADC_CommonInitStruct.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;//采样周期5个时钟周期
	ADC_CommonInit(&ADC_CommonInitStruct);

	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;//使能连续转换
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;//数据右对齐
	ADC_InitStruct.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//不使用外部触发
	ADC_InitStruct.ADC_NbrOfConversion = 1;//通道数
	ADC_InitStruct.ADC_Resolution = ADC_Resolution_12b;//12位分辨率
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;//不扫描
	ADC_Init(ADC1, &ADC_InitStruct);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
    
	DMA_InitStruct.DMA_BufferSize=100;//需要搬运数据的数量
	DMA_InitStruct.DMA_Channel=DMA_Channel_0;//DMA通道
	DMA_InitStruct.DMA_DIR=DMA_DIR_PeripheralToMemory;//外设到内存 从adc采集数据
	DMA_InitStruct.DMA_FIFOMode=DMA_FIFOMode_Disable;
	DMA_InitStruct.DMA_Memory0BaseAddr=(uint32_t)adc_buf;//目标地址
	DMA_InitStruct.DMA_MemoryBurst=DMA_MemoryBurst_Single;//单次突发
	DMA_InitStruct.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord;//半字
	DMA_InitStruct.DMA_MemoryInc=DMA_MemoryInc_Enable;//地址自增
	DMA_InitStruct.DMA_Mode=DMA_Mode_Circular;//循环模式
	
	DMA_InitStruct.DMA_PeripheralBaseAddr=(uint32_t)&ADC1->DR;//数据源地址
	DMA_InitStruct.DMA_PeripheralBurst=DMA_PeripheralBurst_Single;//单次突发
	DMA_InitStruct.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord;//半字
	DMA_InitStruct.DMA_PeripheralInc=DMA_PeripheralInc_Disable;
	DMA_InitStruct.DMA_Priority=DMA_Priority_High;
    DMA_Init(DMA2_Stream0, &DMA_InitStruct);
	DMA_Cmd(DMA2_Stream0,ENABLE);

	ADC_RegularChannelConfig( ADC1,  ADC_Channel_9, 1, ADC_SampleTime_84Cycles);//设置采样规则，采样时间
	ADC_DMARequestAfterLastTransferCmd( ADC1,  ENABLE);//设置dma触发条件
	ADC_DMACmd( ADC1, ENABLE);//使能adc dma
	ADC_Cmd( ADC1,  ENABLE);//使能adc
	ADC_SoftwareStartConv( ADC1);//触发adc开始转换
	
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
