#include "drv_motor.h"
/*
��������motor_init
�������ܣ���ʼ�����
�����������
�����������
������motor ->PC7 �ߵ�ƽ��
*/
void motor_init()
{
	RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOC, ENABLE);

    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;//����������
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz; //��������
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT; //�������ģʽ
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP; //ʹ������
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP; //�����������
	GPIO_ResetBits(GPIOC,GPIO_Pin_7);//Ĭ�Ϲر�motor
	GPIO_Init(GPIOC,&GPIO_InitStruct);
}

/*
��������motor_ON
�������ܣ��������
�����������
�����������
������motor ->PC7 �ߵ�ƽ��
*/
void motor_ON()
{
	GPIO_SetBits(GPIOC,GPIO_Pin_7);//��motor
}

/*
��������motor_OFF
�������ܣ��ر����
�����������
�����������
������motor ->PC7 �ߵ�ƽ��
*/
void motor_OFF()
{
	GPIO_ResetBits(GPIOC,GPIO_Pin_7);//�ر�motor
}
