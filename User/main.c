 /******************************************************************************
   * 测试硬件：立创开发板·GD32E230C8T6    使用主频72Mhz    晶振8Mhz
   * 版 本 号: V1.0
   * 修改作者: www.lckfb.com
   * 修改日期: 2023年11月02日
   * 功能介绍:      
   *****************************************************************************
   * 梁山派软硬件资料与相关扩展板软硬件资料官网全部开源  
   * 开发板官网：www.lckfb.com   
   * 技术支持常驻论坛，任何技术问题欢迎随时交流学习  
   * 立创论坛：club.szlcsc.com   
   * 其余模块移植手册：【立创·GD32E230C8T6开发板】模块移植手册
   * 关注bilibili账号：【立创开发板】，掌握我们的最新动态！
   * 不靠卖板赚钱，以培养中国工程师为己任
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
    systick_config();			// 滴答定时器初始化
	usart_gpio_config(115200U); 	// 串口0初始化

#if USB_USART_DMA // 使用DMA
    printf("DMA receive\r\n");
    dma_config(); // DMA配置
#else             // 使用中断
    printf("Interrupt receive\r\n");
#endif

    while (1)
    {

        /* 等待数据传输完成 */
        if (g_recv_complete_flag) // 数据接收完成
        {
            g_recv_complete_flag = 0;                   // 等待下次接收
            printf("g_recv_length:%d ", g_recv_length); // 打印接收的数据长度
            printf("g_recv_buff:%s\r\n", g_recv_buff);  // 打印接收的数据
            memset(g_recv_buff, 0, g_recv_length);      // 清空数组
            g_recv_length = 0;                          // 清空长度
        }
    }
}
