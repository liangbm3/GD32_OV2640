#include "bsp_dma.h"
#include "bsp_usart.h"

/************************************************
�������� �� dma_config
��    �� �� DMA����
��    �� �� ��
�� �� ֵ �� ��
��    �� �� LC
*************************************************/
void dma_config(void)
{
    dma_parameter_struct dma_init_struct; // DMA�����ݽṹ��
    rcu_periph_clock_enable(BSP_DMA_RCU);             // ����DMAʱ��

    dma_deinit(BSP_DMA_CH); // ��ʼ��DMAͨ��

    /* ����DMA��ʼ������ */
    dma_init_struct.periph_addr = (uint32_t)&USART_TDATA(BSP_USART); // �����ַ
    dma_init_struct.periph_inc = DMA_PERIPH_INCREASE_DISABLE;       // ��ʹ������ģʽ��Ϊ�̶�ģʽ
    dma_init_struct.memory_addr = (uint32_t)g_recv_buff;           // �ڴ��ַ
    dma_init_struct.memory_inc = DMA_MEMORY_INCREASE_ENABLE;        // ����ģʽ
    dma_init_struct.memory_width = DMA_MEMORY_WIDTH_8BIT;    // һ�δ��䳤��8bit
	dma_init_struct.periph_width = DMA_PERIPHERAL_WIDTH_8BIT;    // һ�δ��䳤��8bit
    dma_init_struct.direction = DMA_PERIPHERAL_TO_MEMORY;               // ���赽�ڴ�
    dma_init_struct.number = USART_RECEIVE_LENGTH;                  // Ҫ�����������
    dma_init_struct.priority = DMA_PRIORITY_ULTRA_HIGH;             // �������ȼ�
    /* ��ʼ��DMA�ṹ�� */
    dma_init(BSP_DMA_CH, &dma_init_struct);
	
	
	dma_circulation_disable(BSP_DMA_CH); // �ر�ѭ��
	dma_memory_to_memory_disable(BSP_DMA_CH);
	
	usart_dma_transmit_config(BSP_DMA, USART_DENT_ENABLE);
	
	    /* ʹ��DMAͨ���ж� */
    dma_interrupt_enable(BSP_DMA_CH, DMA_INT_FTF);
	
    /* ʹ��DMAͨ�� */
    dma_channel_enable(BSP_DMA_CH);

    /* �����ж����ȼ� */
    nvic_irq_enable(BSP_DMA_CH_IRQ, 1);
    /* ʹ�ܴ���DMA���� */
    usart_dma_receive_config(BSP_USART, USART_DENR_ENABLE);
}

/************************************************
�������� �� BSP_DMA_CH_IRQHandler
��    �� �� DMA�жϷ�����
��    �� �� ��
�� �� ֵ �� ��
��    �� �� LC
*************************************************/
void BSP_DMA_CH_IRQ_HANDLER(void)
{

    if (dma_interrupt_flag_get(BSP_DMA_CH, DMA_INT_FLAG_FTF) == SET) // ��������ж�
    {
        dma_interrupt_flag_clear(BSP_DMA_CH, DMA_INT_FLAG_FTF); // ���жϱ�־λ
        // g_recv_complete_flag = 1;                            // ���ݴ������
    }
}