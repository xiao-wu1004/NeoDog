
#include "drv_all.h"

//�������ĳ�ʼ��
void usart6_init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE); //����GPIOG��ʱ��
	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;		//����ģʽ
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP; 	//�������
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_14; //��������
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;	//��������
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;		//����
	GPIO_Init(GPIOG, &GPIO_InitStruct); 			//��ʼ��GPIOG

	USART_InitTypeDef USART_InitStruct;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource9, GPIO_AF_USART6);
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource14, GPIO_AF_USART6);
	USART_ITConfig(USART6, USART_IT_RXNE, ENABLE);	//���������ж�
	USART_ITConfig(USART6, USART_IT_IDLE, ENABLE);	//���������ж�
	NVIC_InitTypeDef NVIC_InitStruct;

	//�����ж�
	NVIC_InitStruct.NVIC_IRQChannel = USART6_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1; //��ռ���ȼ�
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1; //��Ӧ���ȼ�
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);

	USART_InitStruct.USART_BaudRate = 115200;		//������
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //��Ӳ��������
	USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_InitStruct.USART_Parity = USART_Parity_No; //��У��λ
	USART_InitStruct.USART_StopBits = USART_StopBits_1; //һλֹͣλ
	USART_InitStruct.USART_WordLength = USART_WordLength_8b; //��λ����λ
	USART_Init(USART6, &USART_InitStruct);
	USART_ClearFlag(USART6, USART_FLAG_TC); 		//��շ�����ɵı�־���������ɵ�һ����ĸ�Ķ�ʧ
	USART_Cmd(USART6, ENABLE);
}


//��дfputc����
//int fputc(int ch, FILE * f)
//{
//	USART_SendData(USART6, ch); 					//ͨ������6��������

//	while (USART_GetFlagStatus(USART6, USART_FLAG_TC) == RESET)
//		; //�ȴ��������

//	USART_ClearFlag(USART6, USART_FLAG_TC); 		//��շ�����ɵı�־
//	return ch;
//}


/*����2�ĳ�ʼ��
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

	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);	//���������ж�
	USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);	//���������ж�
	NVIC_InitTypeDef NVIC_InitStruct;

	//����2�ж�
	NVIC_InitStruct.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1; //��ռ���ȼ�
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1; //��Ӧ���ȼ�
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	USART_InitTypeDef USART_InitStruct;

	USART_InitStruct.USART_BaudRate = 115200;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStruct.USART_Parity = USART_Parity_No; //û��У��λ
	USART_InitStruct.USART_StopBits = USART_StopBits_1; //һλֹͣλ
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART2, &USART_InitStruct);
	USART_ClearFlag(USART2, USART_FLAG_TC); 		//��շ�����ɵı�־���������ɵ�һ����ĸ�Ķ�ʧ
	USART_Cmd(USART2, ENABLE);

}


