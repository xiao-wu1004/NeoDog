#ifndef __DRV_KEY_H__
#define __DRV_KEY_H__
#include <stm32f4xx.h>
void key_init(void);

void key_init1(void);
uint8_t key_scan(void);
uint8_t key1_scan(void);
uint8_t key2_scan(void);
uint8_t key3_scan(void);
extern int times;
void key_state(void);

#endif
