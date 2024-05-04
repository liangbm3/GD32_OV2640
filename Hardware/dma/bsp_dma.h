#ifndef _BSP_DMA_H
#define _BSP_DMA_H

#include "gd32e23x.h"
#include "systick.h"


#define USB_USART_DMA 0

#define BSP_DMA_RCU 			RCU_DMA                            // DMAʱ��
#define BSP_DMA 				DMA                                    // DMA
#define BSP_DMA_CH 				DMA_CH2                              // DMAͨ��
#define BSP_DMA_CH_IRQ 			DMA_Channel1_2_IRQn               // DMA�ж�
#define BSP_DMA_CH_IRQ_HANDLER 	DMA_Channel1_2_IRQHandler 	// DMA�жϷ�������

void dma_config(void); // ����DMA

#endif /* BSP_DMA_H */