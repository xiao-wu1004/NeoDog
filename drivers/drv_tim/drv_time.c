
#include "drv_all.h"
volatile  uint8_t delay_done = 1; // 延时完成标志
//tim7初始化 实现led1每隔一秒亮一次
void tim7_init(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStruct.TIM_Period = 0xffff;
    TIM_TimeBaseInitStruct.TIM_Prescaler = 84 - 1;
    //TIM_TimeBaseInitStruct.TIM_RepetitionCounter=;This parameter is valid only for TIM1 and TIM8
    
    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = TIM7_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);
    TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);
    //TIM_Cmd(TIM7, ENABLE);
	
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseInitStruct);
    TIM_ARRPreloadConfig(TIM7, ENABLE);
    TIM_ClearFlag(TIM7, TIM_FLAG_Update);
}

void tim7_delay_ms(uint32_t ms)
{
    //uint32_t total = ms ; //分段数 为什么是6553（65535/10），因为跟预分频8400有关
    while (ms > 0)
    {
        uint16_t chunk = (ms > 65) ? 65 : ms;  // Max 65ms per chunk for 1us/count
        // Clear the update flag BEFORE configuring the timer for the new delay.
        // This prevents potential issues if the flag was already set.
        TIM7->SR = ~TIM_FLAG_Update;
        TIM7->CNT = 0;                        // Reset counter
        TIM7->ARR = chunk * 1000 - 1;         // Set auto-reload value for the chunk
        TIM7->EGR |= TIM_EGR_UG;              // Generate an update event to load ARR and reset CNT

        // Wait for the update flag to be set, indicating the period has elapsed
        while (!(TIM7->SR & TIM_FLAG_Update));

        // Clear the update flag for the next iteration (or next timer usage)
        TIM7->SR = ~TIM_FLAG_Update;
        ms -= chunk;
    }
}
//void TIM7_Delay_ms(uint32_t ms)
//{
//    while(ms > 0)
//    {
//        uint16_t chunk = (ms > 65) ? 65 : ms;  // 单次最大65ms（防止1MHz下溢出）
//
//        TIM7->CNT = 0;
//        TIM7->ARR = chunk * 1000 - 1;         // 转换为us计数
//        TIM7->EGR |= TIM_EGR_UG;              // 强制更新寄存器
//
//        while(!(TIM7->SR & TIM_FLAG_Update));  // 等待更新事件
//        TIM7->SR &= ~TIM_FLAG_Update;          // 清除标志
//
//        ms -= chunk;
//    }
//}

 
void tim4_delay_init() 
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    
    TIM_TimeBaseStructure.TIM_Period = 84-1;
    TIM_TimeBaseStructure.TIM_Prescaler = 1-1;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
}                                    
 
void tim4_delay_ms(uint16_t ms)
{
    while(ms > 0)
    {
        uint32_t chunk = (ms > 65) ? 65 : ms; // 单次最大65ms（防止uint16_t溢出）
        
        // 设置1us中断一次，累计chunk*1000次
        TIM_SetAutoreload(TIM4, 84 - 1);
        TIM_SetCounter(TIM4, 0);
        TIM_Cmd(TIM4, ENABLE);
        
        for(uint32_t i = 0; i < chunk * 1000; i++)
        {
            while(!TIM_GetFlagStatus(TIM4, TIM_FLAG_Update));
            TIM_ClearFlag(TIM4, TIM_FLAG_Update);
        }
        
        TIM_Cmd(TIM4, DISABLE);
        ms -= chunk;
    }
}   

//延时nus
//nus为要延时的us数.                                               
void tim4_delay_us(uint32_t nus)
{
    uint32_t cnt;
    cnt = nus;
    TIM_Cmd(TIM4, ENABLE);
    while(cnt--)
    {
        while(TIM_GetFlagStatus(TIM4, TIM_FLAG_Update) == RESET);
        TIM_ClearFlag(TIM4, TIM_FLAG_Update);
    }
    TIM_Cmd(TIM4, DISABLE);
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
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
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

//tim3 初始化（实现风扇档位）引脚PC6
//PC 6 7 8 9
void tim3_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOC, &GPIO_InitStruct);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_TIM3);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_TIM3);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource8, GPIO_AF_TIM3);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource9, GPIO_AF_TIM3);
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStruct.TIM_Period = 20000 - 1;
    TIM_TimeBaseInitStruct.TIM_Prescaler = 84 - 1;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);
    //TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
    TIM_OCInitTypeDef TIM_OCInitStruct;
    TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High; //有效电平
    TIM_OCInitStruct.TIM_Pulse = 1500; 				//比较初值
    TIM_OC1Init(TIM3, &TIM_OCInitStruct);
    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable); //开启比较的影子寄存器
    TIM_OCInitStruct.TIM_Pulse = 1500; 				//比较初值
    TIM_OC2Init(TIM3, &TIM_OCInitStruct);
    TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable); //开启比较的影子寄存器
    TIM_OCInitStruct.TIM_Pulse = 1500; 				//比较初值
    TIM_OC3Init(TIM3, &TIM_OCInitStruct);
    TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable); //开启比较的影子寄存器
    TIM_OCInitStruct.TIM_Pulse = 1500; 				//比较初值
    TIM_OC4Init(TIM3, &TIM_OCInitStruct);
    TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable); //开启比较的影子寄存器
    //TIM_ARRPreloadConfig(TIM3, ENABLE);			//开启装载寄存器的影子寄存器
    TIM_CtrlPWMOutputs(TIM3, ENABLE);				//使能PWM输出
    TIM_Cmd(TIM3, ENABLE); 						//使能定时器3
    //printf("tim3 succes\r\n");
}

////tim4 初始化（实现风扇档位）CH1引脚PD12    TIM4 有问题！！！慎用！！！

//void tim4_init(void)
//{
//	GPIO_InitTypeDef GPIO_InitStruct;

//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
//	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
//	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
//	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
//	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
//	GPIO_Init(GPIOD, &GPIO_InitStruct);

//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
//	GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4);
//	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;

//	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
//	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
//	TIM_TimeBaseInitStruct.TIM_Period = 5000 - 1;
//	TIM_TimeBaseInitStruct.TIM_Prescaler = 84 - 1;
//	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStruct);
//	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);

//	TIM_OCInitTypeDef TIM_OCInitStruct;

//	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
//	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
//	TIM_OCInitStruct.TIM_Pulse = 0; 				//比较初值
//	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High; //有效电平
//	TIM_OC1Init(TIM4, &TIM_OCInitStruct);

//	TIM_ARRPreloadConfig(TIM4, ENABLE);			//开启装载寄存器的影子寄存器
//	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable); //开启比较的影子寄存器
//	TIM_CtrlPWMOutputs(TIM4, ENABLE);				//使能PWM输出

//	TIM_Cmd(TIM4, ENABLE); 						//使能定时器3
//	printf("tim4 init succes");
//}



