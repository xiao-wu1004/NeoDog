#include "drv_all.h"

/*
user����->PF9
key2 PC8
key3 PC5
�����жϵĳ�ʼ��
*/
void exti9_init(void)
{
    // ͳһ��ʼ������

    GPIO_InitTypeDef GPIO_InitStruct;
    
    // ����ʱ��
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF | RCC_AHB1Periph_GPIOC, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    
    // ����PF9 (USER����)
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOF, &GPIO_InitStruct);
    
    // ����PC8��PC5 (KEY2��KEY3)
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_5;
    GPIO_Init(GPIOC, &GPIO_InitStruct);
    
    // �����ⲿ�ж���
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource9);
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource8);
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource5);
    
    // �����ⲿ�ж�
    EXTI_InitTypeDef EXTI_InitStruct;
    EXTI_InitStruct.EXTI_Line = EXTI_Line9 | EXTI_Line8 | EXTI_Line5;
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStruct);
    
    // ����NVIC
    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = EXTI9_5_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);

}

/*
key1 PC9
key2 PC8
key3 PC5
*/
//void exti_key3_1_init(void)
//{
//    GPIO_InitTypeDef GPIO_InitStruct;
//    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//��GPIOC��ʱ��
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
//    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
//    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_5;
//    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
//    GPIO_Init(GPIOC, &GPIO_InitStruct);


//    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource8);
//    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource5);

//    EXTI_InitTypeDef EXTI_InitStruct;
//    EXTI_InitStruct.EXTI_Line = EXTI_Line8 | EXTI_Line5;
//    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
//    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
//    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
//    EXTI_Init(&EXTI_InitStruct);

//    NVIC_InitTypeDef NVIC_InitStruct;
//    NVIC_InitStruct.NVIC_IRQChannel = EXTI9_5_IRQn;
//    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
//    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
//    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStruct);
//}
