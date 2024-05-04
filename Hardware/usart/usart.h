#ifndef __USART_H
#define __USART_H
#include "systick.h"
#include <stdint.h>
#include "stdio.h"
#include "gd32e23x.h"
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
//串口宏定义
//RX    PA3
//TX    PA4
/* -------------------------------------------------------------------------- */

//RX端口：
#define RCU_RX RCU_GPIOA
#define PORT_RX GPIOA
#define GPIO_RX GPIO_PIN_10

//TX端口：
#define RCU_TX RCU_GPIOA
#define PORT_TX GPIOA
#define GPIO_TX GPIO_PIN_9


/* -------------------------------------------------------------------------- */
//串口变量定义
/* -------------------------------------------------------------------------- */

//串口缓冲区的数据长度
#define USART_RECEIVE_LENGTH 4096

extern uint8_t  g_recv_buff[USART_RECEIVE_LENGTH]; // ½ÓÊÕ»º³åÇø
extern uint16_t g_recv_length;										 // ½ÓÊÕÊý¾Ý³¤¶È
extern uint8_t  g_recv_complete_flag; 						 // ½ÓÊÕÍê³É±êÖ¾Î»


/* -------------------------------------------------------------------------- */
//其他宏定义
/* -------------------------------------------------------------------------- */

//波特率：
#define BUAD_RATE 115200
  	

void usart_init(void);
void usart_send_data(uint8_t ucch); 
void usart_send_String(uint8_t *ucstr);
#endif


