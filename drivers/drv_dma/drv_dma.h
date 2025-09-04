#ifndef __DRV_DMA_H__
#define	__DRV_DMA_H__
#include "stm32f4xx.h"
void dma_init(uint32_t *src, uint32_t *dir,uint32_t size);
void dmadata_compare(void);
#endif
