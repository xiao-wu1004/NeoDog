
#include "drv_all.h"

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
void SVC_Handler(void)
{
}


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
void PendSV_Handler(void)
{
}


/**
  * @brief	This function handles SysTick Handler.
  * @param	None
  * @retval None
  */
void SysTick_Handler(void)
{
}


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

        switch(fan_speed)
        {
            case 0:
                TIM_SetCompare1(TIM3, 0);
                break;

            case 1:
                TIM_SetCompare1(TIM3, 1500);
                break;

            case 2:
                TIM_SetCompare1(TIM3, 3000);
                break;

            case 3:
                TIM_SetCompare1(TIM3, 5000);
                break;
        }
    }

    if (EXTI_GetITStatus(EXTI_Line5))
    {
        EXTI_ClearITPendingBit(EXTI_Line5);




        //GPIO_ToggleBits(GPIOC, GPIO_Pin_7); 		//改变马达电平
//        beep_OFF();
//        fan_OFF();

    }

}


char rx_buffer[20];
uint8_t rx_index = 0;
void USART2_IRQHandler(void)
{
    if (USART_GetITStatus(USART2, USART_IT_RXNE))
    {
        USART_ClearITPendingBit(USART2, USART_IT_RXNE);

        char receive_char	= USART_ReceiveData(USART2);

        if (receive_char == '\n' || receive_char == '\r' || rx_index >= 20 - 1)
        {
            rx_buffer[rx_index] = '\0';

            // 处理接收到的命令
            if (strcmp(rx_buffer, "LED_ON") == 0)
            {
                all_led_ON();
                printf("LED turned ON\r\n");
            }
            else if (strcmp(rx_buffer, "LED_OFF") == 0)
            {
                all_led_OFF();
                printf("LED turned OFF\r\n");
            }
            else if (strcmp(rx_buffer, "FAN_ON") == 0)
            {
                fan_ON();
                printf("FAN turned ON\r\n");
            }
            else if (strcmp(rx_buffer, "FAN_OFF") == 0)
            {
                fan_OFF();
                printf("FAN turned OFF\r\n");
            }

            else
            {
                printf("Unknown command: %s\r\n", rx_buffer);
            }

            // 重置缓冲区索引
            rx_index			= 0;
        }
        else
        {
            rx_buffer[rx_index++] = receive_char;
        }

        //USART_SendData(USART2, USART_ReceiveData(USART2));
        USART_ClearITPendingBit(USART2, USART_IT_RXNE);
    }

    if (USART_GetITStatus(USART2, USART_IT_IDLE)) //空闲中断
    {
        USART_ClearITPendingBit(USART2, USART_IT_IDLE);
        USART_ReceiveData(USART2);
        USART_SendData(USART2, 'a');
    }
}

volatile float sht20_temp;
//volatile uint8_t temp_flag;
void TIM7_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM7, TIM_IT_Update))
    {
        TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
        //temp_flag = 1;
		
		sht20_temp=sht20_getTdata();
        //GPIO_ToggleBits(GPIOC, GPIO_Pin_4); 		//改变led1的电平

        //GPIO_ToggleBits(GPIOF, GPIO_Pin_8); //改变user_led的电平
    }
}


/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
