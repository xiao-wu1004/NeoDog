#include "drv_all.h"
/*
��������led_Init
�������ܣ���ʼ��led
�����������
�����������
������led ->PF8 �͵�ƽ��
*/
void led_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    //���ⲿʱ��
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF | RCC_AHB1Periph_GPIOC, ENABLE);
    //    RCC->AHB1ENR = 0x01 << 5;
    //    GPIOF->MODER &= ~(0x03 << 16); //����
    //    GPIOF->MODER |= 0x01 << 16; //���ģʽ01
    //    GPIOF->BSRRL |= 0x01 << 8; //��� ��λ ��16λ
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8; //����������
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT; //�������ģʽ
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz; //��������
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP; //ʹ������
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP; //�����������
    //GPIOF��ʼ��
    GPIO_Init(GPIOF, &GPIO_InitStruct);
    //����Ϊ�ߵ�ƽ ledϨ��
    GPIO_SetBits(GPIOF, GPIO_Pin_8);
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_3 | GPIO_Pin_13; //����������
    //GPIOC��ʼ��
    GPIO_Init(GPIOC, &GPIO_InitStruct);
    //����Ϊ�ߵ�ƽ ledϨ��
    GPIO_ResetBits(GPIOC, GPIO_Pin_4 | GPIO_Pin_3 | GPIO_Pin_13);
}

//void led3_1_init(void)
//{
//    GPIO_InitTypeDef GPIO_InitStruct3;
//    //���ⲿʱ��
//    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

//    GPIO_InitStruct3.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_3 | GPIO_Pin_13; //����������
//    GPIO_InitStruct3.GPIO_Mode = GPIO_Mode_OUT; //�������ģʽ
//    GPIO_InitStruct3.GPIO_Speed = GPIO_Speed_2MHz; //��������
//    GPIO_InitStruct3.GPIO_PuPd = GPIO_PuPd_UP; //ʹ������
//    GPIO_InitStruct3.GPIO_OType = GPIO_OType_PP; //�����������

//    //GPIO��ʼ��
//    GPIO_Init(GPIOC, &GPIO_InitStruct3);

//    //����Ϊ�ߵ�ƽ ledϨ��
//    GPIO_ResetBits(GPIOC, GPIO_Pin_4 | GPIO_Pin_3 | GPIO_Pin_13);
//}


/*
��������led_ON
�������ܣ�����led
�����������
�����������
������led ->PF8 �͵�ƽ��
*/
void led_ON(void)
{
    //printf("userled ON\r\n");
    GPIO_ResetBits(GPIOF, GPIO_Pin_8);
    //GPIOF->BSRRH |=(0x01 << 8); //���� ��λ  ��16λ
}


/*
��������led_OFF
�������ܣ�Ϩ��led
�����������
�����������
������led ->PF8 �ߵ�ƽ��
*/
void led_OFF(void)
{
    GPIO_SetBits(GPIOF, GPIO_Pin_8);
    //GPIOF->BSRRL |= 0x01 << 8; //��� ��λ ��16λ
}

/*
��������delay_ms
�������ܣ����Ե�ms��ʱ
���������ms��
�����������
��������
*/
void delay_ms(uint32_t ms)
{
    uint32_t i, j;

    for (i = 0; i < ms; i++)
    {
        for (j = 0; j < 0xfff; j++);
    }
}

// ΢�뼶��ʱ�����Թ��ƣ�
void delay_us(unsigned int us)
{
    for (volatile unsigned int i = 0; i < us; i++)
    {
        // ��ѭ��������ѭ��������Ҫ����CPUƵ�ʵ���
        for (volatile unsigned int j = 0; j < 10; j++)
        {
            // ��С�Ŀ�ѭ��
        }
    }
}
/*
��������led_Blink
�������ܣ�led ��˸
�����������
�����������
������led ->PF8 �͵�ƽ��
*/
void led_Blink(void)
{
    uint32_t i;

    for (i = 0; i < 10; i++)
    {
        led_ON();
        //delay_ms(2000);
        drv_systick_ms(999);
        led_OFF();
        //delay_ms(2000);
        drv_systick_ms(999);
    }
}



/*
��������led1_ON
�������ܣ�����led1
�����������
�����������
������led1 ->PC4 �͵�ƽ��
*/
void led1_ON(void)
{
    GPIO_SetBits(GPIOC, GPIO_Pin_4);
}


/*
��������led1_OFF
�������ܣ�Ϩ��led1
�����������
�����������
������led1 ->PC4 �ߵ�ƽ��
*/
void led1_OFF(void)
{
    GPIO_ResetBits(GPIOC, GPIO_Pin_4);
}

/*
��������led2_ON
�������ܣ�����led2
�����������
�����������
������led2 ->PC3 �͵�ƽ��
*/
void led2_ON(void)
{
    GPIO_SetBits(GPIOC, GPIO_Pin_3);
}


/*
��������led2_OFF
�������ܣ�Ϩ��led2
�����������
�����������
������led2 ->PC3 �ߵ�ƽ��
*/
void led2_OFF(void)
{
    GPIO_ResetBits(GPIOC, GPIO_Pin_3);
}

/*
��������led3_ON
�������ܣ�����led3
�����������
�����������
������led3 ->PC13 �͵�ƽ��
*/
void led3_ON(void)
{
    GPIO_SetBits(GPIOC, GPIO_Pin_13);
}


/*
��������led3_OFF
�������ܣ�Ϩ��led3
�����������
�����������
������led3 ->PC13 �ߵ�ƽ��
*/
void led3_OFF(void)
{
    GPIO_ResetBits(GPIOC, GPIO_Pin_13);
}

/*
��������led3_OFF
�������ܣ�Ϩ��led3
�����������
�����������
������led3 ->PC13 �ߵ�ƽ��
*/

void liushui_led(void)
{
    uint8_t i;

    for (i = 0; i < 100; i++)
    {
        led1_ON();
        drv_systick_ms(1999);
        led1_OFF();
        led2_ON();
        drv_systick_ms(1999);
        led2_OFF();
        led3_ON();
        drv_systick_ms(1999);
        led3_OFF();
    }
}

//��led1 led2 led3
void all_led_ON(void)
{
    GPIO_SetBits(GPIOC, GPIO_Pin_4);
    GPIO_SetBits(GPIOC, GPIO_Pin_3);
    GPIO_SetBits(GPIOC, GPIO_Pin_13);
}

//�ر�led1 led2 led3
void all_led_OFF(void)
{
    GPIO_ResetBits(GPIOC, GPIO_Pin_4);
    GPIO_ResetBits(GPIOC, GPIO_Pin_3);
    GPIO_ResetBits(GPIOC, GPIO_Pin_13);
}
