#ifndef __LCD_INIT_H
#define __LCD_INIT_H
#include <stdint.h>
#include "systick.h"
#include <gd32e23x.h>

#define USE_HORIZONTAL 2  //设置横屏或者竖屏显示 0或1为竖屏，2或3为横屏

/* ----------------------------LCD端口移植 ----------------------------------- */
// VCC - 3.3V
// SCL - PB3    串行信号时钟输入
// SDA - PB4    串行信号数据输入
// RES - PB5    复位信号（低电平有效）
// DC  - PB6    数据/命令控制（拉高为数据、拉低为命令）
// CS  - PB7    片选输入（CS拉低时，芯片才能使能MCU通信）
// BLK - PB8    背光控制（默认打开背光、引脚拉低为关闭背光）                                                   */
/* -------------------------------------------------------------------------- */
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

/* --------------------------------- LCD端口定义 -------------------------------- */
//参考自嘉立创文档
/* -------------------------------------------------------------------------- */
#define LCD_SCLK_Clr() gpio_bit_write(PORT_LCD_SCL, GPIO_LCD_SCL, RESET)//SCL=SCLK
#define LCD_SCLK_Set() gpio_bit_write(PORT_LCD_SCL, GPIO_LCD_SCL, SET)

#define LCD_MOSI_Clr() gpio_bit_write(PORT_LCD_SDA, GPIO_LCD_SDA, RESET)//SDA=MOSI
#define LCD_MOSI_Set() gpio_bit_write(PORT_LCD_SDA, GPIO_LCD_SDA, SET)

#define LCD_RES_Clr()  gpio_bit_write(PORT_LCD_RES, GPIO_LCD_RES, RESET)//RES
#define LCD_RES_Set()  gpio_bit_write(PORT_LCD_RES, GPIO_LCD_RES, SET)

#define LCD_DC_Clr()   gpio_bit_write(PORT_LCD_DC, GPIO_LCD_DC, RESET)//DC
#define LCD_DC_Set()   gpio_bit_write(PORT_LCD_DC, GPIO_LCD_DC, SET)
                       
#define LCD_CS_Clr()   gpio_bit_write(PORT_LCD_CS, GPIO_LCD_CS, RESET)//CS
#define LCD_CS_Set()   gpio_bit_write(PORT_LCD_CS, GPIO_LCD_CS, SET)

#define LCD_BLK_Clr()  gpio_bit_write(PORT_LCD_BLK, GPIO_LCD_BLK, RESET)//BLK
#define LCD_BLK_Set()  gpio_bit_write(PORT_LCD_BLK, GPIO_LCD_BLK, SET)


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

void LCD_GPIO_Init(void);//初始化GPIO
void LCD_Writ_Bus(u8 dat);//模拟SPI时序
void LCD_WR_DATA8(u8 dat);//写入一个字节
void LCD_WR_DATA(u16 dat);//写入两个字节
void LCD_WR_REG(u8 dat);//写入一个指令
void LCD_Address_Set(u16 x1,u16 y1,u16 x2,u16 y2);//设置坐标函数
void LCD_Init(void);//LCD初始化
#endif




