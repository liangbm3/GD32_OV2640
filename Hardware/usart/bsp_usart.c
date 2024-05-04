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
#include "bsp_usart.h"
#include "stdio.h"
#include "bsp_dma.h"

uint8_t 	g_recv_buff[USART_RECEIVE_LENGTH];   // ���ջ�����
uint16_t 	g_recv_length = 0;									 // �������ݳ���
uint8_t		g_recv_complete_flag = 0; 					 // ����������ɱ�־λ

/************************************************
�������� �� usart_gpio_config
��    �� �� ��������GPIO
��    �� �� band_rate:������
�� �� ֵ �� ��
��    �� �� LC
*************************************************/
void usart_gpio_config(uint32_t band_rate)
{
	/* ����ʱ�� */
	rcu_periph_clock_enable(BSP_USART_TX_RCU);   // ��������ʱ��
	rcu_periph_clock_enable(BSP_USART_RX_RCU);   // �����˿�ʱ��
	rcu_periph_clock_enable(BSP_USART_RCU);      // �����˿�ʱ��
	
	/* ����GPIO���ù��� */
  gpio_af_set(BSP_USART_TX_PORT,BSP_USART_AF,BSP_USART_TX_PIN);	
	gpio_af_set(BSP_USART_RX_PORT,BSP_USART_AF,BSP_USART_RX_PIN);	
	
	/* ����GPIO��ģʽ */
	/* ����TXΪ����ģʽ ����ģʽ */
	gpio_mode_set(BSP_USART_TX_PORT,GPIO_MODE_AF,GPIO_PUPD_PULLUP,BSP_USART_TX_PIN);
	/* ����RXΪ����ģʽ ����ģʽ */
	gpio_mode_set(BSP_USART_RX_PORT, GPIO_MODE_AF,GPIO_PUPD_PULLUP,BSP_USART_RX_PIN);
	
	/* ����TXΪ������� 50MHZ */
	gpio_output_options_set(BSP_USART_TX_PORT,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,BSP_USART_TX_PIN);
	/* ����RXΪ������� 50MHZ */
	gpio_output_options_set(BSP_USART_RX_PORT,GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, BSP_USART_RX_PIN);

	/* ���ô��ڵĲ��� */
	usart_deinit(BSP_USART);                                 // ��λ����
	usart_baudrate_set(BSP_USART,band_rate);                 // ���ò�����
	usart_parity_config(BSP_USART,USART_PM_NONE);            // û��У��λ
	usart_word_length_set(BSP_USART,USART_WL_8BIT);          // 8λ����λ
	usart_stop_bit_set(BSP_USART,USART_STB_1BIT);     			 // 1λֹͣλ

  /* ʹ�ܴ��� */
	usart_enable(BSP_USART);                                 // ʹ�ܴ���
	usart_transmit_config(BSP_USART,USART_TRANSMIT_ENABLE);  // ʹ�ܴ��ڷ���
	usart_receive_config(BSP_USART,USART_RECEIVE_ENABLE);    // ʹ�ܴ��ڽ���
	
    /* �ж����� */
    nvic_irq_enable(BSP_USART_IRQ, 2);              // �����ж����ȼ�
#if !USB_USART_DMA                                     // ʹ���ж�
    usart_interrupt_enable(BSP_USART, USART_INT_RBNE); // �����ݻ������ǿ��жϺ���������ж�
#endif
    usart_interrupt_enable(BSP_USART, USART_INT_IDLE); // ���м���ж�
}


/************************************************
�������� �� usart_send_data
��    �� �� �����ط���һ���ֽ�
��    �� �� ucch��Ҫ���͵��ֽ�
�� �� ֵ �� 
��    �� �� LC
*************************************************/
void usart_send_data(uint8_t ucch)
{
	usart_data_transmit(BSP_USART,(uint8_t)ucch);							 // ��������
	while(RESET == usart_flag_get(BSP_USART,USART_FLAG_TBE));  // �ȴ��������ݻ�������־��λ
}


/************************************************
�������� �� usart_send_String
��    �� �� ���ڷ����ַ���
��    �� �� ucstr:Ҫ���͵��ַ���
�� �� ֵ �� 
��    �� �� LC
*************************************************/
void usart_send_string(uint8_t *ucstr)
{
	while(ucstr && *ucstr)        // ��ַΪ�ջ���ֵΪ������
	{
	  usart_send_data(*ucstr++);  // ���͵����ַ�
	}
}

/************************************************
�������� �� fputc
��    �� �� �����ض�����
��    �� �� 
�� �� ֵ �� 
��    �� �� LC
*************************************************/
int fputc(int ch, FILE *f)
{
     usart_send_data(ch);
     // �ȴ��������ݻ�������־��λ
     return ch;
}

/************************************************
�������� �� BSP_USART_IRQHandler
��    �� �� ���ڽ����жϷ�����
��    �� �� ��
�� �� ֵ �� ��
��    �� �� LC
*************************************************/
void BSP_USART_IRQHandler(void)
{
#if !USB_USART_DMA                                                       // ʹ���ж�
    if (usart_interrupt_flag_get(BSP_USART, USART_INT_FLAG_RBNE) == SET) // ���ջ�������Ϊ��
    {
        g_recv_buff[g_recv_length++] = usart_data_receive(BSP_USART); // �ѽ��յ������ݷŵ���������
    }
#endif

    if (usart_interrupt_flag_get(BSP_USART, USART_INT_FLAG_IDLE) == SET) // ��⵽֡�ж�
    {
		usart_interrupt_flag_clear(USART0, USART_INT_FLAG_IDLE);
        usart_data_receive(BSP_USART); // ����Ҫ������������ֵ����Ҫ

#if USB_USART_DMA // ʹ��DMA
        /* ����DMA���յ������� */
        g_recv_length = USART_RECEIVE_LENGTH - dma_transfer_number_get(BSP_DMA_CH); // ����ʵ�ʽ��յ����ݳ���
        /* ��������DMA���� */
        dma_channel_disable(BSP_DMA_CH); // ʧ��DMAͨ��
        dma_config();                             // ��������DMA���д���
#endif

        g_recv_buff[g_recv_length] = '\0'; // ���ݽ�����ϣ����������־
        g_recv_complete_flag = 1;          // �������
    }
}

