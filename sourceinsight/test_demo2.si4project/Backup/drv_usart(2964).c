
#include "drv_all.h"

//串口六的初始化
void usart6_init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE); //开启GPIOG的时钟
	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;		//复用模式
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP; 	//推挽输出
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_14; //配置引脚
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;	//配置速率
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;		//上拉
	GPIO_Init(GPIOG, &GPIO_InitStruct); 			//初始化GPIOG

	USART_InitTypeDef USART_InitStruct;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource9, GPIO_AF_USART6);
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource14, GPIO_AF_USART6);
	USART_ITConfig(USART6, USART_IT_RXNE, ENABLE);	//开启接收中断
	USART_ITConfig(USART6, USART_IT_IDLE, ENABLE);	//开启空闲中断
	NVIC_InitTypeDef NVIC_InitStruct;

	//串口中断
	NVIC_InitStruct.NVIC_IRQChannel = USART6_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1; //抢占优先级
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1; //响应优先级
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);

	USART_InitStruct.USART_BaudRate = 115200;		//波特率
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //无硬件流控制
	USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_InitStruct.USART_Parity = USART_Parity_No; //无校验位
	USART_InitStruct.USART_StopBits = USART_StopBits_1; //一位停止位
	USART_InitStruct.USART_WordLength = USART_WordLength_8b; //八位数据位
	USART_Init(USART6, &USART_InitStruct);
	USART_ClearFlag(USART6, USART_FLAG_TC); 		//清空发送完成的标志，否则会造成第一个字母的丢失
	USART_Cmd(USART6, ENABLE);
}


//改写fputc函数
//int fputc(int ch, FILE * f)
//{
//	USART_SendData(USART6, ch); 					//通过串口6发送数据

//	while (USART_GetFlagStatus(USART6, USART_FLAG_TC) == RESET)
//		; //等待发送完成

//	USART_ClearFlag(USART6, USART_FLAG_TC); 		//清空发送完成的标志
//	return ch;
//}


/*串口2的初始化
RX PA3
TX PA2
*/
void usart2_init()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_2;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);

	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);	//开启接收中断
	USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);	//开启空闲中断
	NVIC_InitTypeDef NVIC_InitStruct;

	//串口2中断
	NVIC_InitStruct.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1; //抢占优先级
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1; //响应优先级
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	USART_InitTypeDef USART_InitStruct;

	USART_InitStruct.USART_BaudRate = 115200;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStruct.USART_Parity = USART_Parity_No; //没有校验位
	USART_InitStruct.USART_StopBits = USART_StopBits_1; //一位停止位
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART2, &USART_InitStruct);
	USART_ClearFlag(USART2, USART_FLAG_TC); 		//清空发送完成的标志，否则会造成第一个字母的丢失
	USART_Cmd(USART2, ENABLE);

}


