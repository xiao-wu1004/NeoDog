
#include "drv_all.h"
#include "oled.h"
#include "bmp.h"
#include "FreeRTOS.h"
#include "task.h"

int times = 1000;
//dma��Դ����
uint32_t dma_src[5] = {0x11111111, 0x11111112, 0x11111113, 0x11111114, 0x11111115};
//dma��Ŀ��
uint32_t dma_dir[5] = {0};
uint8_t t = 0;

//ȫ�ֱ�������
extern  float sht20_temp;
extern  float sht20_rh;
extern  uint8_t temp_flag;
extern  uint8_t rh_flag;
extern  uint8_t wk_flag;
extern  uint8_t liuhan_flag;
extern  uint8_t smile_flag ;
extern  uint8_t bigsmile_flag;
extern  uint8_t dance_flag;
extern  uint8_t greet_flag;
extern  uint8_t left_flag;
extern  uint8_t right_flag;

extern uint8_t dance_em_flag ;
extern uint8_t hello_em_flag ;


extern uint8_t right_em_flag ;
extern uint8_t left_em_flag ;
extern uint8_t stop_em_flag ;
extern uint8_t led_ON_flag ;
extern uint8_t led_OFF_flag ;


extern unsigned char stop[];
extern unsigned char led_ONN[];
extern unsigned char led_OF[];
extern unsigned char smile128[];
extern unsigned char bigsmile128[];

//// ����״̬����
//typedef enum
//{
//    ACTION_IDLE,          // ����״̬
//    ACTION_WALKING,       // ������
//    ACTION_DANCING,       // ������
//    ACTION_GREETING,      // ���к���
//    ACTION_TURNING_LEFT,  // ��ת��
//    ACTION_TURNING_RIGHT,  // ��ת��
//	ACTION_TURNING_TEMP
//} ActionState;

//// ������ʾ��־
//typedef enum
//{
//    EXPRESSION_NONE,
//    EXPRESSION_WALKING,
//    EXPRESSION_DANCE,
//    EXPRESSION_GREET,
//    EXPRESSION_SMILE,
//    EXPRESSION_LEFT,
//    EXPRESSION_RIGHT,
//	EXPRESSION_TEMP
//} ExpressionType;

// �������Ʊ���
ActionState current_action = ACTION_IDLE;

// �������
ExpressionType current_expression = EXPRESSION_NONE;


// ������־λ�������ԭ�б�־λ���ݣ�
extern uint8_t wk_flag, dance_flag, greet_flag;


/**
 * @brief ����OLED��ʾ����������
 */
void update_oled_display(void)
{
    switch (current_expression)
    {
        case EXPRESSION_WALKING:
            OLED_Clear();
            OLED_ShowPicture(0, 0, 128, 64, liuhan_BMP128, 1);
            OLED_Refresh();
            tim4_delay_ms(1000);
            current_expression = EXPRESSION_NONE;
            break;

        case EXPRESSION_DANCE:
            OLED_Clear();
            OLED_ShowPicture(0, 0, 128, 64, tiaowu, 1);
            OLED_Refresh();
            tim4_delay_ms(1000);
            current_expression = EXPRESSION_NONE;
            break;

        case EXPRESSION_GREET:
            OLED_Clear();
            OLED_ShowPicture(0, 0, 128, 64, hello, 1);
            OLED_Refresh();
            tim4_delay_ms(1000);
            current_expression = EXPRESSION_NONE;
            break;

        case EXPRESSION_LEFT:
            OLED_Clear();
            OLED_ShowPicture(32, 0, 64, 41, left, 1);
            OLED_Refresh();
            current_expression = EXPRESSION_NONE;
            break;

        case EXPRESSION_RIGHT:
            OLED_Clear();
            OLED_ShowPicture(32, 0, 64, 64, right, 1);
            OLED_Refresh();
            current_expression = EXPRESSION_NONE;
            break;

        case EXPRESSION_TEMP:
            sht20_temp = sht20_getTdata();
            sht20_rh = sht20_getRHdata();
            // ��OLED����ʾ��ʪ��
            char temp_str[16];
            char hum_str[16];
            // ��ʽ���¶��ַ���
            sprintf(temp_str, "%.1f C", sht20_temp);
            // ��ʽ��ʪ���ַ���
            sprintf(hum_str, "%.1f %%", sht20_rh);
            OLED_Clear();
            OLED_ShowString(16, 10, "Temp:", 16, 1);
            OLED_ShowString(16, 34, "Hum :", 16, 1);
            // ��ʾ�¶�
            OLED_ShowString(64, 10, (uint8_t *)temp_str, 16, 1);
            // ��ʾʪ��
            OLED_ShowString(64, 34, (uint8_t *)hum_str, 16, 1);
            OLED_Refresh();
            // ��ʱ2������
            tim4_delay_ms(3000);
            //tim4_delay_ms(3000);
            OLED_Clear();
            current_expression = EXPRESSION_NONE;
            break;

        case EXPRESSION_LED_ON:
            OLED_Clear();
            OLED_ShowPicture(32, 0, 64, 64, led_ONN, 1);
            OLED_Refresh();
            tim4_delay_ms(1500);
            current_expression = EXPRESSION_NONE;
            break;

        case EXPRESSION_LED_OFF:
            OLED_Clear();
            OLED_ShowPicture(32, 0, 64, 64, led_OF, 1);
            OLED_Refresh();
            tim4_delay_ms(1500);
            current_expression = EXPRESSION_NONE;
            break;

        case EXPRESSION_NONE:
            OLED_Clear();
            
            break;

        default:
            OLED_Clear();
            // ������ʾĬ�ϻ��������
            break;
    }
}
int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ��Ϊ4  ��ռ���ȼ���ߣ������2
    //usart_all_init();//����2,3,6��ʼ��
    usart3_init();
    usart_2_6_Init();
    led_init();//led��
    //beep_init();//������
    drv_systick_init(168);
    fan_init();//����
    //motor_init();//���
    //key_init();//user����
    //key_init1();//key 1 2 3
    //exti9_init();//�����ж�
    //tim7_init();
    tim4_delay_init();
    //tim13_init();
    sht20_init();
    OLED_Init();
    //    OLED_ScrollDisplay(11,4,1);
    //    OLED_Clear();
    //    printf("hello va\r\n");
    //    OLED_Clear();
    //    OLED_ShowPicture(0, 0, 128, 64, liuhan_BMP128, 1);
    //    OLED_Refresh();
    //    tim4_delay_ms(3000);
    //	OLED_ShowPicture(0, 0, 128, 64, smile128, 1);
    //    OLED_Refresh();
    //    tim4_delay_ms(3000);
    //    OLED_Clear();
    sg90_init();
    //    drv_74hc595_init();
    //    dma_init(dma_src, dma_dir, 5);
    //    tim4_delay_ms(10);
    //    dmadata_compare();
    //adc1_init();
    //WiFi_Client_Init();
    printf("hello\r\n");

    while (1)
    {
        update_oled_display();

        // ���߶������⴦����Ҫ����ִ�У�
        if (current_action == ACTION_WALKING)
        {
            if (wk_flag == 0)  // �յ�ֹͣ����
            {
                current_action = ACTION_IDLE;
                robot_standup();
            }
            else
            {
                robot_walk_continuous(); // �������ò���鷵��ֵ
            }

            continue; // ���������������
        }

        switch (current_action)
        {
            case ACTION_DANCING:
                if (!robot_dance())
                {
                    break;
                }

                current_action = ACTION_IDLE;
                dance_flag = 0;
                dance_em_flag = 0;
                current_expression = EXPRESSION_NONE;
                break;

            case ACTION_GREETING:
                if (!robot_greet(3, 400))
                {
                    break;
                }

                current_action = ACTION_IDLE;
                greet_flag = 0;
                //hello_em_flag=0;
                current_expression = EXPRESSION_NONE;
                break;

            case ACTION_TURNING_LEFT:
                if (!robot_turn_left(3, 200))
                {
                    break;
                }

                current_action = ACTION_IDLE;
                left_em_flag = 0;
                current_expression = EXPRESSION_NONE;
                break;

            case ACTION_TURNING_RIGHT:
                if (!robot_turn_right(3, 200))
                {
                    break;
                }

                current_action = ACTION_IDLE;
                right_em_flag = 0;
                current_expression = EXPRESSION_NONE;
                break;

            case ACTION_IDLE:

                // ����¶�������
                if (wk_flag)
                {
                    current_action = ACTION_WALKING;
                    current_expression = EXPRESSION_WALKING;
                    break;
                }
                else if (dance_flag)
                {
                    current_action = ACTION_DANCING;
                    current_expression = EXPRESSION_DANCE;
					dance_flag=0;
                    break;
                }
                else if (left_em_flag)
                {
                    current_action = ACTION_TURNING_LEFT;
                    current_expression = EXPRESSION_LEFT;
					left_em_flag=0;
                    break;
                }
                else if (right_em_flag)
                {
                    current_action = ACTION_TURNING_RIGHT;
                    current_expression = EXPRESSION_RIGHT;
					right_em_flag=0;
                    break;
                }
                else if (temp_flag)
                {
                    //current_action = ACTION_TURNING_TEMP;
                    current_expression = EXPRESSION_TEMP;
                    temp_flag = 0;
                    break;
                }
                else if (greet_flag)
                {
                    current_action = ACTION_GREETING;
                    current_expression = EXPRESSION_GREET;
                    greet_flag = 0;
                    break;
                }

                else if (led_ON_flag)
                {
                    current_expression = EXPRESSION_LED_ON;
                    led_ON_flag = 0;
                    break;
                }
                else if (led_OFF_flag)
                {
                    current_expression = EXPRESSION_LED_OFF;
                    led_OFF_flag = 0;
                    break;
                }
                
                break;
        }

        
    }
}


