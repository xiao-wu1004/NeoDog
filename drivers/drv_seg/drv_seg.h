#ifndef __DRV_SEG_H__
#define __DRV_SEG_H__
#include <stm32f4xx.h>
void drv_74hc595_init(void);
void seg_display(uint8_t wei, uint8_t duan);
void display_temp(float temp);
#endif
