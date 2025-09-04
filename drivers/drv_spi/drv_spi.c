

#include "drv_all.h"

//mosi PB15
//miso PB14
//sck PB13
//nss PB12
void spi2_init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15 | GPIO_Pin_14 | GPIO_Pin_13;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_SPI2);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource14, GPIO_AF_SPI2);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_SPI2);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
	GPIO_Init(GPIOB, &GPIO_InitStruct);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
	SPI_InitTypeDef SPI_InitStruct;

	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2; //spi时钟分频
	SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge;		//第二个边沿采样
	SPI_InitStruct.SPI_CPOL = SPI_CPOL_High;		//时钟线空闲时为高
	SPI_InitStruct.SPI_CRCPolynomial = 7;			//crc校验，默认为7
	SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;	//数据位8位
	SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex; //全双工
	SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB; //数据高位先行
	SPI_InitStruct.SPI_Mode = SPI_Mode_Master;		//主机模式
	SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;			//片选由软件控制
	SPI_Init(SPI2, &SPI_InitStruct);
	SPI_Cmd(SPI2, ENABLE);
	GPIO_SetBits(GPIOB, GPIO_Pin_12);//拉高片选，默认不选中设备
}


void spi2_senddata(uint8_t data)
{
	while (SPI_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);//等上次数据发送完后才能继续发数据

	SPI_I2S_SendData(SPI2, data);
}


