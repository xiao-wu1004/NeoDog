#include "drv_beep.h"
#include "drv_led.h"
#include "drv_systick.h"
/*
函数名：beep_init
函数功能：初始化蜂鸣器
输入参数：无
输出参数：无
其他：beep ->PA15 高电平响
*/
void beep_init()
{

    //开启GPIOA的时钟
    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;//设置引脚数
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz; //设置速率
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT; //设置输出模式
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP; //使能上拉
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP; //设置推挽输出

    //GPIO初始化
    GPIO_Init(GPIOA, &GPIO_InitStruct);
    //设置为低电平 蜂鸣器不响
    GPIO_ResetBits(GPIOA, GPIO_Pin_15);

//    RCC->AHB1ENR |= 0x01 << 0;//开启GPIOA的时钟
//    GPIOA->MODER &= ~(0x03 << 30);//清零
//    GPIOA->MODER |= 0x01 << 30;//配置成输出模式01
//
//	GPIOA->PUPDR &= ~(0x03<<30);
//	GPIOA->PUPDR |=0x01<<30; //配置成上拉模式01
//
//    GPIOA->ODR &= ~(0x01 << 15);//置0（用与和取反）beep默认关闭


}

/*
函数名：beep_ON
函数功能：让蜂鸣器响
输入参数：无
输出参数：无
其他：beep ->PA15 高电平响
*/
void beep_ON()
{

    GPIO_SetBits(GPIOA, GPIO_Pin_15);


//    GPIOA->ODR |= 0x01 << 15;//置1（用或）

}
/*
函数名：beep_OFF
函数功能：让蜂鸣器不响
输入参数：无
输出参数：无
其他：beep ->PA15 高电平响
*/
void beep_OFF()
{

    GPIO_ResetBits(GPIOA, GPIO_Pin_15);

//    GPIOA->ODR &= ~(0x01 << 15);//清0（用与和取反）

}

/*
函数名：beep_Blink
函数功能：beep 闪烁
输入参数：无
输出参数：无
其他：beep ->PA15 高电平响
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
