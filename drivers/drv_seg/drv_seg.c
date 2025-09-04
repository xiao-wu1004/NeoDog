
#include "drv_all.h"

static uint8_t seg_code[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F}; //0-9
static uint8_t seg_wei[] = {0x08, 0x04, 0x02, 0x01};

void drv_74hc595_init()
{
    spi2_init();
}


void seg_display(uint8_t wei, uint8_t duan)
{
    spi2_senddata(seg_wei[wei]);
    spi2_senddata(seg_code[duan]);
    GPIO_ResetBits(GPIOB, GPIO_Pin_12);
    drv_systick_ms(1);
    GPIO_SetBits(GPIOB, GPIO_Pin_12);
}
void display_temp(float temp)
{
    uint8_t digits[4];  // 存储 4 位数字（DIG1-DIG4）
    uint8_t is_negative = 0;

    // 处理负数
    if (temp < 0)
    {
        is_negative = 1;
        temp = -temp;
    }

    // 提取整数部分（前 2 位）
    uint8_t integer_part = (uint8_t)temp;
    digits[3] = integer_part / 10;  // 十位
    digits[2] = integer_part % 10;  // 个位

    // 提取小数部分（后 2 位）
    float decimal_part = temp - integer_part;
    digits[1] = (uint8_t)(decimal_part * 10);      // 十分位
    digits[0] = (uint8_t)(decimal_part * 100) % 10; // 百分位

    // 显示到数码管
    for (uint8_t i = 0; i < 4; i++)
    {
        // seg_display(i, seg_code[digits[i]] | 0x80);  // 添加小数点
        
            //seg_display(i, seg_code[digits[i]]);
            seg_display(i, digits[i]);
        


    }

}

