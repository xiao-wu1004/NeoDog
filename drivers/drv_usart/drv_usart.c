
#include "drv_all.h"

/**
  *  ��ʼ��USART2��USART6

  */
void usart_2_6_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    USART_InitTypeDef USART_InitStruct;
    NVIC_InitTypeDef NVIC_InitStruct;

    /*------------------------ USART2 ���� ------------------------*/
    // 1. ʹ��ʱ��
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

    // 2. ����GPIOA2(TX)��GPIOA3(RX)
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    // 3. ���Ÿ�������
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);

    // 4. USART��������
    USART_InitStruct.USART_BaudRate = 115200;
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;
    USART_InitStruct.USART_StopBits = USART_StopBits_1;
    USART_InitStruct.USART_Parity = USART_Parity_No;
    USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_Init(USART2, &USART_InitStruct);

    // 5. �ж�����
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//���������ж�
    USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);//���������ж�
    NVIC_InitStruct.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);

    // 6. ʹ��USART2
    USART_ClearFlag(USART2, USART_FLAG_TC);
    USART_Cmd(USART2, ENABLE);

    /*------------------------ USART6 ���� ------------------------*/
    // 1. ʹ��ʱ��
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);

    // 2. ����GPIOG9(TX)��GPIOG14(RX)
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_14;
    GPIO_Init(GPIOG, &GPIO_InitStruct); // ������USART2��ͬ�������ظ�����

    // 3. ���Ÿ�������
    GPIO_PinAFConfig(GPIOG, GPIO_PinSource9, GPIO_AF_USART6);
    GPIO_PinAFConfig(GPIOG, GPIO_PinSource14, GPIO_AF_USART6);

    // 4. USART�������ã���USART2��ͬ��
    USART_Init(USART6, &USART_InitStruct);

    // 5. �ж�����
    USART_ITConfig(USART6, USART_IT_RXNE, ENABLE);
    USART_ITConfig(USART6, USART_IT_IDLE, ENABLE);
    NVIC_InitStruct.NVIC_IRQChannel = USART6_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStruct);

    // 6. ʹ��USART6
    USART_ClearFlag(USART6, USART_FLAG_TC);
    USART_Cmd(USART6, ENABLE);

    /*------------------------ ��ӡ��ʼ����Ϣ ------------------------*/
    //printf("USART2 & USART6 ��ʼ���ɹ�\r\n");
}



////��дfputc����
//int fputc(int ch, FILE * f)
//{
//	USART_SendData(USART6, ch); 					//ͨ������6��������
//	while (USART_GetFlagStatus(USART6, USART_FLAG_TC) == RESET)
//		; //�ȴ��������
//	USART_ClearFlag(USART6, USART_FLAG_TC); 		//��շ�����ɵı�־
//	return ch;
//}

/*����3�ĳ�ʼ��(WIFI)
RX PB11
TX PB10
*/
void usart3_init(void)
{

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); //����GPIOB��ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;		//����ģʽ
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP; 	//�������
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11; //��������
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;	//��������
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;		//����
	GPIO_Init(GPIOB, &GPIO_InitStruct); 			//��ʼ��GPIOA

	USART_InitTypeDef USART_InitStruct;
	USART_InitStruct.USART_BaudRate = 115200;		//������
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //��Ӳ��������
	USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_InitStruct.USART_Parity = USART_Parity_No; //��У��λ
	USART_InitStruct.USART_StopBits = USART_StopBits_1; //һλֹͣλ
	USART_InitStruct.USART_WordLength = USART_WordLength_8b; //��λ����λ
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3);
	USART_Init(USART3, &USART_InitStruct);
	
	
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);	//���������ж�
	USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);	//���������ж�
	NVIC_InitTypeDef NVIC_InitStruct;

	//�����ж�
	NVIC_InitStruct.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1; //��ռ���ȼ�   ����ԽС�����ȼ�Խ��
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1; //��Ӧ���ȼ�   ����ԽС�����ȼ�Խ��
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);

	
	USART_ClearFlag(USART3, USART_FLAG_TC); 		//��շ�����ɵı�־���������ɵ�һ����ĸ�Ķ�ʧ
	USART_Cmd(USART3, ENABLE);
	//printf("usart3��ʼ���ɹ�\r\n");
}


///**
//  * @brief  ͳһ���ڳ�ʼ������
//  * @note   ��ʼ��USART2��USART3��USART6
//  */
//void usart_all_init(void)
//{
//    GPIO_InitTypeDef GPIO_InitStruct;
//    USART_InitTypeDef USART_InitStruct;
//    NVIC_InitTypeDef NVIC_InitStruct;
//    
//    /*------------------------ ͨ��USART�������� ------------------------*/
//    USART_InitStruct.USART_BaudRate = 115200;
//    USART_InitStruct.USART_WordLength = USART_WordLength_8b;
//    USART_InitStruct.USART_StopBits = USART_StopBits_1;
//    USART_InitStruct.USART_Parity = USART_Parity_No;
//    USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
//    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
//    
//    /*------------------------ USART2 ���� ------------------------*/
//    // 1. ʹ��ʱ��
//    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

//    // 2. ����GPIOA2(TX)��GPIOA3(RX)
//    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
//    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
//    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
//    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
//    GPIO_Init(GPIOA, &GPIO_InitStruct);

//    // 3. ���Ÿ�������
//    GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
//    GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);

//    // 4. USART��������
//    USART_Init(USART2, &USART_InitStruct);

//    // 5. �ж�����
//    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
//    USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);
//    NVIC_InitStruct.NVIC_IRQChannel = USART2_IRQn;
//    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
//    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
//    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStruct);

//    // 6. ʹ��USART2
//    USART_ClearFlag(USART2, USART_FLAG_TC);
//    USART_Cmd(USART2, ENABLE);

//    /*------------------------ USART3 ���� ------------------------*/
//    // 1. ʹ��ʱ��
//    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

//    // 2. ����GPIOB10(TX)��GPIOB11(RX)
//    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
//    GPIO_Init(GPIOB, &GPIO_InitStruct); // ������USART2��ͬ

//    // 3. ���Ÿ�������
//    GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3);
//    GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3);

//    // 4. USART��������
//    USART_Init(USART3, &USART_InitStruct);

//    // 5. �ж�����
//    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
//	USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);
//    NVIC_InitStruct.NVIC_IRQChannel = USART3_IRQn;
//    NVIC_Init(&NVIC_InitStruct); // ����������USART2��ͬ

//    // 6. ʹ��USART3
//    USART_ClearFlag(USART3, USART_FLAG_TC);
//    USART_Cmd(USART3, ENABLE);

//    /*------------------------ USART6 ���� ------------------------*/
//    // 1. ʹ��ʱ��
//    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);

//    // 2. ����GPIOG9(TX)��GPIOG14(RX)
//    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_14;
//    GPIO_Init(GPIOG, &GPIO_InitStruct); // ������USART2��ͬ

//    // 3. ���Ÿ�������
//    GPIO_PinAFConfig(GPIOG, GPIO_PinSource9, GPIO_AF_USART6);
//    GPIO_PinAFConfig(GPIOG, GPIO_PinSource14, GPIO_AF_USART6);

//    // 4. USART��������
//    USART_Init(USART6, &USART_InitStruct);

//    // 5. �ж�����
//    USART_ITConfig(USART6, USART_IT_RXNE, ENABLE);
//    USART_ITConfig(USART6, USART_IT_IDLE, ENABLE);
//    NVIC_InitStruct.NVIC_IRQChannel = USART6_IRQn;
//    NVIC_Init(&NVIC_InitStruct); // ����������USART2��ͬ

//    // 6. ʹ��USART6
//    USART_ClearFlag(USART6, USART_FLAG_TC);
//    USART_Cmd(USART6, ENABLE);
//    
//    printf("All USARTs initialized successfully\r\n");
//}

//��дfputc����
int fputc(int ch, FILE * f)
{
    USART_SendData(USART6, ch); 					//ͨ������6��������

    while (USART_GetFlagStatus(USART6, USART_FLAG_TC) == RESET); //�ȴ��������

    USART_ClearFlag(USART6, USART_FLAG_TC); 		//��շ�����ɵı�־
    return ch;
}


