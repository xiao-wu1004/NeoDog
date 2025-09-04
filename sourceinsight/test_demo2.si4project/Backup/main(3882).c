
#include "drv_all.h"


int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    led_init();

    //led3_1_init();
    beep_init();
    drv_systick_init(168);
    fan_init();
    motor_init();
    key_init();
    key_init1();
    exti9_init();

    //exti_key3_1_init();
    usart6_init();
    tim7_init();
    tim13_init();
    printf("hello va\r\n");

    uint16_t led_pwm = 0;
    uint8_t dir = 0;

    while (1)
    {
        //		led_ON();
        //		drv_systick_ms(1000);
        //		led_OFF();
        //		drv_systick_ms(1000);
        //liushui_led();
        //beep_Blink();
        if(dir == 0)
        {
            led_pwm++;
        }
        else
        {
            led_pwm--;
        }

        if(led_pwm > 500)
        {
            dir = 1;
        }

        if(led_pwm == 0)
        {
            dir = 0;
        }

        TIM_SetCompare1(TIM13, led_pwm);
        drv_systick_ms(10);
    }
}


