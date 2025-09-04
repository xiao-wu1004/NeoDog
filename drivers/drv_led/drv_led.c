#include "drv_all.h"
/*
函数名：led_Init
函数功能：初始化led
输入参数：无
输出参数：无
其他：led ->PF8 低电平亮
*/
void led_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    //打开外部时钟
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF | RCC_AHB1Periph_GPIOC, ENABLE);
    //    RCC->AHB1ENR = 0x01 << 5;
    //    GPIOF->MODER &= ~(0x03 << 16); //清零
    //    GPIOF->MODER |= 0x01 << 16; //输出模式01
    //    GPIOF->BSRRL |= 0x01 << 8; //灭灯 置位 低16位
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8; //设置引脚数
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT; //设置输出模式
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz; //设置速率
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP; //使能上拉
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP; //设置推挽输出
    //GPIOF初始化
    GPIO_Init(GPIOF, &GPIO_InitStruct);
    //设置为高电平 led熄灭
    GPIO_SetBits(GPIOF, GPIO_Pin_8);
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_3 | GPIO_Pin_13; //设置引脚数
    //GPIOC初始化
    GPIO_Init(GPIOC, &GPIO_InitStruct);
    //设置为高电平 led熄灭
    GPIO_ResetBits(GPIOC, GPIO_Pin_4 | GPIO_Pin_3 | GPIO_Pin_13);
}

//void led3_1_init(void)
//{
//    GPIO_InitTypeDef GPIO_InitStruct3;
//    //打开外部时钟
//    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

//    GPIO_InitStruct3.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_3 | GPIO_Pin_13; //设置引脚数
//    GPIO_InitStruct3.GPIO_Mode = GPIO_Mode_OUT; //设置输出模式
//    GPIO_InitStruct3.GPIO_Speed = GPIO_Speed_2MHz; //设置速率
//    GPIO_InitStruct3.GPIO_PuPd = GPIO_PuPd_UP; //使能上拉
//    GPIO_InitStruct3.GPIO_OType = GPIO_OType_PP; //设置推挽输出

//    //GPIO初始化
//    GPIO_Init(GPIOC, &GPIO_InitStruct3);

//    //设置为高电平 led熄灭
//    GPIO_ResetBits(GPIOC, GPIO_Pin_4 | GPIO_Pin_3 | GPIO_Pin_13);
//}


/*
函数名：led_ON
函数功能：点亮led
输入参数：无
输出参数：无
其他：led ->PF8 低电平亮
*/
void led_ON(void)
{
    //printf("userled ON\r\n");
    GPIO_ResetBits(GPIOF, GPIO_Pin_8);
    //GPIOF->BSRRH |=(0x01 << 8); //亮灯 复位  高16位
}


/*
函数名：led_OFF
函数功能：熄灭led
输入参数：无
输出参数：无
其他：led ->PF8 高电平灭
*/
void led_OFF(void)
{
    GPIO_SetBits(GPIOF, GPIO_Pin_8);
    //GPIOF->BSRRL |= 0x01 << 8; //灭灯 置位 低16位
}

/*
函数名：delay_ms
函数功能：粗略的ms延时
输入参数：ms数
输出参数：无
其他：无
*/
void delay_ms(uint32_t ms)
{
    uint32_t i, j;

    for (i = 0; i < ms; i++)
    {
        for (j = 0; j < 0xfff; j++);
    }
}

// 微秒级延时（粗略估计）
void delay_us(unsigned int us)
{
    for (volatile unsigned int i = 0; i < us; i++)
    {
        // 空循环，具体循环次数需要根据CPU频率调整
        for (volatile unsigned int j = 0; j < 10; j++)
        {
            // 更小的空循环
        }
    }
}
/*
函数名：led_Blink
函数功能：led 闪烁
输入参数：无
输出参数：无
其他：led ->PF8 低电平亮
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
函数名：led1_ON
函数功能：点亮led1
输入参数：无
输出参数：无
其他：led1 ->PC4 低电平亮
*/
void led1_ON(void)
{
    GPIO_SetBits(GPIOC, GPIO_Pin_4);
}


/*
函数名：led1_OFF
函数功能：熄灭led1
输入参数：无
输出参数：无
其他：led1 ->PC4 高电平灭
*/
void led1_OFF(void)
{
    GPIO_ResetBits(GPIOC, GPIO_Pin_4);
}

/*
函数名：led2_ON
函数功能：点亮led2
输入参数：无
输出参数：无
其他：led2 ->PC3 低电平亮
*/
void led2_ON(void)
{
    GPIO_SetBits(GPIOC, GPIO_Pin_3);
}


/*
函数名：led2_OFF
函数功能：熄灭led2
输入参数：无
输出参数：无
其他：led2 ->PC3 高电平灭
*/
void led2_OFF(void)
{
    GPIO_ResetBits(GPIOC, GPIO_Pin_3);
}

/*
函数名：led3_ON
函数功能：点亮led3
输入参数：无
输出参数：无
其他：led3 ->PC13 低电平亮
*/
void led3_ON(void)
{
    GPIO_SetBits(GPIOC, GPIO_Pin_13);
}


/*
函数名：led3_OFF
函数功能：熄灭led3
输入参数：无
输出参数：无
其他：led3 ->PC13 高电平灭
*/
void led3_OFF(void)
{
    GPIO_ResetBits(GPIOC, GPIO_Pin_13);
}

/*
函数名：led3_OFF
函数功能：熄灭led3
输入参数：无
输出参数：无
其他：led3 ->PC13 高电平灭
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

//打开led1 led2 led3
void all_led_ON(void)
{
    GPIO_SetBits(GPIOC, GPIO_Pin_4);
    GPIO_SetBits(GPIOC, GPIO_Pin_3);
    GPIO_SetBits(GPIOC, GPIO_Pin_13);
}

//关闭led1 led2 led3
void all_led_OFF(void)
{
    GPIO_ResetBits(GPIOC, GPIO_Pin_4);
    GPIO_ResetBits(GPIOC, GPIO_Pin_3);
    GPIO_ResetBits(GPIOC, GPIO_Pin_13);
}
