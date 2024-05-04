 /******************************************************************************
   * ����Ӳ�������������塤GD32E230C8T6    ʹ����Ƶ72Mhz    ����8Mhz
   * �� �� ��: V1.0
   * �޸�����: www.lckfb.com
   * �޸�����: 2023��11��02��
   * ���ܽ���:      
   *****************************************************************************
   * ��ɽ����Ӳ�������������չ����Ӳ�����Ϲ���ȫ����Դ  
   * �����������www.lckfb.com   
   * ����֧�ֳ�פ��̳���κμ������⻶ӭ��ʱ����ѧϰ  
   * ������̳��club.szlcsc.com   
   * ����ģ����ֲ�ֲ᣺��������GD32E230C8T6�����塿ģ����ֲ�ֲ�
   * ��עbilibili�˺ţ������������塿���������ǵ����¶�̬��
   * ��������׬Ǯ���������й�����ʦΪ����
  ******************************************************************************/

#ifndef _BSP_USART_H
#define _BSP_USART_H

#include "gd32e23x.h"
#include "systick.h"

#define BSP_USART_TX_RCU  		RCU_GPIOA   		// ����TX�Ķ˿�ʱ��
#define BSP_USART_RX_RCU  		RCU_GPIOA   		// ����RX�Ķ˿�ʱ��
#define BSP_USART_RCU     		RCU_USART0  		// ����0��ʱ��

#define BSP_USART_TX_PORT 		GPIOA				// ����TX�Ķ˿�
#define BSP_USART_RX_PORT 		GPIOA				// ����RX�Ķ˿�
#define BSP_USART_AF 			GPIO_AF_1   		// ����0�ĸ��ù���
#define BSP_USART_TX_PIN  		GPIO_PIN_9  		// ����TX������
#define BSP_USART_RX_PIN  		GPIO_PIN_10 		// ����RX������

#define BSP_USART 				USART0      		// ����0
#define BSP_USART_IRQ     		USART0_IRQn 		// ����0�ж�
#define BSP_USART_IRQHandler  	USART0_IRQHandler	// ����0�жϷ�����

/* ���ڻ����������ݳ��� */
#define USART_RECEIVE_LENGTH  4096

extern uint8_t  g_recv_buff[USART_RECEIVE_LENGTH]; // ���ջ�����
extern uint16_t g_recv_length;										 // �������ݳ���
extern uint8_t  g_recv_complete_flag; 						 // ������ɱ�־λ

void usart_gpio_config(uint32_t band_rate);  			 // ���ô���
void usart_send_data(uint8_t ucch);          			 // ����һ���ַ�
void usart_send_string(uint8_t *ucstr);      			 // ����һ���ַ���

#endif
