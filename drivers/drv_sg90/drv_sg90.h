#ifndef __DRV_SG90_H__
#define __DRV_SG90_H__
#include "stm32f4xx.h"
#include <stdbool.h>
void sg90_init(void);
void sg90_set_angle(uint8_t ch, uint8_t angle);
bool robot_walk_continuous(void);
void robot_sitdown(void);
void robot_standup(void);
void robot_stop(void);


// ÌøÎèÖ÷º¯Êý
bool robot_dance(void);
bool robot_turn_left(uint8_t steps, uint16_t speed);
bool robot_turn_right(uint8_t steps, uint16_t speed);
bool robot_greet(uint8_t times, uint16_t speed);

void test_all_servos(void);
#endif
