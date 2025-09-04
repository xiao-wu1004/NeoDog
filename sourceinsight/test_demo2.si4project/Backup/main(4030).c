
#include "drv_all.h"

#include "oled.h"
#include "bmp.h"
int times = 1000;
//dma的源数据
uint32_t dma_src[5] = {0x11111111, 0x11111112, 0x11111113, 0x11111114, 0x11111115};
//dma的目标
uint32_t dma_dir[5] = {0};

float sht20_temp;
volatile uint8_t temp_flag;
int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    led_init();

    beep_init();
    drv_systick_init(168);
    fan_init();
    motor_init();
    key_init();
    key_init1();


    exti9_init();
    usart6_init();
    tim7_init();
    tim13_init();
    tim3_init();
    TIM_SetCompare1(TIM3, 0);
    printf("hello va\r\n");

    sht20_init();

    uint16_t led_pwm = 0;
    uint8_t dir = 0;

    u8 t = ' ';
    OLED_Init();				//初始化OLED

    drv_74hc595_init();
    //float temp=sht20_getTdata();


    dma_init(dma_src, dma_dir, 5);
    drv_systick_ms(10);
    dmadata_compare();

    while (1)
    {
//        OLED_ShowPicture(0, 0, 128, 64, BMP1, 1);
//        OLED_Refresh();
//        drv_systick_ms(100);
//        OLED_Clear();
//        OLED_ShowChinese(0, 0, 0, 16, 1); //中
//        OLED_ShowChinese(18, 0, 1, 16, 1); //景
//        OLED_ShowChinese(36, 0, 2, 16, 1); //园
//        OLED_ShowChinese(54, 0, 3, 16, 1); //电
//        OLED_ShowChinese(72, 0, 4, 16, 1); //子
//        OLED_ShowChinese(90, 0, 5, 16, 1); //技
//        OLED_ShowChinese(108, 0, 6, 16, 1); //术
//        OLED_ShowString(8, 16, "ZHONGJINGYUAN", 16, 1);
//        OLED_ShowString(20, 32, "2014/05/01", 16, 1);
//        OLED_ShowString(0, 48, "ASCII:", 16, 1);
//        OLED_ShowString(63, 48, "CODE:", 16, 1);
//        OLED_ShowChar(48, 48, t, 16, 1); //显示ASCII字符
//        t++;

//        if(t > '~')t = ' ';

//        OLED_ShowNum(103, 48, t, 3, 16, 1);
//        OLED_Refresh();
//        drv_systick_ms(500);
//        OLED_Clear();
//        OLED_ShowChinese(0, 0, 0, 16, 1); //16*16 中
//        OLED_ShowChinese(16, 0, 0, 24, 1); //24*24 中
//        OLED_ShowChinese(24, 20, 0, 32, 1); //32*32 中
//        OLED_ShowChinese(64, 0, 0, 64, 1); //64*64 中
//        OLED_Refresh();
//        drv_systick_ms(500);
//        OLED_Clear();
//        OLED_ShowString(0, 0, "ABC", 8, 1); //6*8 “ABC”
//        OLED_ShowString(0, 8, "ABC", 12, 1); //6*12 “ABC”
//        OLED_ShowString(0, 20, "ABC", 16, 1); //8*16 “ABC”
//        OLED_ShowString(0, 36, "ABC", 24, 1); //12*24 “ABC”
//        OLED_Refresh();
//        drv_systick_ms(500);
//        OLED_ScrollDisplay(11, 4, 1);


//        key_state();

		if(temp_flag)
		{
			sht20_temp=sht20_getTdata();
			temp_flag=0;
		}
        display_temp(sht20_temp);
        //drv_systick_us(1);
//        sht20_getRHdata();
//        drv_systick_ms(3000);


//        if(dir == 0)
//        {
//            led_pwm++;
//        }
//        else
//        {
//            led_pwm--;
//        }

//        if(led_pwm > 500)
//        {
//            dir = 1;
//        }

//        if(led_pwm == 0)
//        {
//            dir = 0;
//        }

//        TIM_SetCompare1(TIM13, led_pwm);
//        drv_systick_ms(10);
    }
}


