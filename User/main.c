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
#include "pic.h"
#include "lcd.h"
#include "lcd_init.h"
#include "ov2640.h"

u8* ov2640_framebuf;
#define OV2640_JPEG_WIDTH	320	//JPEG拍照的宽度
#define OV2640_JPEG_HEIGHT	240		//JPEG拍照的高度
//OV2640速度控制
//¸根据LCD分辨率的不同，设置不同的参数
void ov2640_speed_ctrl(void)
{
	u8 clkdiv,pclkdiv;			//时钟分频系数和PCLK分频系数
	clkdiv=3;
	pclkdiv=15;
	SCCB_WR_Reg(0XFF,0X00);		
	SCCB_WR_Reg(0XD3,pclkdiv);	//设置PCLK分频
	SCCB_WR_Reg(0XFF,0X01);
	SCCB_WR_Reg(0X11,clkdiv);	//设置CLK分频	
}
//ov2640拍照返回jpg图片
//返回值：0，成功
//		 1，失败
u8 ov2640_jpg_photo()
{
	u8 res=0;
	u32 i=0,t=0,j=0,c;
	u32 jpeglen=0;
	u8* pbuf;
	u32 Len=0;
	u8 s[4];
	
	OV2640_JPEG_Mode();							//切换为JPEG模式
  	OV2640_OutSize_Set(OV2640_JPEG_WIDTH,OV2640_JPEG_HEIGHT); 
	// SCCB_WR_Reg(0XFF,0X00);
	// SCCB_WR_Reg(0XD3,30);
	// SCCB_WR_Reg(0XFF,0X01);
	// SCCB_WR_Reg(0X11,0X1);
	for(i=0;i<10;i++)		//丢失10帧，等待ov2640自动调节好
	{
		while(OV2640_VSYNC()==1);	 
		while(OV2640_VSYNC()==0);	  
	}  
	while(OV2640_VSYNC()==1)	//开始采集JPEG数据
	{
		while(OV2640_HREF())
		{ 
			uint8_t tem[500];
			while(OV2640_PCLK()==0); 
			// ov2640_framebuf[jpeglen]=OV2640_DATA0();
			tem[jpeglen]=OV2640_DATA0();
			for(int i=0;i<500;i++)
			{
				printf("%d ",tem[i]);
			}
			
			while(OV2640_PCLK()==1);
			jpeglen++;
		} 
	}		
		pbuf=(u8*)ov2640_framebuf;
		for(i=0;i<jpeglen;i++)//查找0XFF,0XD8
		{
			if((pbuf[i]==0XFF)&&(pbuf[i+1]==0XD8))//记录帧头位置
			{
				t=i;
			}
			if((pbuf[i]==0XFF)&&(pbuf[i+1]==0XD9))//记录帧尾位置
			{
				j=i+1;
				break;
			}
		}
		Len=j-t+1;
		if(i==jpeglen)
		{
			res=1;//没找到
			
		}
		else		//找到了
		{
			pbuf+=t;//偏移到0XFF,0XD8´¦
			s[0]=(u8)(((Len)&0xff000000)>>24);
			s[1]=(u8)(((Len)&0xff0000)>>16);
			s[2]=(u8)(((Len)&0xff00)>>8);
			s[3]=(u8)((Len)&0xff);
		}
	return res;
}


int main(void)
{
    systick_config();			// 滴答定时器初始化
	usart_gpio_config(115200U); 	// 串口0初始化
    float t = 0;
    LCD_Init();//屏幕初始化
    LCD_Fill(0,0,LCD_W,LCD_H,WHITE);//清全屏为白色         
    #if USB_USART_DMA // 使用DMA
        printf("DMA receive\r\n");
        dma_config(); // DMA配置
    #else             // 使用中断
        printf("Interrupt receive\r\n");
    #endif
	
	if(OV2640_Init())
	{
		printf("ov2640错误！\r\n");
		delay_1ms(200);
	}
	delay_1ms(1500);
	OV2640_OutSize_Set(320,240);
	ov2640_speed_ctrl();
	ov2640_jpg_photo();
    while (1)
    {
		
        LCD_ShowChinese(40,0,"工训课",RED,WHITE,32,0);
        LCD_ShowString(0,16*2,"LCD_W:",BLACK,WHITE,16,0);
        LCD_ShowIntNum(48,16*2,LCD_W,3,BLACK,WHITE,16);
        LCD_ShowString(80,16*2,"LCD_H:",BLACK,WHITE,16,0);
        LCD_ShowIntNum(128,16*2,LCD_H,3,BLACK,WHITE,16);  
        LCD_ShowString(0,16*3,"Nun:",BLACK,WHITE,16,0);
        LCD_ShowFloatNum1(8*4,16*3,t,4,BLACK,WHITE,16);
        t+=0.11;
           /* 等待数据传输完成 INTERRUPT */ 
        printf("hello\n");
        delay_1ms(20);
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
