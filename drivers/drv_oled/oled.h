#ifndef __OLED_H
#define __OLED_H

//#include "sys.h"
#include "stdlib.h"
#include "stm32f4xx.h"

//-----------------OLED�˿ڶ���----------------
//pb12->scl
//pb13->sda
#define OLED_SCL_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_12)//SCL
#define OLED_SCL_Set() GPIO_SetBits(GPIOB,GPIO_Pin_12)

#define OLED_SDA_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_13)//DIN
#define OLED_SDA_Set() GPIO_SetBits(GPIOB,GPIO_Pin_13)

#define OLED_RES_Clr() GPIO_ResetBits(GPIOD,GPIO_Pin_4)//RES
#define OLED_RES_Set() GPIO_SetBits(GPIOD,GPIO_Pin_4)


#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����

void OLED_ClearPoint(uint8_t x, uint8_t y);
void OLED_ColorTurn(uint8_t i);
void OLED_DisplayTurn(uint8_t i);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_WaitAck(void);
void Send_Byte(uint8_t dat);
void OLED_WR_Byte(uint8_t dat, uint8_t mode);
void OLED_DisPlay_On(void);
void OLED_DisPlay_Off(void);
void OLED_Refresh(void);
void OLED_Clear(void);
void OLED_DrawPoint(uint8_t x, uint8_t y, uint8_t t);
void OLED_DrawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t mode);
void OLED_DrawCircle(uint8_t x, uint8_t y, uint8_t r);
void OLED_ShowChar(uint8_t x, uint8_t y, uint8_t chr, uint8_t size1, uint8_t mode);
void OLED_ShowChar6x8(uint8_t x, uint8_t y, uint8_t chr, uint8_t mode);
void OLED_ShowString(uint8_t x, uint8_t y, uint8_t *chr, uint8_t size1, uint8_t mode);
void OLED_ShowNum(uint8_t x, uint8_t y, uint32_t num, uint8_t len, uint8_t size1, uint8_t mode);
void OLED_ShowChinese(uint8_t x, uint8_t y, uint8_t num, uint8_t size1, uint8_t mode);
void OLED_ScrollDisplay(uint8_t num, uint8_t space, uint8_t mode);
void OLED_ShowPicture(uint8_t x, uint8_t y, uint8_t sizex, uint8_t sizey, uint8_t BMP[], uint8_t mode);
void OLED_Init(void);



/* GIF�����ṹ�� */
typedef struct
{
    const uint8_t **frames;    // ָ֡�����飨ÿ��Ԫ��ָ��һ֡��
    uint16_t frame_count;      // ��֡����45֡��
    uint16_t frame_size;       // ��֡��С��512�ֽڣ�
    uint8_t width;             // ͼ���ȣ�64���أ�
    uint8_t height;            // ͼ��߶ȣ�64���أ�
    uint16_t delay_ms;         // ֡���ʱ�䣨���룩
    uint8_t loop_count;        // ѭ��������0=���ޣ�
} GIF_Animation;

///* �����������ṹ�壨�򻯰棩*/
//typedef struct {
//    GIF_Animation *animations;
//    uint8_t count;
//    uint8_t current_anim;
//    uint16_t current_frame;    // ֧��45֡
//    uint8_t playing;
//    uint16_t frame_counter;    // �򻯵�֡������
//} GIF_Player;

//void OLED_ShowGIFFrame(uint8_t x, uint8_t y, const GIF_Animation *anim, uint16_t frame_idx);
//void GIF_Player_Init(GIF_Player *player, GIF_Animation *anims, uint8_t count);
//void GIF_Player_Update(GIF_Player *player, uint8_t x, uint8_t y);
//int GIF_Player_SwitchAnim(GIF_Player *player, uint8_t anim_index);
//void GIF_Player_Control(GIF_Player *player, uint8_t play);
//int GIF_Player_SetLoopCount(GIF_Player *player, uint8_t anim_index, uint8_t loop_count);
//uint8_t GIF_Player_GetCurrentAnim(GIF_Player *player);
//uint8_t GIF_Player_GetCurrentFrame(GIF_Player *player);
//uint8_t GIF_Player_IsPlaying(GIF_Player *player);
//void GIF_Player_Reset(GIF_Player *player);


//void OLED_DrawGIF(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t k, uint16_t m, uint8_t GIF[][m]);
#endif

