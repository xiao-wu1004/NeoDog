#include "drv_all.h"

void dma_init(uint32_t *src, uint32_t *dir,uint32_t size)
{
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
    DMA_InitTypeDef DMA_InitStruct;
	DMA_InitStruct.DMA_BufferSize=size;//需要搬运数据的数量
	DMA_InitStruct.DMA_Channel=DMA_Channel_0;
	DMA_InitStruct.DMA_DIR=DMA_DIR_MemoryToMemory;
	DMA_InitStruct.DMA_FIFOMode=DMA_FIFOMode_Disable;
	DMA_InitStruct.DMA_Memory0BaseAddr=(uint32_t)dir;//目标地址
	DMA_InitStruct.DMA_MemoryBurst=DMA_MemoryBurst_Single;
	DMA_InitStruct.DMA_MemoryDataSize=DMA_MemoryDataSize_Word;
	DMA_InitStruct.DMA_MemoryInc=DMA_MemoryInc_Enable;
	DMA_InitStruct.DMA_Mode=DMA_Mode_Normal;
	
	DMA_InitStruct.DMA_PeripheralBaseAddr=(uint32_t )src;//源地址
	DMA_InitStruct.DMA_PeripheralBurst=DMA_PeripheralBurst_Single;//单次突发
	DMA_InitStruct.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Word;
	DMA_InitStruct.DMA_PeripheralInc=DMA_PeripheralInc_Enable;
	DMA_InitStruct.DMA_Priority=DMA_Priority_High;
    DMA_Init(DMA2_Stream0, &DMA_InitStruct);
	DMA_Cmd(DMA2_Stream0,ENABLE);
}

extern uint32_t dma_src[];
extern uint32_t dma_dir[];
void dmadata_compare()
{
	uint8_t i;
	for(i=0;i<5;i++)
	{
		if(dma_src[i]!=dma_dir[i])
		{
			printf("data error!\r\n");
			return;
		}
		printf("%d ",dma_dir[i]);
	}
	printf("data ok!\r\n");
}
