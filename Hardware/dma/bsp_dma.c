#include "bsp_dma.h"
#include "bsp_usart.h"

/************************************************
函数名称 ： dma_config
功    能 ： DMA配置
参    数 ： 无
返 回 值 ： 无
作    者 ： LC
*************************************************/
void dma_config(void)
{
    dma_parameter_struct dma_init_struct; // DMA单数据结构体
    rcu_periph_clock_enable(BSP_DMA_RCU);             // 开启DMA时钟

    dma_deinit(BSP_DMA_CH); // 初始化DMA通道

    /* 配置DMA初始化参数 */
    dma_init_struct.periph_addr = (uint32_t)&USART_TDATA(BSP_USART); // 外设地址
    dma_init_struct.periph_inc = DMA_PERIPH_INCREASE_DISABLE;       // 不使用增量模式，为固定模式
    dma_init_struct.memory_addr = (uint32_t)g_recv_buff;           // 内存地址
    dma_init_struct.memory_inc = DMA_MEMORY_INCREASE_ENABLE;        // 增量模式
    dma_init_struct.memory_width = DMA_MEMORY_WIDTH_8BIT;    // 一次传输长度8bit
	dma_init_struct.periph_width = DMA_PERIPHERAL_WIDTH_8BIT;    // 一次传输长度8bit
    dma_init_struct.direction = DMA_PERIPHERAL_TO_MEMORY;               // 外设到内存
    dma_init_struct.number = USART_RECEIVE_LENGTH;                  // 要传输的数据量
    dma_init_struct.priority = DMA_PRIORITY_ULTRA_HIGH;             // 超高优先级
    /* 初始化DMA结构体 */
    dma_init(BSP_DMA_CH, &dma_init_struct);
	
	
	dma_circulation_disable(BSP_DMA_CH); // 关闭循环
	dma_memory_to_memory_disable(BSP_DMA_CH);
	
	usart_dma_transmit_config(BSP_DMA, USART_DENT_ENABLE);
	
	    /* 使能DMA通道中断 */
    dma_interrupt_enable(BSP_DMA_CH, DMA_INT_FTF);
	
    /* 使能DMA通道 */
    dma_channel_enable(BSP_DMA_CH);

    /* 配置中断优先级 */
    nvic_irq_enable(BSP_DMA_CH_IRQ, 1);
    /* 使能串口DMA接收 */
    usart_dma_receive_config(BSP_USART, USART_DENR_ENABLE);
}

/************************************************
函数名称 ： BSP_DMA_CH_IRQHandler
功    能 ： DMA中断服务函数
参    数 ： 无
返 回 值 ： 无
作    者 ： LC
*************************************************/
void BSP_DMA_CH_IRQ_HANDLER(void)
{

    if (dma_interrupt_flag_get(BSP_DMA_CH, DMA_INT_FLAG_FTF) == SET) // 传输完成中断
    {
        dma_interrupt_flag_clear(BSP_DMA_CH, DMA_INT_FLAG_FTF); // 清中断标志位
        // g_recv_complete_flag = 1;                            // 数据传输完成
    }
}