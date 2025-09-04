#include "drv_all.h"
sht20_val tem_hum_data;
/*
函数名：sht20_init
函数功能：sht20的初始化
输入参数：无
输出参数：无
其他：
*/

void sht20_init()
{
    iic_init();
}
/*
函数名：sht20_read_T
函数功能：sht20读取温度数据
输入参数：无
输出参数：温度原始值
其他：
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
函数名：sht20_getTdata
函数功能：sht20获取温度数据
输入参数：无
输出参数：无
其他：
*/
void sht20_getTdata()
{
	uint16_t temp=0;
	temp=sht20_read_T();
	tem_hum_data.tem=-46.85+(175.72/65536.00)*(float)temp;
	printf("temp=%.2f",tem_hum_data.tem);
}

/*
函数名：sht20_read_RH
函数功能：sht20读取湿度数据
输入参数：无
输出参数：湿度原始值
其他：
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
函数名：sht20_getRHdata
函数功能：sht20获取湿度数据
输入参数：无
输出参数：无
其他：
*/
void sht20_getRHdata()
{
	uint16_t temp=0;
	temp=sht20_read_RH();
	tem_hum_data.hum=-6+(125/65536.00)*(float)temp;
	printf("RH=%.2f",tem_hum_data.hum);
	printf("%%");
}
