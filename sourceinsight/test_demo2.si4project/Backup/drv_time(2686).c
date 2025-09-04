
#include "drv_all.h"

//tim7初始化 实现led1每隔一秒亮一次
void tim7_init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;

	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = 10000 - 1;
	TIM_TimeBaseInitStruct.TIM_Prescaler = 8400 - 1;

	//TIM_TimeBaseInitStruct.TIM_RepetitionCounter=;This parameter is valid only for TIM1 and TIM8
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseInitStruct);

	NVIC_InitTypeDef NVIC_InitStruct;

	NVIC_InitStruct.NVIC_IRQChannel = TIM7_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
	TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM7, ENABLE);
}

//tim13 初始化（实现userled呼吸灯）
void tim13_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOF, &GPIO_InitStruct);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM13, ENABLE);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource8, GPIO_AF_TIM13);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;

	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = 5000 - 1;
	TIM_TimeBaseInitStruct.TIM_Prescaler = 84 - 1;
	TIM_TimeBaseInit(TIM13, &TIM_TimeBaseInitStruct);
	TIM_ITConfig(TIM13, TIM_IT_Update, ENABLE);

	TIM_OCInitTypeDef TIM_OCInitStruct;

	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_Pulse = 0; 				//比较初值
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_Low; //有效电平
	TIM_OC1Init(TIM13, &TIM_OCInitStruct);

	TIM_ARRPreloadConfig(TIM13, ENABLE);			//开启装载寄存器的影子寄存器
	TIM_OC1PreloadConfig(TIM13, TIM_OCPreload_Enable); //开启比较的影子寄存器
	TIM_CtrlPWMOutputs(TIM13, ENABLE);				//使能PWM输出

	TIM_Cmd(TIM13, ENABLE); 						//使能定时器13

}

//tim14 初始化（实现风扇档位）引脚PC6
void tim14_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOC, &GPIO_InitStruct);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource8, GPIO_AF_TIM14);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;

	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = 5000 - 1;
	TIM_TimeBaseInitStruct.TIM_Prescaler = 84 - 1;
	TIM_TimeBaseInit(TIM14, &TIM_TimeBaseInitStruct);
	TIM_ITConfig(TIM14, TIM_IT_Update, ENABLE);

	TIM_OCInitTypeDef TIM_OCInitStruct;

	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_Pulse = 0; 				//比较初值
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High; //有效电平
	TIM_OC1Init(TIM14, &TIM_OCInitStruct);

	TIM_ARRPreloadConfig(TIM14, ENABLE);			//开启装载寄存器的影子寄存器
	TIM_OC1PreloadConfig(TIM14, TIM_OCPreload_Enable); //开启比较的影子寄存器
	TIM_CtrlPWMOutputs(TIM14, ENABLE);				//使能PWM输出

	TIM_Cmd(TIM14, ENABLE); 						//使能定时器13

}



