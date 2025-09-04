#include "drv_all.h"
#include <string.h>
#include <stdio.h>

// ���ڷ����ַ�����������ԭ��ʵ�֣�
void USART_SendString(USART_TypeDef* USARTx, char *str)
{
    while (*str)
    {
        USART_SendData(USARTx, *str++);

        while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);
    }
}

// ��ǿ��ATָ��ͣ�����Ӧ��飩
uint8_t WiFi_SendCommand(const char *cmd, const char *expect, uint32_t timeout_ms)
{
    char response[128] = {0};
    uint16_t index = 0;
    uint32_t start_time = 0; // ������������ʱ��ʽ���滻

    // ����ָ��
    USART_SendString(USART3, (char*)cmd);
    USART_SendString(USART3, "\r\n");

    // ��ʱ���ƣ�ʹ��������ʱ������
    while (1)
    {
        if (USART_GetFlagStatus(USART3, USART_IT_RXNE))
        {
            char ch = USART_ReceiveData(USART3);

            if (index < sizeof(response) -1)
            {
                response[index++] = ch;
                response[index] = '\0';

                // ���Ԥ����Ӧ
                if (expect != NULL && strstr(response, expect)) return 1;

                // ������
                if (strstr(response, "ERROR")) return 0;
            }
        }

        // ��ʱ�жϣ�������֤��ʱ�������ȣ�
        drv_systick_ms(10);

        if (++start_time >= timeout_ms) break;
    }

    return 0; // ��ʱ
}

// WiFi��ʼ�����ϸ���ѭ��ԭ�����̣�
uint8_t WiFi_Client_Init(void)
{
    printf("\n=== WiFi��ʼ����ʼ ===\n");

    // 1. �ָ��������ã���ѡ��
    printf("�ָ���������...");
    WiFi_SendCommand("AT+RESTORE", "OK", 2000);
    drv_systick_ms(2000); // ȷ���������
    printf("OK\n");

    // 2. ����ATָ��
    printf("����ATָ��...");
    if (!WiFi_SendCommand("AT", "OK", 2000))
    {
        printf("ʧ��\n");
        return 0;
    }
    printf("OK\n");

    // 3. ��������ģʽ���������֣�
    printf("��������ģʽ...");
    if (!WiFi_SendCommand("ATE1", "OK", 2000))
    {
        printf("ʧ��\n");
        // ע�⣺��Щģ����ܲ�֧�ֻ���ģʽ�����ﲻ��Ϊ��������
    }
    else
    {
        printf("OK\n");
    }

    // 4. ����Stationģʽ
    printf("����ģʽ...");
    if (!WiFi_SendCommand("AT+CWMODE=1", "OK", 3000))
    {
        printf("ʧ��\n");
        return 0;
    }
    printf("OK\n");

    // 5. ����WiFi���ؼ����裬�ӳ���ʱ��
    char connect_cmd[128];
    sprintf(connect_cmd, "AT+CWJAP=\"%s\",\"%s\"", WIFI_SSID, WIFI_PASSWORD);
    printf("����WiFi...");
    if (!WiFi_SendCommand(connect_cmd, "OK", 10000))
    {
        printf("ʧ��\n");
        return 0;
    }
    printf("OK\n");

    // 6. ���õ�����ģʽ
    printf("���õ�����...");
    if (!WiFi_SendCommand("AT+CIPMUX=0", "OK", 3000))
    {
        printf("ʧ��\n");
        return 0;
    }
    printf("OK\n");

    // 7. ���ӷ�����
    char server_cmd[64];
    sprintf(server_cmd, "AT+CIPSTART=\"TCP\",\"%s\",%s", SERVER_IP, SERVER_PORT);
    printf("���ӷ�����...");
    if (!WiFi_SendCommand(server_cmd, "OK", 5000))
    {
        printf("ʧ��\n");
        return 0;
    }
    printf("OK\n");

    printf("=== WiFi��ʼ���ɹ� ===\n");
    return 1;
}

// ���ݷ��ͣ���ȫ������ԭ���߼���
uint8_t WiFi_SendData(const char *data)
{
    char cmd[64];
    sprintf(cmd, "AT+CIPSEND=%d", strlen(data));

    // ���ͳ���ָ��
    if (!WiFi_SendCommand(cmd, ">", 3000)) return 0;

    // ����ʵ������
    USART_SendString(USART3, (char*)data);
    return WiFi_SendCommand("", "SEND OK", 3000);
}

// �����߼������������ƣ�
void WiFi_Reconnect(void)
{
    uint8_t retry = 3;

    while (retry--)
    {
        WiFi_SendCommand("AT+CIPCLOSE", NULL, 1000); // ǿ�ƹر�����

        if (WiFi_Client_Init()) break;

        drv_systick_ms(5000); // ��ʱ5�������
    }
}
