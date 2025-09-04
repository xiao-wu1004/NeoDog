#ifndef __DRV_TIME_H__
#define __DRV_TIME_H__
#include "stm32f4xx.h"
void tim7_init(void);
void tim13_init(void);
void tim3_init(void);
void tim4_init(void);
void tim7_delay_ms(uint32_t ms);

void tim4_delay_us(uint32_t nus);
void tim4_delay_ms(uint16_t nms);
void tim4_delay_init(void);
#endif
