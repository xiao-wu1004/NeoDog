#ifndef __DRV_IIC_H__
#define __DRV_IIC_H__
#include <stm32f4xx.h>
#define SCL_H					GPIO_SetBits( GPIOB,  GPIO_Pin_6)
#define SCL_L					GPIO_ResetBits( GPIOB,	GPIO_Pin_6)
#define SDA_H					GPIO_SetBits(GPIOB,  GPIO_Pin_7)
#define SDA_L					GPIO_ResetBits(GPIOB,  GPIO_Pin_7)
#define READ_SDA				GPIO_ReadInputDataBit( GPIOB, GPIO_Pin_7)
#define ACK 					0
#define NOACK					1
void iic_init(void);
void iic_in(void);
void iic_out(void);
void iic_start(void);
void iic_stop(void);
void iic_sendACK(void);
void iic_sendNOACK(void);
uint8_t iic_waitACK(void);

void iic_senddata(uint8_t data);

uint8_t iic_readdata(uint8_t flag_ack );
#endif
