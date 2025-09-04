
#include "drv_all.h"
#include "oled.h"

extern unsigned char smile2[];
extern unsigned char bigsmile128[];
extern unsigned char liuhan_BMP128[];



/**
  ******************************************************************************
  * @file	 GPIO/GPIO_IOToggle/stm32f4xx_it.c
  * @author  MCD Application Team
  * @version V1.8.0
  * @date	 04-November-2016
  * @brief	 Main Interrupt Service Routines.
  * 		 This file provides template for all exceptions handler and
  * 		 peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2016 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  * 	   http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"

/** @addtogroup STM32F4xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup GPIO_IOToggle
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*			  Cortex-M4 Processor Exceptions Handlers						  */
/******************************************************************************/

/**
  * @brief	 This function handles NMI exception.
  * @param	None
  * @retval None
  */
void NMI_Handler(void)
{
}


/**
  * @brief	This function handles Hard Fault exception.
  * @param	None
  * @retval None
  */
void HardFault_Handler(void)
{
    /* Go to infinite loop when Hard Fault exception occurs */
    while (1)
    {
    }
}


/**
  * @brief	This function handles Memory Manage exception.
  * @param	None
  * @retval None
  */
void MemManage_Handler(void)
{
    /* Go to infinite loop when Memory Manage exception occurs */
    while (1)
    {
    }
}


/**
  * @brief	This function handles Bus Fault exception.
  * @param	None
  * @retval None
  */
void BusFault_Handler(void)
{
    /* Go to infinite loop when Bus Fault exception occurs */
    while (1)
    {
    }
}


/**
  * @brief	This function handles Usage Fault exception.
  * @param	None
  * @retval None
  */
void UsageFault_Handler(void)
{
    /* Go to infinite loop when Usage Fault exception occurs */
    while (1)
    {
    }
}


/**
  * @brief	This function handles SVCall exception.
  * @param	None
  * @retval None
  */
//void SVC_Handler(void)
//{
//}


/**
  * @brief	This function handles Debug Monitor exception.
  * @param	None
  * @retval None
  */
void DebugMon_Handler(void)
{
}


/**
  * @brief	This function handles PendSVC exception.
  * @param	None
  * @retval None
  */
//void PendSV_Handler(void)
//{
//}


/**
  * @brief	This function handles SysTick Handler.
  * @param	None
  * @retval None
  */
//void SysTick_Handler(void)
//{
//}


/******************************************************************************/
/*				   STM32F4xx Peripherals Interrupt Handlers 				  */
/*	Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*	available peripheral interrupt handler's name please refer to the startup */
/*	file (startup_stm32f40xx.s/startup_stm32f427x.s/startup_stm32f429x.s).	  */
/******************************************************************************/

/**
  * @brief	This function handles PPP interrupt request.
  * @param	None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/
volatile uint8_t fan_speed = 0; //0：停止 1：低速 2：中速 3：高速


void EXTI9_5_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line9))
    {
        EXTI_ClearITPendingBit(EXTI_Line9);
        GPIO_ToggleBits(GPIOA, GPIO_Pin_15);		//改变蜂鸣器电平
        //        fan_OFF();
        //        motor_OFF();
    }

    if (EXTI_GetITStatus(EXTI_Line8))
    {
        EXTI_ClearITPendingBit(EXTI_Line8);
        fan_speed = (fan_speed + 1) % 4;
        //        switch (fan_speed)
        //        {
        //            case 0:
        //                TIM_SetCompare1(TIM4, 0);
        //                break;
        //            case 1:
        //                TIM_SetCompare1(TIM4, 1500);
        //                break;
        //            case 2:
        //                TIM_SetCompare1(TIM4, 3000);
        //                break;
        //            case 3:
        //                TIM_SetCompare1(TIM4, 5000);
        //                break;
        //        }
    }

    if (EXTI_GetITStatus(EXTI_Line5))
    {
        EXTI_ClearITPendingBit(EXTI_Line5);
        //GPIO_ToggleBits(GPIOC, GPIO_Pin_7); 		//改变马达电平
        //        beep_OFF();
        //        fan_OFF();
    }
}


char rx_buffer[40];
uint8_t rx_index = 0;

// 定义所有全局控制标志
//温度和湿度变量
float sht20_temp;
float sht20_rh;
uint8_t temp_flag = 0;
uint8_t rh_flag = 0;

extern  uint8_t wk_flag ;  // 行走标志

uint8_t liuhan_flag = 0; //流汗表情标志
uint8_t smile_flag = 0; //微笑表情标志
uint8_t bigsmile_flag = 0;
uint8_t dance_flag = 0;

uint8_t left_flag = 0;
uint8_t right_flag = 0;
uint8_t greet_flag = 0;

uint8_t dance_em_flag = 0;
uint8_t hello_em_flag = 0;


uint8_t right_em_flag = 0;
uint8_t left_em_flag = 0;
uint8_t stop_em_flag = 0;

uint8_t led_ON_flag = 0;
uint8_t led_OFF_flag = 0;

// 动作控制变量
extern ActionState current_action ;

// 表情控制
extern ExpressionType current_expression ;

//命令处理函数
static void process_command(char *cmd)
{
    if(current_action != ACTION_IDLE)
    {
        current_action = ACTION_IDLE;
        current_expression = EXPRESSION_NONE;
        // 重置所有舵机到安全位置
        robot_standup();
    }

    if (strcmp(cmd, "LED_ON") == 0)
    {
        led_ON_flag = 1;
        led_ON();
        //printf("LED turned ON\r\n");
    }
    else if (strcmp(cmd, "LED_OFF") == 0)
    {
        led_OFF_flag = 1;
        led_OFF();
        //printf("LED turned OFF\r\n");
    }
    else if (strcmp(cmd, "FAN_ON") == 0)
    {
        fan_ON();
        //printf("FAN turned ON\r\n");
    }
    else if (strcmp(cmd, "FAN_OFF") == 0)
    {
        fan_OFF();
        //printf("FAN turned OFF\r\n");
    }
    else if (strcmp(cmd, "standup") == 0)
    {
        wk_flag = 0;
        bigsmile_flag = 1;
        robot_standup();

    }
    else if (strcmp(cmd, "sitdown") == 0)
    {
        wk_flag = 0;
        smile_flag = 1;
        robot_sitdown();

    }
    else if (strcmp(cmd, "walk") == 0)
    {
        wk_flag = 1;
        liuhan_flag = 1;

    }
    else if (strcmp(cmd, "stop") == 0)
    {

        stop_em_flag = 1;
        wk_flag = 0;
        //robot_standup();//有问题
        //printf("停止行走请求已接收\r\n");
    }
    else if (strcmp(cmd, "weather") == 0)
    {
        temp_flag = 1;

    }
    else if (strcmp(cmd, "dance") == 0)
    {
        dance_em_flag = 1;
        dance_flag = 1;

    }
    else if (strcmp(cmd, "greet") == 0)
    {
        hello_em_flag = 1;
        greet_flag = 1;

    }
    else if (strcmp(cmd, "left") == 0)
    {
        left_em_flag = 1;
        left_flag = 1;


    }
    else if (strcmp(cmd, "right") == 0)
    {
        right_em_flag = 1;
        right_flag = 1;

    }

    //    else
    //    {
    //        printf("Unknown command: %s\r\n", cmd);
    //    }
}

void USART2_IRQHandler(void)
{
    if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {
        USART_ClearITPendingBit(USART2, USART_IT_RXNE);
        char ch = USART_ReceiveData(USART2);
        // 转发到USART6
        USART_SendData(USART6, ch);

        while (USART_GetFlagStatus(USART6, USART_FLAG_TC) == RESET);

        USART_ClearFlag(USART6, USART_FLAG_TC);

        if (rx_index < sizeof(rx_buffer) - 1)
        {
            if (ch == '\n' || ch == '\r')
            {
                rx_buffer[rx_index] = '\0';
                process_command(rx_buffer);
                rx_index = 0; // 重置索引
            }
            else
            {
                rx_buffer[rx_index++] = ch;
            }
        }
        else
        {
            rx_index = 0; // 防止缓冲区溢出
        }
    }

    if (USART_GetITStatus(USART2, USART_IT_IDLE)) //空闲中断
    {
        USART_ClearITPendingBit(USART2, USART_IT_IDLE);
        USART_ReceiveData(USART2);

        if (rx_index > 0)
        {
            rx_buffer[rx_index] = '\0'; //结束字符串
            // 处理接收到的命令
            process_command(rx_buffer);
            rx_index = 0;
        }
    }
}

char rx_buffer6[40];
uint8_t rx_index6 = 0;
void USART6_IRQHandler(void)
{
    if (USART_GetITStatus(USART6, USART_IT_RXNE))
    {
        USART_ClearITPendingBit(USART6, USART_IT_RXNE);
        char ch	= USART_ReceiveData(USART6);

        if (rx_index6 < sizeof(rx_buffer6) - 1)
        {
            if (ch == '\n' || ch == '\r')
            {
                rx_buffer6[rx_index6] = '\0';
                // 处理接收到的命令
                process_command(rx_buffer6);
                // 重置缓冲区索引
                rx_index6			= 0;
            }
            else
            {
                rx_buffer6[rx_index6++] = ch;
            }
        }

        //USART_SendData(USART2, USART_ReceiveData(USART2));
    }

    if (USART_GetITStatus(USART6, USART_IT_IDLE)) //空闲中断
    {
        USART_ClearITPendingBit(USART6, USART_IT_IDLE);
        USART_ReceiveData(USART6);

        if (rx_index6 > 0)
        {
            rx_buffer6[rx_index6] = '\0'; //结束字符串
            // 处理接收到的命令
            process_command(rx_buffer6);
            rx_index6 = 0;
        }
    }
}

char rx_buffer3[40];
uint8_t rx_index3 = 0;
uint8_t colon_found = 0;   // 标记是否找到冒号

void USART3_IRQHandler()
{
    if (USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
    {
        USART_ClearITPendingBit(USART3, USART_IT_RXNE);
        char ch = USART_ReceiveData(USART3);
        // 转发到USART6
        USART_SendData(USART6, ch);

        while (USART_GetFlagStatus(USART6, USART_FLAG_TC) == RESET);

        USART_ClearFlag(USART6, USART_FLAG_TC);

        if (rx_index3 < sizeof(rx_buffer3) - 1)
        {
            if (ch == '\n' || ch == '\r')
            {
                rx_buffer3[rx_index3] = '\0';
                process_command(rx_buffer3);
                rx_index3 = 0; // 重置索引
            }
            else
            {
                rx_buffer3[rx_index3++] = ch;
            }
        }
        else
        {
            rx_index3 = 0; // 防止缓冲区溢出
        }
    }

    if (USART_GetITStatus(USART3, USART_IT_IDLE)) //空闲中断
    {
        USART_ClearITPendingBit(USART3, USART_IT_IDLE);
        USART_ReceiveData(USART3);

        if (rx_index3 > 0)
        {
            rx_buffer3[rx_index3] = '\0'; //结束字符串
            // 处理接收到的命令
            process_command(rx_buffer3);
            rx_index3 = 0;
        }
    }
}

extern uint8_t delay_done;

//void TIM7_IRQHandler(void)
//{
//    if (TIM_GetITStatus(TIM7, TIM_IT_Update))
//    {
//        TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
//		TIM_Cmd(TIM7,DISABLE);
//		delay_done=1;
//        //GPIO_ToggleBits(GPIOC, GPIO_Pin_4); 		//改变led1的电平
//        //GPIO_ToggleBits(GPIOF, GPIO_Pin_8); //改变user_led的电平
//    }
//}

//void TIM4_IRQHandler(void)
//{
//    if (TIM_GetITStatus(TIM4, TIM_IT_Update))
//    {
//        TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
//		TIM_Cmd(TIM4,DISABLE);
//		delay_done=1;
//        //GPIO_ToggleBits(GPIOC, GPIO_Pin_4); 		//改变led1的电平
//        //GPIO_ToggleBits(GPIOF, GPIO_Pin_8); //改变user_led的电平
//    }
//}



/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
