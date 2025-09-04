
#include "drv_all.h"
#include "FreeRTOS.h"
#include "task.h"
//SDA PB7
//SCL PB6


//iic��ʼ��
void iic_init(void)
{


    GPIO_InitTypeDef GPIO_InitStruct;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStruct);
}

//iic����ģʽ������������˵��
void iic_in(void)
{


    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;

    GPIO_Init(GPIOB, &GPIO_InitStruct);
}

//iic���ģʽ������������˵��
void iic_out(void)
{

    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStruct);
}

//iic��ʼ�ź�
void iic_start(void)
{
    SCL_L; //��ʱ�������ͣ�ʹ������Ч
    iic_out();//������������Ϊ���ģʽ

    SDA_H;//������������
    SCL_H;//����ʱ����ʱ������Ч
    tim4_delay_us(5);//��ʱ5us������IICʱ��Ҫ��
    SDA_L;//���������ߣ������½���
    tim4_delay_us(5);//��ʱ5us������IICʱ��Ҫ��
    SCL_L;//����ʱ����ռ������


}

//iicֹͣ�ź�
void iic_stop(void)
{

    SCL_L; //��ʱ�������ͣ�ʹ������Ч
    iic_out();//������������Ϊ���ģʽ

    SDA_L;//������������
    SCL_H;//����ʱ����ʱ������Ч
    tim4_delay_us(5);//��ʱ5us������IICʱ��Ҫ��
    SDA_H;//���������ߣ�����������
    tim4_delay_us(5);//��ʱ5us������IICʱ��Ҫ��


}

//����Ӧ���ź�
void iic_sendACK(void)
{

    SCL_L; //��ʱ�������ͣ�ʹ������Ч
    iic_out();//������������Ϊ���ģʽ

    SDA_L;//������������
    SCL_H;//����ʱ����ʱ������Ч
    tim4_delay_us(5);//��ʱ5us������IICʱ��Ҫ��
    SCL_L;//����ʱ����ռ������


}


//���ͷ�Ӧ���ź�
void iic_sendNOACK(void)
{

    SCL_L; //��ʱ�������ͣ�ʹ������Ч
    iic_out();//������������Ϊ���ģʽ

    SDA_H;//������������
    SCL_H;//����ʱ����ʱ������Ч
    tim4_delay_us(5);//��ʱ5us������IICʱ��Ҫ��
    SCL_L;//����ʱ����ռ������


}

//�ȴ�Ӧ��
uint8_t iic_waitACK(void)
{
    uint16_t tim_out = 0;
    SCL_L; //��ʱ�������ͣ�ʹ������Ч
    iic_in();//������������Ϊ����ģʽ

    SCL_H; //��ʱ�������ͣ�ʹ������Ч

    while(READ_SDA)
    {
        tim_out++;

        if(tim_out > 500)//��ʱû�еȵ�Ӧ���ź�ֹͣ����ͨ�Ų�����NOACK
        {
            iic_stop();
            return NOACK;
        }
    }

    SCL_L;//����ʱ����ռ������
    return ACK;


}

//��������
void iic_senddata(uint8_t data)
{
    uint8_t i = 0;
    SCL_L; //��ʱ�������ͣ�ʹ������Ч
    iic_out();//������������Ϊ���ģʽ

    for(i = 0; i < 8; i++)
    {
        if(data & 0x80)
        {
            SDA_H;
        }
        else
        {
            SDA_L;
        }

        SCL_H;//��ʱ�������ͣ�ʹ������Ч
        tim4_delay_us(1);
        SCL_L;
        tim4_delay_us(1);
        data = data << 1;
    }

}

//��ȡ����
uint8_t iic_readdata(uint8_t flag_ack )
{

    uint8_t read_data = 0, i = 0;
    SCL_L; //��ʱ�������ͣ�ʹ������Ч
    iic_in();//������������Ϊ����ģʽ

    for(i = 0; i < 8; i++)
    {
        read_data = read_data << 1;
        SCL_H;

        if(READ_SDA)
        {
            read_data |= 0x01;
        }

        tim4_delay_us(1);
        SCL_L;
        tim4_delay_us(1);
    }

    if(flag_ack == ACK)
    {
        iic_sendACK();
    }
    else
    {
        iic_sendNOACK();
    }

    SCL_L;
    return read_data;
}


