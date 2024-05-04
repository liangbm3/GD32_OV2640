#ifndef _BSP_DMA_H
#define _BSP_DMA_H

#include "gd32e23x.h"
#include "systick.h"


#define USB_USART_DMA 1

#define BSP_DMA_RCU 			RCU_DMA                            // DMA时钟
#define BSP_DMA 				DMA                                    // DMA
#define BSP_DMA_CH 				DMA_CH2                              // DMA通道
#define BSP_DMA_CH_IRQ 			DMA_Channel1_2_IRQn               // DMA中断
#define BSP_DMA_CH_IRQ_HANDLER 	DMA_Channel1_2_IRQHandler 	// DMA中断服务函数名

void dma_config(void); // 配置DMA

#endif /* BSP_DMA_H */