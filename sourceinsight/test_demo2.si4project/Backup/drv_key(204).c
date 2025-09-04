
#include "drv_all.h"

#define USER_KEY_PIN			GPIO_Pin_9
#define KEY1_PIN				GPIO_Pin_9
#define KEY2_PIN				GPIO_Pin_8
#define KEY3_PIN				GPIO_Pin_5

#define USER_KEY				GPIO_ReadInputDataBit( GPIOF,  GPIO_Pin_9)
#define KEY1					GPIO_ReadInputDataBit( GPIOC,  GPIO_Pin_9)
#define KEY2					GPIO_ReadInputDataBit( GPIOC,  GPIO_Pin_8)
#define KEY3					GPIO_ReadInputDataBit( GPIOC,  GPIO_Pin_5)


//user-key的初始化
void key_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOF, &GPIO_InitStruct);


}


//key1 key2 key3的初始化
void key_init1(void)
{
	GPIO_InitTypeDef GPIO_InitStruct1;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	GPIO_InitStruct1.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct1.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_8 | GPIO_Pin_5;
	GPIO_InitStruct1.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOC, &GPIO_InitStruct1);

}


//按键检测函数
uint8_t key_state()
{
	if (!USER_KEY || !KEY1 || !KEY2 || !KEY3)
		{
		drv_systick_ms(10);

		if (!USER_KEY)
			{
				while(USER_KEY);
			}

		if (!KEY1)
			{

			}

		if (!KEY2)
			{

			}

		if (!KEY3)
			{

			}
		}
}


uint8_t key_scan(void)
{
	uint8_t 		user_key_flag;

	user_key_flag		= 0;

	//user按键控制蜂鸣器
	if (GPIO_ReadInputDataBit(GPIOF, USER_KEY_PIN) == RESET)
		{

		drv_systick_ms(20);

		if (GPIO_ReadInputDataBit(GPIOF, USER_KEY_PIN) == RESET)
			{
			while (GPIO_ReadInputDataBit(GPIOF, USER_KEY_PIN) == SET)
				;

			user_key_flag		= ~user_key_flag;
			return user_key_flag;
			}

		}

	return user_key_flag;
}


uint8_t key1_scan(void)
{
	uint8_t 		key1_flag;

	key1_flag			= 0;

	//key1按键控制motor
	if (GPIO_ReadInputDataBit(GPIOC, KEY1_PIN) == RESET)
		{

		drv_systick_ms(20);

		if (GPIO_ReadInputDataBit(GPIOC, KEY1_PIN) == RESET)
			{
			while (GPIO_ReadInputDataBit(GPIOC, KEY1_PIN) == RESET)
				;

			key1_flag			= ~key1_flag;
			return key1_flag;
			}
		}

	return key1_flag;
}


uint8_t key2_scan(void)
{
	uint8_t 		key2_flag;

	key2_flag			= 0;

	//key2按键控制fan
	if (GPIO_ReadInputDataBit(GPIOC, KEY2_PIN) == RESET)
		{

		drv_systick_ms(20);

		if (GPIO_ReadInputDataBit(GPIOC, KEY2_PIN) == RESET)
			{
			while (GPIO_ReadInputDataBit(GPIOC, KEY2_PIN) == RESET)
				;

			key2_flag			= ~key2_flag;
			return key2_flag;
			}
		}

	return key2_flag;
}


uint8_t key3_scan(void)
{
	uint8_t 		key3_flag;

	key3_flag			= 0;

	//key3按键控制流水灯
	if (GPIO_ReadInputDataBit(GPIOC, KEY3_PIN) == RESET)
		{

		drv_systick_ms(20);

		if (GPIO_ReadInputDataBit(GPIOC, KEY3_PIN) == RESET)
			{
			while (GPIO_ReadInputDataBit(GPIOC, KEY3_PIN) == RESET)
				;

			key3_flag			= ~key3_flag;
			return key3_flag;
			}
		}

	return key3_flag;
}




