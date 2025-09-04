#include "drv_fan.h"
/*
��������fan_init
�������ܣ���ʼ��fan
�����������
�����������
������fan ->PC6 �ߵ�ƽ��
*/
void fan_init()
{
    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOC, ENABLE);

    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;//����������
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz; //��������
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT; //�������ģʽ
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP; //ʹ������

    GPIO_Init(GPIOC, &GPIO_InitStruct);
    GPIO_ResetBits(GPIOC, GPIO_Pin_6); //Ĭ�Ϲر�fan
}

/*
��������fan_ON
�������ܣ�����fan
�����������
�����������
������fan ->PC6 �ߵ�ƽ��
*/
void fan_ON()
{
    GPIO_SetBits(GPIOC, GPIO_Pin_6); //��fan
}

/*
��������fan_OFF
�������ܣ��ر�fan
�����������
�����������
������fan ->PC6 �ߵ�ƽ��
*/
void fan_OFF()
{
    GPIO_ResetBits(GPIOC, GPIO_Pin_6); //�ر�fan

}
