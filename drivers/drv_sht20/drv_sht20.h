#ifndef __DRV_SHT20_H__
#define __DRV_SHT20_H__
#include <stm32f4xx.h>
typedef struct
{
    uint8_t tem_h;
    uint8_t tem_l;
    uint8_t hum_h;
    uint8_t hum_l;
    float tem;
    float hum;
} sht20_val;

void sht20_init(void);
uint16_t sht20_read_T(void);
float sht20_getTdata(void);
uint16_t sht20_read_RH(void);
float sht20_getRHdata(void);
#endif
