#include "drv_all.h"
sht20_val tem_hum_data;
/*
��������sht20_init
�������ܣ�sht20�ĳ�ʼ��
�����������
�����������
������
*/

void sht20_init()
{
    iic_init();
}
/*
��������sht20_read_T
�������ܣ�sht20��ȡ�¶�����
�����������
����������¶�ԭʼֵ
������
*/
uint16_t sht20_read_T()
{
	uint8_t data[2];
	uint16_t ret=0;
    iic_start();
    iic_senddata(0x80);

    if (iic_waitACK() != ACK)
    {
        iic_stop();
        return NOACK;
    }
	iic_senddata(0xe3);
	
	if(iic_waitACK()!=ACK)
	{
		iic_stop();
		return NOACK;
	}
	iic_start();
	
	iic_senddata(0x81);
	if(iic_waitACK()!=ACK)
	{
		iic_stop();
		return NOACK;
	}
	drv_systick_ms(85);
	
	data[0]=iic_readdata(ACK);
	//printf("data[0]=%o ",data[0]);
	
	data[1]=iic_readdata(NOACK);
	//printf("data[1]=%o ",data[1]);
	ret=((data[0]<<8)|data[1]);
	return ret;
}

/*
��������sht20_getTdata
�������ܣ�sht20��ȡ�¶�����
�����������
�����������
������
*/
void sht20_getTdata()
{
	uint16_t temp=0;
	temp=sht20_read_T();
	tem_hum_data.tem=-46.85+(175.72/65536.00)*(float)temp;
	printf("temp=%.2f",tem_hum_data.tem);
}

/*
��������sht20_read_RH
�������ܣ�sht20��ȡʪ������
�����������
���������ʪ��ԭʼֵ
������
*/
uint16_t sht20_read_RH()
{
	uint8_t data[2];
	uint16_t ret=0;
    iic_start();
    iic_senddata(0x80);

    if (iic_waitACK() != ACK)
    {
        iic_stop();
        return NOACK;
    }
	iic_senddata(0xe5);
	
	if(iic_waitACK()!=ACK)
	{
		iic_stop();
		return NOACK;
	}
	iic_start();
	
	iic_senddata(0x81);
	if(iic_waitACK()!=ACK)
	{
		iic_stop();
		return NOACK;
	}
	drv_systick_ms(29);
	
	data[0]=iic_readdata(ACK);
	data[1]=iic_readdata(NOACK);
	ret=((data[0]<<8)|data[1]);
	return ret;
}

/*
��������sht20_getRHdata
�������ܣ�sht20��ȡʪ������
�����������
�����������
������
*/
void sht20_getRHdata()
{
	uint16_t temp=0;
	temp=sht20_read_RH();
	tem_hum_data.hum=-6+(125/65536.00)*(float)temp;
	printf("RH=%.2f",tem_hum_data.hum);
	printf("%%");
}
