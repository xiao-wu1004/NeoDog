#include "drv_beep.h"
#include "drv_led.h"
#include "drv_systick.h"
/*
��������beep_init
�������ܣ���ʼ��������
�����������
�����������
������beep ->PA15 �ߵ�ƽ��
*/
void beep_init()
{

    //����GPIOA��ʱ��
    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;//����������
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz; //��������
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT; //�������ģʽ
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP; //ʹ������
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP; //�����������

    //GPIO��ʼ��
    GPIO_Init(GPIOA, &GPIO_InitStruct);
    //����Ϊ�͵�ƽ ����������
    GPIO_ResetBits(GPIOA, GPIO_Pin_15);

//    RCC->AHB1ENR |= 0x01 << 0;//����GPIOA��ʱ��
//    GPIOA->MODER &= ~(0x03 << 30);//����
//    GPIOA->MODER |= 0x01 << 30;//���ó����ģʽ01
//
//	GPIOA->PUPDR &= ~(0x03<<30);
//	GPIOA->PUPDR |=0x01<<30; //���ó�����ģʽ01
//
//    GPIOA->ODR &= ~(0x01 << 15);//��0�������ȡ����beepĬ�Ϲر�


}

/*
��������beep_ON
�������ܣ��÷�������
�����������
�����������
������beep ->PA15 �ߵ�ƽ��
*/
void beep_ON()
{

    GPIO_SetBits(GPIOA, GPIO_Pin_15);


//    GPIOA->ODR |= 0x01 << 15;//��1���û�

}
/*
��������beep_OFF
�������ܣ��÷���������
�����������
�����������
������beep ->PA15 �ߵ�ƽ��
*/
void beep_OFF()
{

    GPIO_ResetBits(GPIOA, GPIO_Pin_15);

//    GPIOA->ODR &= ~(0x01 << 15);//��0�������ȡ����

}

/*
��������beep_Blink
�������ܣ�beep ��˸
�����������
�����������
������beep ->PA15 �ߵ�ƽ��
*/
void beep_Blink(void)
{
    uint32_t i;

    for(i = 0; i < 10; i++)
    {
        beep_ON();
        delay_ms(20);
        beep_OFF();
        delay_ms(2000);
    }
}
