
#include "drv_all.h"

/**
  *  初始化USART2和USART6

  */
void usart_2_6_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    USART_InitTypeDef USART_InitStruct;
    NVIC_InitTypeDef NVIC_InitStruct;

    /*------------------------ USART2 配置 ------------------------*/
    // 1. 使能时钟
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

    // 2. 配置GPIOA2(TX)和GPIOA3(RX)
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    // 3. 引脚复用配置
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);

    // 4. USART参数配置
    USART_InitStruct.USART_BaudRate = 115200;
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;
    USART_InitStruct.USART_StopBits = USART_StopBits_1;
    USART_InitStruct.USART_Parity = USART_Parity_No;
    USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_Init(USART2, &USART_InitStruct);

    // 5. 中断配置
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启接受中断
    USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);//开启空闲中断
    NVIC_InitStruct.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);

    // 6. 使能USART2
    USART_ClearFlag(USART2, USART_FLAG_TC);
    USART_Cmd(USART2, ENABLE);

    /*------------------------ USART6 配置 ------------------------*/
    // 1. 使能时钟
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);

    // 2. 配置GPIOG9(TX)和GPIOG14(RX)
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_14;
    GPIO_Init(GPIOG, &GPIO_InitStruct); // 参数与USART2相同，无需重复配置

    // 3. 引脚复用配置
    GPIO_PinAFConfig(GPIOG, GPIO_PinSource9, GPIO_AF_USART6);
    GPIO_PinAFConfig(GPIOG, GPIO_PinSource14, GPIO_AF_USART6);

    // 4. USART参数配置（与USART2相同）
    USART_Init(USART6, &USART_InitStruct);

    // 5. 中断配置
    USART_ITConfig(USART6, USART_IT_RXNE, ENABLE);
    USART_ITConfig(USART6, USART_IT_IDLE, ENABLE);
    NVIC_InitStruct.NVIC_IRQChannel = USART6_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStruct);

    // 6. 使能USART6
    USART_ClearFlag(USART6, USART_FLAG_TC);
    USART_Cmd(USART6, ENABLE);

    /*------------------------ 打印初始化信息 ------------------------*/
    //printf("USART2 & USART6 初始化成功\r\n");
}



////改写fputc函数
//int fputc(int ch, FILE * f)
//{
//	USART_SendData(USART6, ch); 					//通过串口6发送数据
//	while (USART_GetFlagStatus(USART6, USART_FLAG_TC) == RESET)
//		; //等待发送完成
//	USART_ClearFlag(USART6, USART_FLAG_TC); 		//清空发送完成的标志
//	return ch;
//}

/*串口3的初始化(WIFI)
RX PB11
TX PB10
*/
void usart3_init(void)
{

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); //开启GPIOB的时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;		//复用模式
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP; 	//推挽输出
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11; //配置引脚
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;	//配置速率
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;		//上拉
	GPIO_Init(GPIOB, &GPIO_InitStruct); 			//初始化GPIOA

	USART_InitTypeDef USART_InitStruct;
	USART_InitStruct.USART_BaudRate = 115200;		//波特率
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //无硬件流控制
	USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_InitStruct.USART_Parity = USART_Parity_No; //无校验位
	USART_InitStruct.USART_StopBits = USART_StopBits_1; //一位停止位
	USART_InitStruct.USART_WordLength = USART_WordLength_8b; //八位数据位
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3);
	USART_Init(USART3, &USART_InitStruct);
	
	
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);	//开启接收中断
	USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);	//开启空闲中断
	NVIC_InitTypeDef NVIC_InitStruct;

	//串口中断
	NVIC_InitStruct.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1; //抢占优先级   数字越小，优先级越高
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1; //响应优先级   数字越小，优先级越高
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);

	
	USART_ClearFlag(USART3, USART_FLAG_TC); 		//清空发送完成的标志，否则会造成第一个字母的丢失
	USART_Cmd(USART3, ENABLE);
	//printf("usart3初始化成功\r\n");
}


///**
//  * @brief  统一串口初始化函数
//  * @note   初始化USART2、USART3和USART6
//  */
//void usart_all_init(void)
//{
//    GPIO_InitTypeDef GPIO_InitStruct;
//    USART_InitTypeDef USART_InitStruct;
//    NVIC_InitTypeDef NVIC_InitStruct;
//    
//    /*------------------------ 通用USART参数配置 ------------------------*/
//    USART_InitStruct.USART_BaudRate = 115200;
//    USART_InitStruct.USART_WordLength = USART_WordLength_8b;
//    USART_InitStruct.USART_StopBits = USART_StopBits_1;
//    USART_InitStruct.USART_Parity = USART_Parity_No;
//    USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
//    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
//    
//    /*------------------------ USART2 配置 ------------------------*/
//    // 1. 使能时钟
//    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

//    // 2. 配置GPIOA2(TX)和GPIOA3(RX)
//    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
//    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
//    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
//    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
//    GPIO_Init(GPIOA, &GPIO_InitStruct);

//    // 3. 引脚复用配置
//    GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
//    GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);

//    // 4. USART参数配置
//    USART_Init(USART2, &USART_InitStruct);

//    // 5. 中断配置
//    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
//    USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);
//    NVIC_InitStruct.NVIC_IRQChannel = USART2_IRQn;
//    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
//    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
//    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStruct);

//    // 6. 使能USART2
//    USART_ClearFlag(USART2, USART_FLAG_TC);
//    USART_Cmd(USART2, ENABLE);

//    /*------------------------ USART3 配置 ------------------------*/
//    // 1. 使能时钟
//    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

//    // 2. 配置GPIOB10(TX)和GPIOB11(RX)
//    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
//    GPIO_Init(GPIOB, &GPIO_InitStruct); // 参数与USART2相同

//    // 3. 引脚复用配置
//    GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3);
//    GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3);

//    // 4. USART参数配置
//    USART_Init(USART3, &USART_InitStruct);

//    // 5. 中断配置
//    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
//	USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);
//    NVIC_InitStruct.NVIC_IRQChannel = USART3_IRQn;
//    NVIC_Init(&NVIC_InitStruct); // 其他参数与USART2相同

//    // 6. 使能USART3
//    USART_ClearFlag(USART3, USART_FLAG_TC);
//    USART_Cmd(USART3, ENABLE);

//    /*------------------------ USART6 配置 ------------------------*/
//    // 1. 使能时钟
//    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);

//    // 2. 配置GPIOG9(TX)和GPIOG14(RX)
//    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_14;
//    GPIO_Init(GPIOG, &GPIO_InitStruct); // 参数与USART2相同

//    // 3. 引脚复用配置
//    GPIO_PinAFConfig(GPIOG, GPIO_PinSource9, GPIO_AF_USART6);
//    GPIO_PinAFConfig(GPIOG, GPIO_PinSource14, GPIO_AF_USART6);

//    // 4. USART参数配置
//    USART_Init(USART6, &USART_InitStruct);

//    // 5. 中断配置
//    USART_ITConfig(USART6, USART_IT_RXNE, ENABLE);
//    USART_ITConfig(USART6, USART_IT_IDLE, ENABLE);
//    NVIC_InitStruct.NVIC_IRQChannel = USART6_IRQn;
//    NVIC_Init(&NVIC_InitStruct); // 其他参数与USART2相同

//    // 6. 使能USART6
//    USART_ClearFlag(USART6, USART_FLAG_TC);
//    USART_Cmd(USART6, ENABLE);
//    
//    printf("All USARTs initialized successfully\r\n");
//}

//改写fputc函数
int fputc(int ch, FILE * f)
{
    USART_SendData(USART6, ch); 					//通过串口6发送数据

    while (USART_GetFlagStatus(USART6, USART_FLAG_TC) == RESET); //等待发送完成

    USART_ClearFlag(USART6, USART_FLAG_TC); 		//清空发送完成的标志
    return ch;
}


