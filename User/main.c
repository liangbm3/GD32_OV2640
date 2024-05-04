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
#include "gd32e23x.h"
#include "systick.h"
#include <stdio.h>
#include "stdlib.h"
#include "string.h"
#include "bsp_dma.h"
#include "bsp_usart.h"


int main(void)
{
    systick_config();			// �δ�ʱ����ʼ��
	usart_gpio_config(115200U); 	// ����0��ʼ��

#if USB_USART_DMA // ʹ��DMA
    printf("DMA receive\r\n");
    dma_config(); // DMA����
#else             // ʹ���ж�
    printf("Interrupt receive\r\n");
#endif

    while (1)
    {

        /* �ȴ����ݴ������ */
        if (g_recv_complete_flag) // ���ݽ������
        {
            g_recv_complete_flag = 0;                   // �ȴ��´ν���
            printf("g_recv_length:%d ", g_recv_length); // ��ӡ���յ����ݳ���
            printf("g_recv_buff:%s\r\n", g_recv_buff);  // ��ӡ���յ�����
            memset(g_recv_buff, 0, g_recv_length);      // �������
            g_recv_length = 0;                          // ��ճ���
        }
    }
}
