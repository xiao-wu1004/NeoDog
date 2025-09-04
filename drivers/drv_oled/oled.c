#include "oled.h"
#include "stdlib.h"
#include "oledfont.h"
#include "drv_systick.h"
#include "drv_all.h"

uint8_t OLED_GRAM[144][8];

//���Ժ���
void OLED_ColorTurn(uint8_t i)
{
    if(i == 0)
    {
        OLED_WR_Byte(0xA6, OLED_CMD); //������ʾ
    }

    if(i == 1)
    {
        OLED_WR_Byte(0xA7, OLED_CMD); //��ɫ��ʾ
    }
}

//��Ļ��ת180��
void OLED_DisplayTurn(uint8_t i)
{
    if(i == 0)
    {
        OLED_WR_Byte(0xC8, OLED_CMD); //������ʾ
        OLED_WR_Byte(0xA1, OLED_CMD);
    }

    if(i == 1)
    {
        OLED_WR_Byte(0xC0, OLED_CMD); //��ת��ʾ
        OLED_WR_Byte(0xA0, OLED_CMD);
    }
}

//��ʱ
void IIC_delay(void)
{
    uint8_t t = 10;

    while(t--);
}

//��ʼ�ź�
void I2C_Start(void)
{
    OLED_SDA_Set();
    OLED_SCL_Set();
    IIC_delay();
    OLED_SDA_Clr();
    IIC_delay();
    OLED_SCL_Clr();
    IIC_delay();
}

//�����ź�
void I2C_Stop(void)
{
    OLED_SDA_Clr();
    OLED_SCL_Set();
    IIC_delay();
    OLED_SDA_Set();
}

//�ȴ��ź���Ӧ
void I2C_WaitAck(void) //�������źŵĵ�ƽ
{
    OLED_SDA_Set();
    IIC_delay();
    OLED_SCL_Set();
    IIC_delay();
    OLED_SCL_Clr();
    IIC_delay();
}

//д��һ���ֽ�
void Send_Byte(uint8_t dat)
{
    uint8_t i;

    for(i = 0; i < 8; i++)
    {
        if(dat & 0x80) //��dat��8λ�����λ����д��
        {
            OLED_SDA_Set();
        }
        else
        {
            OLED_SDA_Clr();
        }

        IIC_delay();
        OLED_SCL_Set();
        IIC_delay();
        OLED_SCL_Clr();//��ʱ���ź�����Ϊ�͵�ƽ
        dat <<= 1;
    }
}

//����һ���ֽ�
//mode:����/�����־ 0,��ʾ����;1,��ʾ����;
void OLED_WR_Byte(uint8_t dat, uint8_t mode)
{
    I2C_Start();
    Send_Byte(0x78);
    I2C_WaitAck();

    if(mode)
    {
        Send_Byte(0x40);
    }
    else
    {
        Send_Byte(0x00);
    }

    I2C_WaitAck();
    Send_Byte(dat);
    I2C_WaitAck();
    I2C_Stop();
}

//����OLED��ʾ
void OLED_DisPlay_On(void)
{
    OLED_WR_Byte(0x8D, OLED_CMD); //��ɱ�ʹ��
    OLED_WR_Byte(0x14, OLED_CMD); //������ɱ�
    OLED_WR_Byte(0xAF, OLED_CMD); //������Ļ
}

//�ر�OLED��ʾ
void OLED_DisPlay_Off(void)
{
    OLED_WR_Byte(0x8D, OLED_CMD); //��ɱ�ʹ��
    OLED_WR_Byte(0x10, OLED_CMD); //�رյ�ɱ�
    OLED_WR_Byte(0xAE, OLED_CMD); //�ر���Ļ
}

//�����Դ浽OLED
void OLED_Refresh(void)
{
    uint8_t i, n;

    for(i = 0; i < 8; i++)
    {
        OLED_WR_Byte(0xb0+i, OLED_CMD); //��������ʼ��ַ
        OLED_WR_Byte(0x00, OLED_CMD);  //���õ�����ʼ��ַ
        OLED_WR_Byte(0x10, OLED_CMD);  //���ø�����ʼ��ַ
        I2C_Start();
        Send_Byte(0x78);
        I2C_WaitAck();
        Send_Byte(0x40);
        I2C_WaitAck();

        for(n = 0; n < 128; n++)
        {
            Send_Byte(OLED_GRAM[n][i]);
            I2C_WaitAck();
        }

        I2C_Stop();
    }
}
//��������
void OLED_Clear(void)
{
    uint8_t i, n;

    for(i = 0; i < 8; i++)
    {
        for(n = 0; n < 128; n++)
        {
            OLED_GRAM[n][i] = 0; //�����������
        }
    }

    OLED_Refresh();//������ʾ
}

//����
//x:0~127
//y:0~63
//t:1 ��� 0,���
void OLED_DrawPoint(uint8_t x, uint8_t y, uint8_t t)
{
    uint8_t i, m, n;
    i = y / 8;
    m = y % 8;
    n = 1 << m;

    if(t)
    {
        OLED_GRAM[x][i] |= n;
    }
    else
    {
        OLED_GRAM[x][i] = ~OLED_GRAM[x][i];
        OLED_GRAM[x][i] |= n;
        OLED_GRAM[x][i] = ~OLED_GRAM[x][i];
    }
}

//����
//x1,y1:�������
//x2,y2:��������
void OLED_DrawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t mode)
{
    u16 t;
    int xerr = 0, yerr = 0, delta_x, delta_y, distance;
    int incx, incy, uRow, uCol;
    delta_x = x2 - x1; //������������
    delta_y = y2 - y1;
    uRow = x1; //�����������
    uCol = y1;

    if(delta_x > 0)incx = 1; //���õ�������
    else if (delta_x == 0)incx = 0; //��ֱ��
    else
    {
        incx = -1;
        delta_x = -delta_x;
    }

    if(delta_y > 0)incy = 1;
    else if (delta_y == 0)incy = 0; //ˮƽ��
    else
    {
        incy = -1;
        delta_y = -delta_x;
    }

    if(delta_x > delta_y)distance = delta_x; //ѡȡ��������������
    else distance = delta_y;

    for(t = 0; t < distance + 1; t++)
    {
        OLED_DrawPoint(uRow, uCol, mode); //����
        xerr += delta_x;
        yerr += delta_y;

        if(xerr > distance)
        {
            xerr -= distance;
            uRow += incx;
        }

        if(yerr > distance)
        {
            yerr -= distance;
            uCol += incy;
        }
    }
}
//x,y:Բ������
//r:Բ�İ뾶
void OLED_DrawCircle(uint8_t x, uint8_t y, uint8_t r)
{
    int a, b, num;
    a = 0;
    b = r;

    while(2 * b * b >= r * r)
    {
        OLED_DrawPoint(x + a, y - b, 1);
        OLED_DrawPoint(x - a, y - b, 1);
        OLED_DrawPoint(x - a, y + b, 1);
        OLED_DrawPoint(x + a, y + b, 1);

        OLED_DrawPoint(x + b, y + a, 1);
        OLED_DrawPoint(x + b, y - a, 1);
        OLED_DrawPoint(x - b, y - a, 1);
        OLED_DrawPoint(x - b, y + a, 1);

        a++;
        num = (a * a + b * b) - r * r; //���㻭�ĵ���Բ�ĵľ���

        if(num > 0)
        {
            b--;
            a--;
        }
    }
}



//��ָ��λ����ʾһ���ַ�,���������ַ�
//x:0~127
//y:0~63
//size1:ѡ������ 6x8/6x12/8x16/12x24
//mode:0,��ɫ��ʾ;1,������ʾ
void OLED_ShowChar(uint8_t x, uint8_t y, uint8_t chr, uint8_t size1, uint8_t mode)
{
    uint8_t i, m, temp, size2, chr1;
    uint8_t x0 = x, y0 = y;

    if(size1 == 8)size2 = 6;
    else size2 = (size1 / 8 + ((size1 % 8) ? 1 : 0)) * (size1 / 2); //�õ�����һ���ַ���Ӧ������ռ���ֽ���

    chr1 = chr - ' '; //����ƫ�ƺ��ֵ

    for(i = 0; i < size2; i++)
    {
        if(size1 == 8)
        {
            temp = asc2_0806[chr1][i];   //����0806����
        }
        else if(size1 == 12)
        {
            temp = asc2_1206[chr1][i];   //����1206����
        }
        else if(size1 == 16)
        {
            temp = asc2_1608[chr1][i];   //����1608����
        }
        else if(size1 == 24)
        {
            temp = asc2_2412[chr1][i];   //����2412����
        }
        else return;

        for(m = 0; m < 8; m++)
        {
            if(temp & 0x01)OLED_DrawPoint(x, y, mode);
            else OLED_DrawPoint(x, y, !mode);

            temp >>= 1;
            y++;
        }

        x++;

        if((size1 != 8) && ((x - x0) == size1 / 2))
        {
            x = x0;
            y0 = y0 + 8;
        }

        y = y0;
    }
}


//��ʾ�ַ���
//x,y:�������
//size1:�����С
//*chr:�ַ�����ʼ��ַ
//mode:0,��ɫ��ʾ;1,������ʾ
void OLED_ShowString(uint8_t x, uint8_t y, uint8_t *chr, uint8_t size1, uint8_t mode)
{
    while((*chr >= ' ') && (*chr <= '~')) //�ж��ǲ��ǷǷ��ַ�!
    {
        OLED_ShowChar(x, y, *chr, size1, mode);

        if(size1 == 8)x += 6;
        else x += size1 / 2;

        chr++;
    }
}

//m^n
u32 OLED_Pow(uint8_t m, uint8_t n)
{
    u32 result = 1;

    while(n--)
    {
        result *= m;
    }

    return result;
}

//��ʾ����
//x,y :�������
//num :Ҫ��ʾ������
//len :���ֵ�λ��
//size:�����С
//mode:0,��ɫ��ʾ;1,������ʾ
void OLED_ShowNum(uint8_t x, uint8_t y, u32 num, uint8_t len, uint8_t size1, uint8_t mode)
{
    uint8_t t, temp, m = 0;

    if(size1 == 8)m = 2;

    for(t = 0; t < len; t++)
    {
        temp = (num / OLED_Pow(10, len - t - 1)) % 10;

        if(temp == 0)
        {
            OLED_ShowChar(x + (size1 / 2 + m)*t, y, '0', size1, mode);
        }
        else
        {
            OLED_ShowChar(x + (size1 / 2 + m)*t, y, temp + '0', size1, mode);
        }
    }
}

//��ʾ����
//x,y:�������
//num:���ֶ�Ӧ�����
//mode:0,��ɫ��ʾ;1,������ʾ
void OLED_ShowChinese(uint8_t x, uint8_t y, uint8_t num, uint8_t size1, uint8_t mode)
{
    uint8_t m, temp;
    uint8_t x0 = x, y0 = y;
    u16 i, size3 = (size1 / 8 + ((size1 % 8) ? 1 : 0)) * size1; //�õ�����һ���ַ���Ӧ������ռ���ֽ���

    for(i = 0; i < size3; i++)
    {
        if(size1 == 16)
        {
            temp = Hzk1[num][i];   //����16*16����
        }
        else if(size1 == 24)
        {
            temp = Hzk2[num][i];   //����24*24����
        }
        else if(size1 == 32)
        {
            temp = Hzk3[num][i];   //����32*32����
        }
        else if(size1 == 64)
        {
            temp = Hzk4[num][i];   //����64*64����
        }
        else return;

        for(m = 0; m < 8; m++)
        {
            if(temp & 0x01)OLED_DrawPoint(x, y, mode);
            else OLED_DrawPoint(x, y, !mode);

            temp >>= 1;
            y++;
        }

        x++;

        if((x - x0) == size1)
        {
            x = x0;
            y0 = y0 + 8;
        }

        y = y0;
    }
}

//num ��ʾ���ֵĸ���
//space ÿһ����ʾ�ļ��
//mode:0,��ɫ��ʾ;1,������ʾ
void OLED_ScrollDisplay(uint8_t num, uint8_t space, uint8_t mode)
{
    uint8_t i, n, t = 0, m = 0, r;

    while(1)
    {
        if(m == 0)
        {
            OLED_ShowChinese(128, 24, t, 16, mode); //д��һ�����ֱ�����OLED_GRAM[][]������
            t++;
        }

        if(t == num)
        {
            for(r = 0; r < 16 * space; r++) //��ʾ���
            {
                for(i = 1; i < 144; i++)
                {
                    for(n = 0; n < 8; n++)
                    {
                        OLED_GRAM[i - 1][n] = OLED_GRAM[i][n];
                    }
                }

                OLED_Refresh();
            }

            t = 0;
        }

        m++;

        if(m == 16)
        {
            m = 0;
        }

        for(i = 1; i < 144; i++) //ʵ������
        {
            for(n = 0; n < 8; n++)
            {
                OLED_GRAM[i - 1][n] = OLED_GRAM[i][n];
            }
        }

        OLED_Refresh();
    }
}

//x,y���������
//sizex,sizey,ͼƬ����
//BMP[]��Ҫд���ͼƬ����
//mode:0,��ɫ��ʾ;1,������ʾ
void OLED_ShowPicture(uint8_t x, uint8_t y, uint8_t sizex, uint8_t sizey, uint8_t BMP[], uint8_t mode)
{
    u16 j = 0;
    uint8_t i, n, temp, m;
    uint8_t x0 = x, y0 = y;
    sizey = sizey / 8 + ((sizey % 8) ? 1 : 0);

    for(n = 0; n < sizey; n++)
    {
        for(i = 0; i < sizex; i++)
        {
            temp = BMP[j];
            j++;

            for(m = 0; m < 8; m++)
            {
                if(temp & 0x01)OLED_DrawPoint(x, y, mode);
                else OLED_DrawPoint(x, y, !mode);

                temp >>= 1;
                y++;
            }

            x++;

            if((x - x0) == sizex)
            {
                x = x0;
                y0 = y0 + 8;
            }

            y = y0;
        }
    }
}



////-------------------------------------------------------------------------------------------------

///**
//  * @brief  ��ʾGIF��֡
//  * @param  x,y: ��ʾλ��(��,ҳ)
//  * @param  anim: ����ָ��
//  * @param  frame_idx: ֡����
//  * @retval ��
//  */
//void OLED_ShowGIFFrame(uint8_t x, uint8_t y, const GIF_Animation *anim, uint16_t frame_idx)
//{
//    if(anim == NULL || frame_idx >= anim->frame_count) return;
//
//    uint8_t pages = anim->height / 8;
//    if(anim->height % 8) pages++;
//
//    const uint8_t *frame = anim->frames[frame_idx]; // ͨ��ָ���������
//    uint16_t index = 0;
//    uint8_t page, col;
//
//    for(page = 0; page < pages; page++) {
//        OLED_WR_Byte(0xB0 + page + y/8, OLED_CMD);
//        OLED_WR_Byte(x & 0x0F, OLED_CMD);
//        OLED_WR_Byte(0x10 | (x >> 4), OLED_CMD);
//
//        I2C_Start();
//        Send_Byte(0x78);
//        I2C_WaitAck();
//        Send_Byte(0x40);
//        I2C_WaitAck();
//
//        for(col = 0; col < anim->width; col++) {
//            Send_Byte(frame[index++]);
//            I2C_WaitAck();
//            if(index >= anim->frame_size) break;
//        }
//
//        I2C_Stop();
//    }
//}

///**
//  * @brief  ��ʼ��GIF������
//  * @param  player: ������ָ��
//  * @param  anims: ��������
//  * @param  count: ��������
//  * @retval ��
//  */
//void GIF_Player_Init(GIF_Player *player, GIF_Animation *anims, uint8_t count) {
//    if(player == NULL || anims == NULL || count == 0) return;
//
//    memset(player, 0, sizeof(GIF_Player));
//    player->animations = anims;
//    player->count = count;
//    player->playing = 1;
//}

///**
//  * @brief  ����GIF������
//  * @param  player: ������ָ��
//  * @param  x,y: ��ʾλ��
//  * @retval ��
//  */

//void GIF_Player_Update(GIF_Player *player, uint8_t x, uint8_t y) {
//    if(player == NULL || !player->playing || player->count == 0)
//        return;
//
//    GIF_Animation *current = &player->animations[player->current_anim];
//
//    if(++player->frame_counter >= (current->delay_ms / 10)) { // ������ѭ������10ms
//        player->frame_counter = 0;
//
//        OLED_ShowGIFFrame(x, y, current, player->current_frame);
//
//        if(++player->current_frame >= current->frame_count) {
//            player->current_frame = 0;
//            if(current->loop_count > 0 && --current->loop_count == 0) {
//                player->current_anim = (player->current_anim + 1) % player->count;
//            }
//        }
//    }
//}
///**
//  * @brief  �л���ָ������
//  * @param  player: ������ָ��
//  * @param  anim_index: ��������
//  * @retval 0�ɹ�, -1ʧ��
//  */
//int GIF_Player_SwitchAnim(GIF_Player *player, uint8_t anim_index) {
//    if(player == NULL || anim_index >= player->count) return -1;
//
//    player->current_anim = anim_index;
//    player->current_frame = 0;
//    player->frame_counter = 0; // ���ü�����
//    return 0;
//}

///**
//  * @brief  ���Ʋ���״̬
//  * @param  player: ������ָ��
//  * @param  play: 1����, 0��ͣ
//  * @retval ��
//  */
//void GIF_Player_Control(GIF_Player *player, uint8_t play) {
//    if(player == NULL) return;
//    player->playing = play;
//}

///**
//  * @brief  ���ö���ѭ������
//  * @param  player: ������ָ��
//  * @param  anim_index: ��������
//  * @param  loop_count: ѭ������
//  * @retval 0�ɹ�, -1ʧ��
//  */
//int GIF_Player_SetLoopCount(GIF_Player *player, uint8_t anim_index, uint8_t loop_count) {
//    if(player == NULL || anim_index >= player->count) return -1;
//    player->animations[anim_index].loop_count = loop_count;
//    return 0;
//}

///**
//  * @brief  ��ȡ��ǰ��������
//  * @param  player: ������ָ��
//  * @retval ��ǰ��������
//  */
//uint8_t GIF_Player_GetCurrentAnim(GIF_Player *player) {
//    return (player != NULL) ? player->current_anim : 0;
//}

///**
//  * @brief  ��ȡ��ǰ֡����
//  * @param  player: ������ָ��
//  * @retval ��ǰ֡����
//  */
//uint8_t GIF_Player_GetCurrentFrame(GIF_Player *player) {
//    return (player != NULL) ? player->current_frame : 0;
//}

///**
//  * @brief  ��ȡ����״̬
//  * @param  player: ������ָ��
//  * @retval 1���ڲ���, 0��ͣ����Ч
//  */
//uint8_t GIF_Player_IsPlaying(GIF_Player *player) {
//    return (player != NULL) ? player->playing : 0;
//}

///**
//  * @brief  ���ö���������
//  * @param  player: ������ָ��
//  * @retval ��
//  */
//void GIF_Player_Reset(GIF_Player *player) {
//    if(player == NULL) return;
//    player->current_anim = 0;
//    player->current_frame = 0;
//    player->frame_counter = 0;
//}
////-------------------------------------------------------------------------------------------------


///**
//  * @brief  ��ʾGIF����
//  * @param  x0: ��ʼ��(0-127)
//  * @param  y0: ��ʼ��(0-63)
//  * @param  x1: ��ֹ��(0-127)
//  * @param  y1: ��ֹ��(0-63)
//  * @param  k: ��֡��
//  * @param  m: ��֡���ݴ�С
//  * @param  GIF[][m]: GIF��������
//  * @retval ��
//  */
//void OLED_DrawGIF(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t k, uint16_t m, uint8_t GIF[][m])
//{
//    uint16_t j = 0; // ��������
//    uint8_t x, y, i, page;
//    uint8_t height_pages = (y1 - y0) / 8;
//    if((y1 - y0) % 8) height_pages++;
//
//    for(i = 0; i < k; i++) // ����ÿһ֡
//    {
//        j = 0;
//        // ��֡����д���Դ�
//        for(page = 0; page < height_pages; page++)
//        {
//            for(x = x0; x < x1; x++)
//            {
//                if(j < m) // ��ֹ����Խ��
//                {
//                    OLED_GRAM[x][page + y0/8] = GIF[i][j++];
//                }
//            }
//        }
//
//        OLED_Refresh(); // ������ʾ
//        drv_systick_ms(10); // ʹ��ϵͳ��ʱ��������֡��
//    }
//}


//OLED�ĳ�ʼ��
//pb12->scl
//pb13->sda
void OLED_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); //ʹ��PORTA~E,PORTGʱ��

    //GPIO��ʼ������
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;//�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
    GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��

//	OLED_RES_Clr();
//	drv_systick_ms(200);
//	OLED_RES_Set();

    OLED_WR_Byte(0xAE, OLED_CMD); //--turn off oled panel
    OLED_WR_Byte(0x00, OLED_CMD); //---set low column address
    OLED_WR_Byte(0x10, OLED_CMD); //---set high column address
    OLED_WR_Byte(0x40, OLED_CMD); //--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
    OLED_WR_Byte(0x81, OLED_CMD); //--set contrast control register
    OLED_WR_Byte(0xCF, OLED_CMD); // Set SEG Output Current Brightness
    OLED_WR_Byte(0xA1, OLED_CMD); //--Set SEG/Column Mapping     0xa0���ҷ��� 0xa1����
    OLED_WR_Byte(0xC8, OLED_CMD); //Set COM/Row Scan Direction   0xc0���·��� 0xc8����
    OLED_WR_Byte(0xA6, OLED_CMD); //--set normal display
    OLED_WR_Byte(0xA8, OLED_CMD); //--set multiplex ratio(1 to 64)
    OLED_WR_Byte(0x3f, OLED_CMD); //--1/64 duty
    OLED_WR_Byte(0xD3, OLED_CMD); //-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
    OLED_WR_Byte(0x00, OLED_CMD); //-not offset
    OLED_WR_Byte(0xd5, OLED_CMD); //--set display clock divide ratio/oscillator frequency
    OLED_WR_Byte(0x80, OLED_CMD); //--set divide ratio, Set Clock as 100 Frames/Sec
    OLED_WR_Byte(0xD9, OLED_CMD); //--set pre-charge period
    OLED_WR_Byte(0xF1, OLED_CMD); //Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
    OLED_WR_Byte(0xDA, OLED_CMD); //--set com pins hardware configuration
    OLED_WR_Byte(0x12, OLED_CMD);
    OLED_WR_Byte(0xDB, OLED_CMD); //--set vcomh
    OLED_WR_Byte(0x40, OLED_CMD); //Set VCOM Deselect Level
    OLED_WR_Byte(0x20, OLED_CMD); //-Set Page Addressing Mode (0x00/0x01/0x02)
    OLED_WR_Byte(0x02, OLED_CMD); //
    OLED_WR_Byte(0x8D, OLED_CMD); //--set Charge Pump enable/disable
    OLED_WR_Byte(0x14, OLED_CMD); //--set(0x10) disable
    OLED_WR_Byte(0xA4, OLED_CMD); // Disable Entire Display On (0xa4/0xa5)
    OLED_WR_Byte(0xA6, OLED_CMD); // Disable Inverse Display On (0xa6/a7)
    OLED_Clear();
    OLED_WR_Byte(0xAF, OLED_CMD);
    //printf("OLED \r\n");
}

