#ifndef __DRV_ALL_H__
#define __DRV_ALL_H__
#include <stm32f4xx.h>
#include "drv_led.h"
#include "drv_beep.h"
#include "drv_systick.h"
#include "drv_key.h"
#include "drv_motor.h"
#include "drv_fan.h"
#include "drv_exti.h"
#include "drv_usart.h"
#include "drv_time.h"
#include "drv_iic.h"
#include "drv_sht20.h"
#include "drv_spi.h"
#include "drv_seg.h"
#include "drv_dma.h"
#include "drv_adc.h"
#include "drv_sg90.h"
#include "drv_wifi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


// ����״̬����
typedef enum
{
    ACTION_IDLE,          // ����״̬
    ACTION_WALKING,       // ������
    ACTION_DANCING,       // ������
    ACTION_GREETING,      // ���к���
    ACTION_TURNING_LEFT,  // ��ת��
    ACTION_TURNING_RIGHT,  // ��ת��
	ACTION_TURNING_TEMP
} ActionState;

// ������ʾ��־
typedef enum
{
    EXPRESSION_NONE,
    EXPRESSION_WALKING,
    EXPRESSION_DANCE,
    EXPRESSION_GREET,
    EXPRESSION_STOP,
    EXPRESSION_LEFT,
    EXPRESSION_RIGHT,
	EXPRESSION_TEMP,
	EXPRESSION_LED_ON,
	EXPRESSION_LED_OFF
	
} ExpressionType;

#endif
