#include "lcd_init.h"
#define delay_ms delay_1ms


/* -------------------------------------------------------------------------- */
//函数名称：LCD_GPIO_Init
//函数功能：初始化LCD相连的GPIO
//传入参数：无
//返回值：无
//作者：lbm
//时间：2024.5.1
/* -------------------------------------------------------------------------- */
void LCD_GPIO_Init(void)
{
	//使能时钟
	rcu_periph_clock_enable(RCU_LCD_SCL);
	rcu_periph_clock_enable(RCU_LCD_SDA);
	rcu_periph_clock_enable(RCU_LCD_CS);
	rcu_periph_clock_enable(RCU_LCD_DC);
	rcu_periph_clock_enable(RCU_LCD_RES);
	rcu_periph_clock_enable(RCU_LCD_BLK);

	//配置SCL
	gpio_mode_set(PORT_LCD_SCL,GPIO_MODE_OUTPUT,GPIO_PUPD_PULLUP,GPIO_LCD_SCL);
	gpio_output_options_set(PORT_LCD_SCL,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,GPIO_LCD_SCL);
	gpio_bit_write(PORT_LCD_SCL,GPIO_LCD_SCL,SET);

	//配置SDA
	gpio_mode_set(PORT_LCD_SDA,GPIO_MODE_OUTPUT,GPIO_PUPD_PULLUP,GPIO_LCD_SDA);
	gpio_output_options_set(PORT_LCD_SDA,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,GPIO_LCD_SDA);
	gpio_bit_write(PORT_LCD_SDA,GPIO_LCD_SDA,SET);

	//配置DC
	gpio_mode_set(PORT_LCD_DC,GPIO_MODE_OUTPUT,GPIO_PUPD_PULLUP,GPIO_LCD_DC);
	gpio_output_options_set(PORT_LCD_DC,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,GPIO_LCD_DC);
	gpio_bit_write(PORT_LCD_DC,GPIO_LCD_DC,SET);

	//配置CS
	gpio_mode_set(PORT_LCD_CS,GPIO_MODE_OUTPUT,GPIO_PUPD_PULLUP,GPIO_LCD_CS);
	gpio_output_options_set(PORT_LCD_CS,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,GPIO_LCD_CS);
	gpio_bit_write(PORT_LCD_CS,GPIO_LCD_CS,SET);

	//配置RES
	gpio_mode_set(PORT_LCD_RES,GPIO_MODE_OUTPUT,GPIO_PUPD_PULLUP,GPIO_LCD_RES);
	gpio_output_options_set(PORT_LCD_RES,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,GPIO_LCD_RES);
	gpio_bit_write(PORT_LCD_RES,GPIO_LCD_RES,SET);

	//配置BLK
	gpio_mode_set(PORT_LCD_BLK,GPIO_MODE_OUTPUT,GPIO_PUPD_PULLUP,GPIO_LCD_BLK);
	gpio_output_options_set(PORT_LCD_BLK,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,GPIO_LCD_BLK);
	gpio_bit_write(PORT_LCD_BLK,GPIO_LCD_BLK,SET);
}


/* -------------------------------------------------------------------------- */
//函数名称：LCD_Writ_Bus
//函数功能：LCD串行数据写入函数
//传入参数：dat	要写入的串行数据
//返回值：无
//最后一次修改时间：2024.5.1
/* -------------------------------------------------------------------------- */
void LCD_Writ_Bus(u8 dat) 
{	
	u8 i;
	LCD_CS_Clr();
	for(i=0;i<8;i++)
	{			  
		LCD_SCLK_Clr();
		if(dat&0x80)
		{
		   LCD_MOSI_Set();
		}
		else
		{
		   LCD_MOSI_Clr();
		}
		LCD_SCLK_Set();
		dat<<=1;
	}	
  LCD_CS_Set();	
}

/* -------------------------------------------------------------------------- */
//函数名称：LCD_WR_DATA8
//函数功能：写入一个字节数据
//传入参数：dat 要写入的8位数据
//返回值：无
//最后一次修改时间：2024.5.1
/* -------------------------------------------------------------------------- */
void LCD_WR_DATA8(u8 dat)
{
	LCD_Writ_Bus(dat);
}


/* -------------------------------------------------------------------------- */
//函数名称：LCD_WR_DATA
//函数功能：写入一个两个字节数据
//传入参数：dat 要写入的16位数据
//返回值：无
//最后一次修改时间：2024.5.1
/* -------------------------------------------------------------------------- */
void LCD_WR_DATA(u16 dat)
{
	LCD_Writ_Bus(dat>>8);
	LCD_Writ_Bus(dat);
}


/* -------------------------------------------------------------------------- */
//函数名称：LCD_WR_REG
//函数功能：写入一个指令
//传入参数：dat 要写入的指令
//返回值：无
//最后一次修改时间：2024.5.1
/* -------------------------------------------------------------------------- */
void LCD_WR_REG(u8 dat)
{
	LCD_DC_Clr();//写指令
	LCD_Writ_Bus(dat);
	LCD_DC_Set();//写数据
}


/* -------------------------------------------------------------------------- */
//函数名称：LCD_Address_Set
//函数功能：设置起始地址和结束地址
//传入参数：x1，x2 设置列的起始和结束地址
//		   y1，y2 设置行的起始和结束地址
//返回值：无
//最后一次修改时间：2024.5.1
/* -------------------------------------------------------------------------- */
void LCD_Address_Set(u16 x1,u16 y1,u16 x2,u16 y2)
{
	if(USE_HORIZONTAL==0)
	{
		LCD_WR_REG(0x2a);//列地址设置
		LCD_WR_DATA(x1+2);
		LCD_WR_DATA(x2+2);
		LCD_WR_REG(0x2b);//行地址设置
		LCD_WR_DATA(y1+1);
		LCD_WR_DATA(y2+1);
		LCD_WR_REG(0x2c);//存储器写
	}
	else if(USE_HORIZONTAL==1)
	{
		LCD_WR_REG(0x2a);//列地址设置
		LCD_WR_DATA(x1+2);
		LCD_WR_DATA(x2+2);
		LCD_WR_REG(0x2b);//行地址设置
		LCD_WR_DATA(y1+1);
		LCD_WR_DATA(y2+1);
		LCD_WR_REG(0x2c);//存储器写
	}
	else if(USE_HORIZONTAL==2)
	{
		LCD_WR_REG(0x2a);//列地址设置
		LCD_WR_DATA(x1+1);
		LCD_WR_DATA(x2+1);
		LCD_WR_REG(0x2b);//行地址设置
		LCD_WR_DATA(y1+2);
		LCD_WR_DATA(y2+2);
		LCD_WR_REG(0x2c);//存储器写
	}
	else
	{
		LCD_WR_REG(0x2a);//列地址设置
		LCD_WR_DATA(x1+1);
		LCD_WR_DATA(x2+1);
		LCD_WR_REG(0x2b);//行地址设置
		LCD_WR_DATA(y1+2);
		LCD_WR_DATA(y2+2);
		LCD_WR_REG(0x2c);//存储器写
	}
}


/* -------------------------------------------------------------------------- */
//函数名称：LCD_Init
//函数功能：进行LCD初始化
//传入参数：无
//返回值：无
//最后一次修改时间：2024.5.1
/* -------------------------------------------------------------------------- */
void LCD_Init(void)
{
	LCD_GPIO_Init();//初始化GPIO
	
	LCD_RES_Clr();//复位
	delay_ms(100);
	LCD_RES_Set();
	delay_ms(100);
	
	LCD_BLK_Set();//打开背光
  delay_ms(100);
	
	//************* Start Initial Sequence **********//
	LCD_WR_REG(0x11); //Sleep out 
	delay_ms(120);              //Delay 120ms 
	//------------------------------------ST7735S Frame Rate-----------------------------------------// 
	LCD_WR_REG(0xB1); 
	LCD_WR_DATA8(0x05); 
	LCD_WR_DATA8(0x3C); 
	LCD_WR_DATA8(0x3C); 
	LCD_WR_REG(0xB2); 
	LCD_WR_DATA8(0x05);
	LCD_WR_DATA8(0x3C); 
	LCD_WR_DATA8(0x3C); 
	LCD_WR_REG(0xB3); 
	LCD_WR_DATA8(0x05); 
	LCD_WR_DATA8(0x3C); 
	LCD_WR_DATA8(0x3C); 
	LCD_WR_DATA8(0x05); 
	LCD_WR_DATA8(0x3C); 
	LCD_WR_DATA8(0x3C); 
	//------------------------------------End ST7735S Frame Rate---------------------------------// 
	LCD_WR_REG(0xB4); //Dot inversion 
	LCD_WR_DATA8(0x03); 
	//------------------------------------ST7735S Power Sequence---------------------------------// 
	LCD_WR_REG(0xC0); 
	LCD_WR_DATA8(0x28); 
	LCD_WR_DATA8(0x08); 
	LCD_WR_DATA8(0x04); 
	LCD_WR_REG(0xC1); 
	LCD_WR_DATA8(0XC0); 
	LCD_WR_REG(0xC2); 
	LCD_WR_DATA8(0x0D); 
	LCD_WR_DATA8(0x00); 
	LCD_WR_REG(0xC3); 
	LCD_WR_DATA8(0x8D); 
	LCD_WR_DATA8(0x2A); 
	LCD_WR_REG(0xC4); 
	LCD_WR_DATA8(0x8D); 
	LCD_WR_DATA8(0xEE); 
	//---------------------------------End ST7735S Power Sequence-------------------------------------// 
	LCD_WR_REG(0xC5); //VCOM 
	LCD_WR_DATA8(0x1A); 
	LCD_WR_REG(0x36); //MX, MY, RGB mode 
	if(USE_HORIZONTAL==0)LCD_WR_DATA8(0x00);
	else if(USE_HORIZONTAL==1)LCD_WR_DATA8(0xC0);
	else if(USE_HORIZONTAL==2)LCD_WR_DATA8(0x70);
	else LCD_WR_DATA8(0xA0); 
	//------------------------------------ST7735S Gamma Sequence---------------------------------// 
	LCD_WR_REG(0xE0); 
	LCD_WR_DATA8(0x04); 
	LCD_WR_DATA8(0x22); 
	LCD_WR_DATA8(0x07); 
	LCD_WR_DATA8(0x0A); 
	LCD_WR_DATA8(0x2E); 
	LCD_WR_DATA8(0x30); 
	LCD_WR_DATA8(0x25); 
	LCD_WR_DATA8(0x2A); 
	LCD_WR_DATA8(0x28); 
	LCD_WR_DATA8(0x26); 
	LCD_WR_DATA8(0x2E); 
	LCD_WR_DATA8(0x3A); 
	LCD_WR_DATA8(0x00); 
	LCD_WR_DATA8(0x01); 
	LCD_WR_DATA8(0x03); 
	LCD_WR_DATA8(0x13); 
	LCD_WR_REG(0xE1); 
	LCD_WR_DATA8(0x04); 
	LCD_WR_DATA8(0x16); 
	LCD_WR_DATA8(0x06); 
	LCD_WR_DATA8(0x0D); 
	LCD_WR_DATA8(0x2D); 
	LCD_WR_DATA8(0x26); 
	LCD_WR_DATA8(0x23); 
	LCD_WR_DATA8(0x27); 
	LCD_WR_DATA8(0x27); 
	LCD_WR_DATA8(0x25); 
	LCD_WR_DATA8(0x2D); 
	LCD_WR_DATA8(0x3B); 
	LCD_WR_DATA8(0x00); 
	LCD_WR_DATA8(0x01); 
	LCD_WR_DATA8(0x04); 
	LCD_WR_DATA8(0x13); 
	//------------------------------------End ST7735S Gamma Sequence-----------------------------// 
	LCD_WR_REG(0x3A); //65k mode 
	LCD_WR_DATA8(0x05); 
	LCD_WR_REG(0x29); //Display on 
} 








