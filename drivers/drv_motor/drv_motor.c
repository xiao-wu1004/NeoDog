#include "drv_motor.h"
/*
函数名：motor_init
函数功能：初始化马达
输入参数：无
输出参数：无
其他：motor ->PC7 高电平开
*/
void motor_init()
{
	RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOC, ENABLE);

    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;//设置引脚数
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz; //设置速率
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT; //设置输出模式
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP; //使能上拉
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP; //设置推挽输出
	GPIO_ResetBits(GPIOC,GPIO_Pin_7);//默认关闭motor
	GPIO_Init(GPIOC,&GPIO_InitStruct);
}

/*
函数名：motor_ON
函数功能：启动马达
输入参数：无
输出参数：无
其他：motor ->PC7 高电平开
*/
void motor_ON()
{
	GPIO_SetBits(GPIOC,GPIO_Pin_7);//打开motor
}

/*
函数名：motor_OFF
函数功能：关闭马达
输入参数：无
输出参数：无
其他：motor ->PC7 高电平开
*/
void motor_OFF()
{
	GPIO_ResetBits(GPIOC,GPIO_Pin_7);//关闭motor
}
