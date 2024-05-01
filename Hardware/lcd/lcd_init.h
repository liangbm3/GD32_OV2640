#ifndef __LCD_INIT_H
#define __LCD_INIT_H
#include <stdint.h>
#include "systick.h"
#include <gd32e23x.h>

#define USE_HORIZONTAL 1  //设置横屏或者竖屏显示 0或1为竖屏，2或3为横屏

//-----------------LCD端口移植---------------- 
// VCC - 3.3V
// SCL - PB3    串行信号时钟输入
// SDA - PB4    串行信号数据输入
// RES - PB5    复位信号（低电平有效）
// DC  - PB6    数据/命令控制（拉高为数据、拉低为命令）
// CS  - PB7    片选输入（CS拉低时，芯片才能使能MCU通信）
// BLK - PB8    背光控制（默认打开背光、引脚拉低为关闭背光）

#define RCU_LCD_SCL     RCU_GPIOB//SCK
#define PORT_LCD_SCL    GPIOB
#define GPIO_LCD_SCL    GPIO_PIN_3

#define RCU_LCD_SDA     RCU_GPIOB//MOSI
#define PORT_LCD_SDA    GPIOB
#define GPIO_LCD_SDA    GPIO_PIN_4

#define RCU_LCD_CS      RCU_GPIOB//NSS
#define PORT_LCD_CS     GPIOB
#define GPIO_LCD_CS     GPIO_PIN_7

#define RCU_LCD_DC      RCU_GPIOB //DC
#define PORT_LCD_DC     GPIOB
#define GPIO_LCD_DC     GPIO_PIN_6

#define RCU_LCD_RES     RCU_GPIOB//RES
#define PORT_LCD_RES    GPIOB
#define GPIO_LCD_RES    GPIO_PIN_5

#define RCU_LCD_BLK     RCU_GPIOB//BLK
#define PORT_LCD_BLK    GPIOB
#define GPIO_LCD_BLK    GPIO_PIN_8


#if USE_HORIZONTAL==0||USE_HORIZONTAL==1
#define LCD_W 128
#define LCD_H 160

#else
#define LCD_W 160
#define LCD_H 128
#endif
	
#ifndef u8
#define u8 uint8_t
#endif

#ifndef u16
#define u16 uint16_t
#endif

#ifndef u32
#define u32 uint32_t
#endif

//-----------------LCD�˿ڶ���---------------- 

#define LCD_SCLK_Clr() GPIO_ResetBits(GPIOA,GPIO_Pin_0)//SCL=SCLK
#define LCD_SCLK_Set() GPIO_SetBits(GPIOA,GPIO_Pin_0)

#define LCD_MOSI_Clr() GPIO_ResetBits(GPIOA,GPIO_Pin_1)//SDA=MOSI
#define LCD_MOSI_Set() GPIO_SetBits(GPIOA,GPIO_Pin_1)

#define LCD_RES_Clr()  GPIO_ResetBits(GPIOA,GPIO_Pin_2)//RES
#define LCD_RES_Set()  GPIO_SetBits(GPIOA,GPIO_Pin_2)

#define LCD_DC_Clr()   GPIO_ResetBits(GPIOA,GPIO_Pin_3)//DC
#define LCD_DC_Set()   GPIO_SetBits(GPIOA,GPIO_Pin_3)
 		     
#define LCD_CS_Clr()   GPIO_ResetBits(GPIOA,GPIO_Pin_4)//CS
#define LCD_CS_Set()   GPIO_SetBits(GPIOA,GPIO_Pin_4)

#define LCD_BLK_Clr()  GPIO_ResetBits(GPIOA,GPIO_Pin_5)//BLK
#define LCD_BLK_Set()  GPIO_SetBits(GPIOA,GPIO_Pin_5)




void LCD_GPIO_Init(void);//��ʼ��GPIO
void LCD_Writ_Bus(u8 dat);//ģ��SPIʱ��
void LCD_WR_DATA8(u8 dat);//д��һ���ֽ�
void LCD_WR_DATA(u16 dat);//д�������ֽ�
void LCD_WR_REG(u8 dat);//д��һ��ָ��
void LCD_Address_Set(u16 x1,u16 y1,u16 x2,u16 y2);//�������꺯��
void LCD_Init(void);//LCD��ʼ��
#endif




