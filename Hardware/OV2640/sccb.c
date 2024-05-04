#include "systick.h"
#include "sccb.h"

/* -------------------------------------------------------------------------- */
//函数名称：SCCB_Init
//函数功能：初始化SCCB接口
//传入参数：无
//返回值：无
//作者：lbm
//日期：2024.5.1
/* -------------------------------------------------------------------------- */
void SCCB_Init(void)
{						
	//使能时钟
	rcu_periph_clock_enable(RCU_SCL);
	rcu_periph_clock_enable(RCU_SDA);

	//设置SCL为输出模式
	gpio_mode_set(PORT_SCL,GPIO_MODE_OUTPUT,GPIO_PUPD_PULLUP,GPIO_SCL);
	//配置为开漏输出、50MHZ
	gpio_output_options_set(PORT_SCL,GPIO_OTYPE_OD,GPIO_OSPEED_50MHZ,GPIO_SCL);
	//设置高电平
	SCCB_SCL(1);

	//配置SDA为输出模式
	gpio_mode_set(PORT_SDA,GPIO_MODE_OUTPUT,GPIO_PUPD_PULLUP,GPIO_SDA);
	//配置为开漏输出、50MHZ
	gpio_output_options_set(PORT_SDA,GPIO_OTYPE_OD,GPIO_OSPEED_50MHZ,GPIO_SDA);
	//设置高电平
	SCCB_SDA(1);
}			 

/* -------------------------------------------------------------------------- */
//函数名称：时序信号模拟函数
//函数作用：模拟IIC的时序信号
//输入参数：见注释
//返回值：见注释
//作者：lbm
//日期：2024.5.30
/* -------------------------------------------------------------------------- */

//SCCB起始信号
//当时钟为高时，数据线由低到高，为起始信号
//在激活状态下，SDA和SCL均为低电平
void SCCB_Start(void)
{
    SCCB_SDA(1);
	SCCB_SCL(1);
	delay_us(50);
	SCCB_SDA(0);
	delay_us(50);
	SCCB_SCL(0);
}

//SCCB停止信号
//当时钟为高时，数据线由低到高，为SCCB停止信号
//空闲状态时，SDA和SCL均为高电平
void SCCB_Stop(void)
{
	SCCB_SDA(0);
	delay_us(50);
	SCCB_SCL(1);
	delay_us(50);
	SCCB_SDA(1);
	delay_us(50);
}  

//产生NA信号
void SCCB_No_Ack(void)
{
	delay_us(50);
	SCCB_SDA(1);
	SCCB_SCL(1);	
	delay_us(50);
	SCCB_SCL(0);	
	delay_us(50);
	SCCB_SDA(0);	
	delay_us(50);
}

//SCCB写入一个字节
//返回值：0，成功；1.失败
u8 SCCB_WR_Byte(u8 dat)
{
	SCCB_SDA_OUT();
	u8 j,res;	 
	for(j=0;j<8;j++) //循环8次发送数据
	{
		if(dat&0x80)
		{
			SCCB_SDA(1);	
		}
		else 
		{
			SCCB_SDA(0);
		}
		dat<<=1;
		delay_us(50);
		SCCB_SCL(1);	
		delay_us(50);
		SCCB_SCL(0);		   
	}			 
	SCCB_SDA_IN();		//设置SDA为输入
	delay_us(50);
	SCCB_SCL(1);			//接收第九位，来判断是否成功
	delay_us(50);
	if(SCCB_READ_SDA)
	{
		res=1;	//SDA=发送失败，返回1
	}  
	else 
	{
		res=0;  //SDA=0发送成功，返回0
	}       
	SCCB_SCL(0);		 
	SCCB_SDA_OUT();		//设置SDA为输出 
	return res;  
}	 

//SCCB读取一个字节
//在SCL的上升沿数据锁存
//返回值：读到的数据
u8 SCCB_RD_Byte(void)
{
	u8 temp=0,j;    
	SCCB_SDA_IN();		//设置SDA为输入
	for(j=8;j>0;j--) 	//循环8次接收数据
	{		     	  
		delay_us(50);
		SCCB_SCL(1);
		temp=temp<<1;
		if(SCCB_READ_SDA)
		{
			temp++;
		}   
		delay_us(50);
		SCCB_SCL(0);
	}	
	SCCB_SDA_OUT();		//设置SDA为输出  
	return temp;
} 							    

//写寄存器
//返回值：0，成功；1，失败
u8 SCCB_WR_Reg(u8 reg,u8 data)
{
	u8 res=0;
	SCCB_Start(); 					//启动SCCB传输
	if(SCCB_WR_Byte(SCCB_ID))res=1;	//写器件ID  
	delay_us(100);
  	if(SCCB_WR_Byte(reg))res=1;		//写寄存器地址
	delay_us(100);
  	if(SCCB_WR_Byte(data))res=1; 	//写数据
  	SCCB_Stop();	  
  	return	res;
}		  					    

//读寄存器
//返回值：读到的寄存器的值
u8 SCCB_RD_Reg(u8 reg)
{
	u8 val=0;
	SCCB_Start(); 				//启动SCCB传输
	SCCB_WR_Byte(SCCB_ID);		//写器件ID
	delay_us(100);	 
  	SCCB_WR_Byte(reg);			//写寄存器地址
	delay_us(100);	  
	SCCB_Stop();   
	delay_us(100);	   
	//设置寄存器地址后才是读
	SCCB_Start();
	SCCB_WR_Byte(SCCB_ID|0X01);	//发送读命令 
	delay_us(100);
  	val=SCCB_RD_Byte();		 	//读取数据
  	SCCB_No_Ack();
  	SCCB_Stop();
  	return val;
}















