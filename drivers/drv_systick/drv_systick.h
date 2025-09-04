#ifndef __DRV_SYSTICK_H__
#define __DRV_SYSTICK_H__
#include <stm32f4xx.h>

void drv_systick_init(uint32_t systick);
void drv_systick_ms(uint32_t ms);
void drv_systick_us(uint32_t us);
#endif
