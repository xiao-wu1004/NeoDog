#ifndef __DRV_led_H__
#define __DRV_led_H__
#include <stm32f4xx.h>

void led_init(void);
void led3_1_init(void);

void led_ON(void);
void led_OFF(void);

void led1_ON(void);
void led1_OFF(void);

void led2_ON(void);
void led2_OFF(void);

void led3_ON(void);
void led3_OFF(void);

void delay_ms(uint32_t ms);

void led_Blink(void);

void liushui_led(void);

void all_led_ON(void);
void all_led_OFF(void);
#endif
