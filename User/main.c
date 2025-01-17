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
#include "pic.h"
#include "lcd.h"
#include "lcd_init.h"

int main(void)
{
    float t = 0;
    systick_config();//滴答定时器初始化 1ms

    LCD_Init();//屏幕初始化
    LCD_Fill(0,0,LCD_W,LCD_H,WHITE);//清全屏为白色
    
    while(1)
    {           
        LCD_ShowChinese(40,0,"中电子",RED,WHITE,32,0);
        LCD_ShowString(0,16*2,"LCD_W:",BLACK,WHITE,16,0);
        LCD_ShowIntNum(48,16*2,LCD_W,3,BLACK,WHITE,16);
        LCD_ShowString(80,16*2,"LCD_H:",BLACK,WHITE,16,0);
        LCD_ShowIntNum(128,16*2,LCD_H,3,BLACK,WHITE,16);
                
        LCD_ShowString(0,16*3,"Nun:",BLACK,WHITE,16,0);
        LCD_ShowFloatNum1(8*4,16*3,t,4,BLACK,WHITE,16);
                
        t+=0.11;

       delay_1ms(1000);        
    }
}