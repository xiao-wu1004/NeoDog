
#include "drv_all.h"


int main(void)
{
	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
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
	printf("hello va\r\n");

	while (1)
		{
//		led_ON();
//		drv_systick_ms(1000);
//		led_OFF();
//		drv_systick_ms(1000);

		//liushui_led();
		//beep_Blink();
		}
}


