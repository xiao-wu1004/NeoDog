#ifndef __DRV_WIFI_H__
#define __DRV_WIFI_H__
#include "stm32f4xx.h"
//10.0.2.15
//���� 192.168.91.71
#define SERVER_IP       "192.168.91.71"  // �ֻ��ȵ�Ĭ��IP
#define SERVER_PORT     "8080"          // �ֻ��������˿�
//#define WIFI_SSID      "test"
//#define WIFI_PASSWORD  "12345678"

#define WIFI_SSID      "hqyjcs"
#define WIFI_PASSWORD  "hqyj2022"
void USART_SendString(USART_TypeDef* USARTx, char *str);
uint8_t WiFi_SendCommand(const char *cmd, const char *expect, uint32_t timeout_ms);
uint8_t WiFi_Client_Init(void);
uint8_t WiFi_SendData(const char *data);
void WiFi_Reconnect(void);
#endif
