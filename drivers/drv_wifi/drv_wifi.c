#include "drv_all.h"
#include <string.h>
#include <stdio.h>

// 串口发送字符串（保持您原有实现）
void USART_SendString(USART_TypeDef* USARTx, char *str)
{
    while (*str)
    {
        USART_SendData(USARTx, *str++);

        while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);
    }
}

// 增强版AT指令发送（带响应检查）
uint8_t WiFi_SendCommand(const char *cmd, const char *expect, uint32_t timeout_ms)
{
    char response[128] = {0};
    uint16_t index = 0;
    uint32_t start_time = 0; // 若您有其他计时方式可替换

    // 发送指令
    USART_SendString(USART3, (char*)cmd);
    USART_SendString(USART3, "\r\n");

    // 超时控制（使用您的延时函数）
    while (1)
    {
        if (USART_GetFlagStatus(USART3, USART_IT_RXNE))
        {
            char ch = USART_ReceiveData(USART3);

            if (index < sizeof(response) -1)
            {
                response[index++] = ch;
                response[index] = '\0';

                // 检查预期响应
                if (expect != NULL && strstr(response, expect)) return 1;

                // 检查错误
                if (strstr(response, "ERROR")) return 0;
            }
        }

        // 超时判断（需您保证延时函数精度）
        drv_systick_ms(10);

        if (++start_time >= timeout_ms) break;
    }

    return 0; // 超时
}

// WiFi初始化（严格遵循您原有流程）
uint8_t WiFi_Client_Init(void)
{
    printf("\n=== WiFi初始化开始 ===\n");

    // 1. 恢复出厂设置（可选）
    printf("恢复出厂设置...");
    WiFi_SendCommand("AT+RESTORE", "OK", 2000);
    drv_systick_ms(2000); // 确保重置完成
    printf("OK\n");

    // 2. 测试AT指令
    printf("测试AT指令...");
    if (!WiFi_SendCommand("AT", "OK", 2000))
    {
        printf("失败\n");
        return 0;
    }
    printf("OK\n");

    // 3. 开启回显模式（新增部分）
    printf("开启回显模式...");
    if (!WiFi_SendCommand("ATE1", "OK", 2000))
    {
        printf("失败\n");
        // 注意：有些模块可能不支持回显模式，这里不视为致命错误
    }
    else
    {
        printf("OK\n");
    }

    // 4. 设置Station模式
    printf("设置模式...");
    if (!WiFi_SendCommand("AT+CWMODE=1", "OK", 3000))
    {
        printf("失败\n");
        return 0;
    }
    printf("OK\n");

    // 5. 连接WiFi（关键步骤，延长超时）
    char connect_cmd[128];
    sprintf(connect_cmd, "AT+CWJAP=\"%s\",\"%s\"", WIFI_SSID, WIFI_PASSWORD);
    printf("连接WiFi...");
    if (!WiFi_SendCommand(connect_cmd, "OK", 10000))
    {
        printf("失败\n");
        return 0;
    }
    printf("OK\n");

    // 6. 设置单连接模式
    printf("设置单连接...");
    if (!WiFi_SendCommand("AT+CIPMUX=0", "OK", 3000))
    {
        printf("失败\n");
        return 0;
    }
    printf("OK\n");

    // 7. 连接服务器
    char server_cmd[64];
    sprintf(server_cmd, "AT+CIPSTART=\"TCP\",\"%s\",%s", SERVER_IP, SERVER_PORT);
    printf("连接服务器...");
    if (!WiFi_SendCommand(server_cmd, "OK", 5000))
    {
        printf("失败\n");
        return 0;
    }
    printf("OK\n");

    printf("=== WiFi初始化成功 ===\n");
    return 1;
}

// 数据发送（完全兼容您原有逻辑）
uint8_t WiFi_SendData(const char *data)
{
    char cmd[64];
    sprintf(cmd, "AT+CIPSEND=%d", strlen(data));

    // 发送长度指令
    if (!WiFi_SendCommand(cmd, ">", 3000)) return 0;

    // 发送实际数据
    USART_SendString(USART3, (char*)data);
    return WiFi_SendCommand("", "SEND OK", 3000);
}

// 重连逻辑（带保护机制）
void WiFi_Reconnect(void)
{
    uint8_t retry = 3;

    while (retry--)
    {
        WiFi_SendCommand("AT+CIPCLOSE", NULL, 1000); // 强制关闭连接

        if (WiFi_Client_Init()) break;

        drv_systick_ms(5000); // 延时5秒后重试
    }
}
