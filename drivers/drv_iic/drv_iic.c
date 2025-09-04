
#include "drv_all.h"
#include "FreeRTOS.h"
#include "task.h"
//SDA PB7
//SCL PB6


//iic初始化
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

//iic输入模式（对于主机来说）
void iic_in(void)
{


    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;

    GPIO_Init(GPIOB, &GPIO_InitStruct);
}

//iic输出模式（对于主机来说）
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

//iic开始信号
void iic_start(void)
{
    SCL_L; //将时钟线拉低，使数据无效
    iic_out();//将数据线设置为输出模式

    SDA_H;//将数据线拉高
    SCL_H;//拉高时钟线时数据有效
    tim4_delay_us(5);//延时5us，满足IIC时序要求
    SDA_L;//拉低数据线，产生下降沿
    tim4_delay_us(5);//延时5us，满足IIC时序要求
    SCL_L;//拉低时钟线占用总线


}

//iic停止信号
void iic_stop(void)
{

    SCL_L; //将时钟线拉低，使数据无效
    iic_out();//将数据线设置为输出模式

    SDA_L;//将数据线拉低
    SCL_H;//拉高时钟线时数据有效
    tim4_delay_us(5);//延时5us，满足IIC时序要求
    SDA_H;//拉低数据线，产生上升沿
    tim4_delay_us(5);//延时5us，满足IIC时序要求


}

//发送应答信号
void iic_sendACK(void)
{

    SCL_L; //将时钟线拉低，使数据无效
    iic_out();//将数据线设置为输出模式

    SDA_L;//将数据线拉低
    SCL_H;//拉高时钟线时数据有效
    tim4_delay_us(5);//延时5us，满足IIC时序要求
    SCL_L;//拉低时钟线占用总线


}


//发送非应答信号
void iic_sendNOACK(void)
{

    SCL_L; //将时钟线拉低，使数据无效
    iic_out();//将数据线设置为输出模式

    SDA_H;//将数据线拉低
    SCL_H;//拉高时钟线时数据有效
    tim4_delay_us(5);//延时5us，满足IIC时序要求
    SCL_L;//拉低时钟线占用总线


}

//等待应答
uint8_t iic_waitACK(void)
{
    uint16_t tim_out = 0;
    SCL_L; //将时钟线拉低，使数据无效
    iic_in();//将数据线设置为输入模式

    SCL_H; //将时钟线拉低，使数据无效

    while(READ_SDA)
    {
        tim_out++;

        if(tim_out > 500)//超时没有等到应答信号停止本次通信并返回NOACK
        {
            iic_stop();
            return NOACK;
        }
    }

    SCL_L;//拉低时钟线占用总线
    return ACK;


}

//发送数据
void iic_senddata(uint8_t data)
{
    uint8_t i = 0;
    SCL_L; //将时钟线拉低，使数据无效
    iic_out();//将数据线设置为输出模式

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

        SCL_H;//将时钟线拉低，使数据无效
        tim4_delay_us(1);
        SCL_L;
        tim4_delay_us(1);
        data = data << 1;
    }

}

//读取数据
uint8_t iic_readdata(uint8_t flag_ack )
{

    uint8_t read_data = 0, i = 0;
    SCL_L; //将时钟线拉低，使数据无效
    iic_in();//将数据线设置为输入模式

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


