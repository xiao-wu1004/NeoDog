#include "drv_fan.h"
/*
函数名：fan_init
函数功能：初始化fan
输入参数：无
输出参数：无
其他：fan ->PC6 高电平开
*/
void fan_init()
{
    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOC, ENABLE);

    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;//设置引脚数
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz; //设置速率
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT; //设置输出模式
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP; //使能上拉

    GPIO_Init(GPIOC, &GPIO_InitStruct);
    GPIO_ResetBits(GPIOC, GPIO_Pin_6); //默认关闭fan
}

/*
函数名：fan_ON
函数功能：开启fan
输入参数：无
输出参数：无
其他：fan ->PC6 高电平开
*/
void fan_ON()
{
    GPIO_SetBits(GPIOC, GPIO_Pin_6); //打开fan
}

/*
函数名：fan_OFF
函数功能：关闭fan
输入参数：无
输出参数：无
其他：fan ->PC6 高电平开
*/
void fan_OFF()
{
    GPIO_ResetBits(GPIOC, GPIO_Pin_6); //关闭fan

}
