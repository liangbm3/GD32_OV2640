#ifndef __SCCB_H
#define __SCCB_H
#include "gd32e23x.h"
#include "systick.h"
#include <stdint.h>
#ifndef u8
#define u8 uint8_t
#endif

#ifndef u16
#define u16 uint16_t
#endif

#ifndef u32
#define u32 uint32_t
#endif

/* -------------------------------------------------------------------------- */
//端口宏定义
//复用端口：    SDA   PA1
//             SCL   PA0
//作者：lbm
//时间：2024.5.3
/* -------------------------------------------------------------------------- */

//SDA端口移植
#define RCU_SDA RCU_GPIOA
#define PORT_SDA GPIOA
#define GPIO_SDA GPIO_PIN_1

//SCL端口移植
#define RCU_SCL RCU_I2C1
#define PORT_SCL GPIOA
#define GPIO_SCL GPIO_PIN_0

//IIC
#define RCU_IIC RCU_I2C1
#define BSP_IIC I2C1
#define IIC_ADDR 0x80
#define IIC_AF GPIO_AF_4

/* -------------------------------------------------------------------------- */
//端口操作函数宏定义
//作者：lbm
//日期2024.5.3
/* -------------------------------------------------------------------------- */

//设置SDA的输入输出
#define SCCB_SDA_IN()  gpio_mode_set(PORT_SDA,GPIO_MODE_INPUT,GPIO_PUPD_PULLUP,GPIO_SDA)
#define SCCB_SDA_OUT() gpio_mode_set(PORT_SDA,GPIO_MODE_OUTPUT,GPIO_PUPD_PULLUP,GPIO_SDA)

//SDA和SCL的输出函数
#define SCCB_SDA(x) gpio_bit_write(PORT_SDA,GPIO_SDA,(x?SET:RESET))
#define SCCB_SCL(x) gpio_bit_write(PORT_SCL,GPIO_SCL,(x?SET:RESET))

//获取SDA的引脚电平变化
#define SCCB_READ_SDA() gpio_input_bit_get(PORT_SDA,GPIO_SDA)

//ov2640的id
#define SCCB_ID   			0X60  			

/* -------------------------------------------------------------------------- */
//函数声明
/* -------------------------------------------------------------------------- */
void SCCB_Init(void);//初始化SCCB接口
void SCCB_Start(void);//SCCB起始信号
void SCCB_Stop(void);//SCCB停止信号
void SCCB_No_Ack(void);//产生NA信号
u8 SCCB_WR_Byte(u8 dat);//SCCB写入一个字节
u8 SCCB_RD_Byte(void);//SCCB读取一个字节
u8 SCCB_WR_Reg(u8 reg,u8 data);//写寄存器
u8 SCCB_RD_Reg(u8 reg);//读寄存器
unsigned char I2C_WaitAck(void);
#endif













